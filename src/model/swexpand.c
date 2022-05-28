/* SWEXPAND.C
    Called after parsing the network definition.
    Expand subnets; autoconnect and autosplit streams; 
           verify streams.  
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "swsym.h"
#include "sw.h"

/** MATCH(SRC,SNK) is true if port names match. */
#define MATCH(SRC,SNK) if(eqs(srcn,#SRC)) {	\
			  if(eqs(snkn,#SNK)) {	\
				return 1;	\
			  } else {		\
				return 0;	\
			  }			\
		}

/** MAX(A,B) returns highest of A or B */
#define MAX(A,B) ( (A>B)? A: B)

/******************   Local Variables   *****************/
static streamType stype = IS_NET;
static Process fl = NULL;  /** List of processes to free	*/

/**<Anchor for external port list */
/**  List of unmatched external ports.*/
static Extport extprtList = NULL;

/******************   Function Prototypes   *****************/
void linkPort(Process P, Port p);
void linkProc(Model m, Process p);
int fixId(int i);
int verifyStream(Stream s);
int fixId(int i);
char **makeArg(ListArgument la, char *name);
char *fixName(char *name);
Extport makeExtport(PortType type, Process p, Port prt, Arrow a, int id);
Arrow makeArrow(char *iptype, int bs);
Port makePort(int n, Ident id);

Stream makeStream(streamType stype, Process src, Process snk, int bs,
    Model m, Port SourcePort, Port SinkPort, char *iptype);

void checkIPtype(char *msg, char *srcType, char *snkType, char *srcName,
	    char *snkName);

Process makeProcess(Model model, Ident name, 
            Component comp, char **arg, Attribute attr);
            
/******************   Local Functions   *****************/

static char *makeName(char *nn, Process p) /** Create a name string */
{
	char bfr[1000];

	strncpy(bfr, p->name, 500);
	if(p->comp->name[0] == '^') {
	    strncat(bfr,"_",1000);
	    strncat(bfr,p->comp->name+1,1000);
	}
	strncat(bfr, nn, 1000);
	return (strdup(bfr));
}
/** Check depth of subnet expansion.   Subnets may invoke subnets up to maxdepth depth. */
static int checkDepth(int d)
{
	if (d > maxdepth) {
		snprintf(fbfr, BUFFSIZE,
			 "Exceeded maximum subnet expansion depth, %d. Loop maybe.\n",
			 maxdepth);
		FAIL(checkDepth, fbfr);
	}
	return d + 1;
}

/** Copy port structure */
static Port copyPort(Port p0)
{
	Port p1;
	p1 = makePort(p0->id, p0->name);
	*p1 = *p0;
	return p1;
}

// Find a matching port for unmatched external port, ep.  
static int findAmatchingPort(Model m, Process p, Extport ep)
{
	Extport ep2 = NULL;
	Port pt;
	Process p2;
	// Component c=NULL;
	char *srcname;
	char *snkname;

	stype = IS_ORPHAN;

	if (ep->type == SOURCE) {
		srcname = makeName(fixName(ep->source->name),p);
		p2 = getProc(srcname);
		if (!p2) {
			p2 = makeProcess(m, srcname, ep->source->comp,
					 ep->source->arg, ep->source->attr);
		}

		pt = makePort(ep->source_id, ep->name);
	} else { if(ep->type == SINK) {
		        snkname = makeName(fixName(ep->sink->name),p);
		        p2 = getProc(snkname);
		        if (!p2) {
			        p2 = makeProcess(m, snkname, ep->sink->comp,
					 ep->sink->arg, ep->sink->attr);
		        }
		        pt = makePort(ep->sink_id, ep->name);
	        } else {  // Must be ORPHAN 
	            return 0;
	        }
	}
	        
	p2->depth = p->depth + 1;
	ep2 =makeExtport(ep->type, p2, pt, 
	                  makeArrow(ep->iptype, ep->bufsz), -1);
	ep2->next = extprtList;
	ep2->source_id = ep->source_id;
	ep2->sink_id = ep->sink_id;
	ep2->name = ep->name;
	extprtList = ep2;
	return 1;
}



static int sameName(char *s0, char *s1)
{
	if ((s0 == NULL) || (s1 == NULL))
		return 0;

	if (strncmp(s0, s1, 80) == 0)
		return 1;

	return 0;
}

static void buildStream(Model m, Process p, Port pt, Extport ep) {	
	Stream s;
	Process pnew;
	Port ptc = NULL;
	char *srcname;
			    
					s = pt->stream;
					if (s == NULL)
						return;
					verifyStream(s);
					assert(s && pt == s->SourcePort);
					srcname =
					    makeName(fixName(ep->source->name),p);
					pnew =
					    makeProcess(m, srcname,
							ep->source->comp,
							ep->source->arg,
							ep->source->attr);
					s->source = pnew;
					if (ep->bufsz > s->bufsz)
						s->bufsz = ep->bufsz;
					checkIPtype("ExpandAprocessA", ep->iptype,
						    s->iptype, s->source->name,
						    ep->name);
					if ((ep->iptype && ep->iptype[0]) != 0)
						s->iptype = ep->iptype;
					pnew->nportsOut++;
					pnew->depth = p->depth + 1;
					ptc = copyPort(pt);
					ptc->stream = s;
					ptc->id = s->source_id = ep->source_id;
					linkPort(pnew, ptc);
					s->SourcePort = ptc;
					s->SinkPort->match = s->SourcePort;
					s->SourcePort->match = s->SinkPort;
					s->SinkPort->name = s->SourcePort->name;
					verifyStream(s);
}	
	

static void buildStream2(Model m, Process p, Port pt, Extport ep) {		
	Stream s;
	Process pnew;
	Port ptc = NULL;
	char *snkname;
					s = pt->stream;
					if (s == NULL)
						return;
					verifyStream(s);
					assert(s && pt == s->SinkPort);
					snkname =
					    makeName(fixName(ep->sink->name),p);
					pnew =
					    makeProcess(m, snkname,
							ep->sink->comp,
							ep->sink->arg,
							ep->sink->attr);
					s->sink = pnew;
					if (ep->bufsz > s->bufsz)
						s->bufsz = ep->bufsz;
					checkIPtype("ExpandAprocessB", s->iptype,
						    ep->iptype, s->sink->name,
						    ep->name);
					if ((ep->iptype && ep->iptype[0]) != 0)
						s->iptype = ep->iptype;
					pnew->nportsIn++;
					pnew->depth = p->depth + 1;
					ptc = copyPort(pt);
					ptc->stream = s;
					ptc->id = s->sink_id = ep->sink_id;
					linkPort(pnew, ptc);
					s->SinkPort = ptc;
					s->SinkPort->match = s->SourcePort;
					s->SourcePort->match = s->SinkPort;
					verifyStream(s);
}					

static void expandSn(Model m, Process p, Subnetm sn) {
    Extport ep;
    Extport ep2=NULL;
    Process p2=NULL;
    Port    pt=NULL;
    
    ep=sn->extport;
    while(ep) {
        p2 = makeProcess(m, makeName(ep->source->name,p), ep->source->comp,
					 ep->source->arg, ep->source->attr);
	    ep2 =makeExtport(ep->type, p2, pt, 
	                  makeArrow(ep->iptype, ep->bufsz), -1);
	    ep2->source_id = ep->source_id;
	    ep2->sink_id = ep->sink_id;
	    ep2->name = makeName(ep->source->name,p);
        ep2->type=ep->type;
        ep2->source=ep->source;
        ep2->sink=ep->sink;
	    ep2->next = extprtList;
	    extprtList = ep2;
        ep=ep->next;
    }
    
}

static void expandOrphan(Model m, Process p) {	
	Subnetm sn;
	
	if(p->comp->name[0] == '^') {
	    sn = m->subnetm;
	    while (sn) {		// find the subnet for p
		    if (strncmp(sn->name, p->comp->name, 100) == 0) {
			    expandSn(m, p, sn);
			    Debug(Expanding Orphan,p->name);
			    return;
		    }
		    sn = sn->next;
	    }
	    FAIL(expandOrphan,"Cannot find subnet definition");
	}
}

/** Expand process,p, subnet component.  
      Match ep to a port,pt in p.
      Update existing stream,s, in pt */
static void ExpandAprocess(Model m, Process p, Extport ep)
{

	Port pt = NULL;
	checkDepth(p->depth);        /* FAIL if excessive expansion depth*/
	
	if (ep->type == SOURCE) {
		pt = p->port;	/** Find matching sink port  */
		if (pt) {
			do {
				pt->id = fixId(pt->id);
				if ((pt->id == ep->sink_id)
				    || sameName(pt->name, ep->name)) {
			        buildStream(m, p,pt,ep);
			        return;
				}
				pt = pt->next;
			}
			while (pt != p->port);
		}
	} else {		/* type is SINK or ORPHAN */
	  if(ep->type == SINK) {	
		pt = p->port;
		if (pt) {
			do {
				pt->id = fixId(pt->id);
				if ((pt->id == ep->source_id) || sameName(pt->name, ep->name)) {	/* Find matching source port for ep */
			        buildStream2(m, p,pt,ep);
					// s->SourcePort->name = s->SinkPort->name;
					return;
				}
				pt = pt->next;
			}
			while (pt != p->port);
		}
	} else {  /* Must be orphan*/
	        expandOrphan(m, p);
	}}

	findAmatchingPort(m, p, ep);

}
/** Expand a subnet*/
static void ExpandAsubnet(Model m, Process p, Stream s)
{
	char *srcname, *snkname;	// Concatenated process names 
	Process src, snk;
	Port psrc, psnk;
	Stream ns;		/* New Stream */
	stype = IS_NET;
	checkDepth(p->depth);  /* FAIL if excessive expansion depth*/
	srcname = makeName(s->source->name,p);
	snkname = makeName(s->sink->name,p);
	src =
	    makeProcess(m, srcname, s->source->comp, makeArg(NULL, NULL), NULL);
	src->arg = s->source->arg;
	src->attr = s->source->attr;
	snk = makeProcess(m, snkname, s->sink->comp, makeArg(NULL, NULL), NULL);
	snk->arg = s->sink->arg;
	snk->attr = s->sink->attr;
	psrc = makePort(s->source_id, s->source->port->name);
	psnk = makePort(s->sink_id, s->sink->port->name);
	linkPort(src, psrc);
	linkPort(snk, psnk);
	src->nportsOut++;
	snk->nportsIn++;
	//bs = s->bufsz;
	ns = makeStream(stype, src, snk, s->bufsz, m, psrc, psnk, s->iptype);
	ns->sink_id = s->sink_id;
	ns->source_id = s->source_id;
	ns->bufsz = s->bufsz;
	ns->type = stype;
	psrc->stream = psnk->stream = ns;
	ns->source->depth = ns->sink->depth = checkDepth(p->depth);
	ns->SinkPort->match = ns->SourcePort;
	ns->SourcePort->match = ns->SinkPort;
	verifyStream(ns);
	verifyStream(s);

}

/** Expand the model for each external port and stream in the subnet */
static void expandSubnet(Model m, Process p, Subnetm sn)
{
	Stream s;
	Extport ep;

	ep = sn->extport;
	while (ep) {
		ExpandAprocess(m, p, ep);
		ep = ep->next;
	}

	s = sn->stream;
	while (s) {
		ExpandAsubnet(m, p, s);
		s = s->next;
	}

}

/** Add process to list to be freed.  */
static void FreeLater(Process * fl, Process p)
{
	p->next = *fl;
	*fl = p;
}

	/** Expand a subnet process, i.e. replace this process
	   with its subnet */
static void expandSub(Model m, Process p)
{
	Subnetm sn;

	sn = m->subnetm;
	while (sn) {		// find the subnet for p
		if (strncmp(sn->name, p->comp->name, 100) == 0) {
			expandSubnet(m, p, sn);
			return;
		}
		sn = sn->next;
	}

	snprintf(fbfr, BUFFSIZE,
		 "Cannot find subnet %s for process %s\n", p->comp->name,
		 p->name);
	FAIL(expandSub, fbfr);
}	/** While some process contains a subnet component, 
	   expand that component subnet. */
static void explodeSubnets(Model m)
{
	Process p, pp, ps;
	int more;		/** 1=could be more subnets  	*/
	int level = 0;		/** subnet level 	 	*/
	int nexpands = 0;
			/** number of expanded subnets */

	do {
		p = m->proc;
		pp = NULL;  /* Previous process in chain*/
		more = 0;
		/* Allow limit on graph expansion. */
		while (p && (m->maxexpands < 0 || nexpands < m->maxexpands)) {
			if (p->comp) {
				if (p->comp->path[0] == '_') {	/* Is a subnet */
					more = 1;
					nexpands++;
					m->nprocs--;
					ps = p;
					if (pp)	// delink p from process chain.     
						pp->next = p->next;
					else {
						m->proc = p->next;
					}
					expandSub(m, ps);
			        level++;
					FreeLater(&fl, ps);	/* Pointers to ps still exist. */
					break;
				}
			}
			pp = p;
			p = p->next;
		}
	}
	while (more);

	if (level > m->level)
		m->level = level;
}

/** return true if external port is matched.*/
static int Matched(Extport ep2)
{
	Port pt;
	int id;

	id = ep2->sink_id;
	pt = ep2->sink->port;
	do {
		if (pt->id == id) {
			if (pt->match == NULL) {
				return 0;
			}
			return 1;
		}
		pt = pt->next;
	}
	while (pt != ep2->sink->port);
	return 0;
}

//Iptypes match if they are identical or if one or the other is not specified.
static int matchIpType(char *t1, char *t2)
{
    if (strncmp(t1, t2, 100) == 0)  
            return 1;

	if ((t1 == t2) ||
	    (t1 == NULL) || (t2 == NULL) ||
	    (t1[0] == 0) || (t2[0] == 0) || (t1[0] == ' ') || t2[0] == ' ')
		return 1;

	return 0;
}

/** Return true if names match.*/
static int MatchName(String srcn, String snkn)
{

	if (srcn == NULL)
		return 0;
	MATCH(OUT, IN);
	MATCH(TAB, SLOT);
	MATCH(PLUG, SOCKET);
	MATCH(out, in);
	MATCH(tab, slot);
	MATCH(plug, socket);

	if (eqs(srcn, snkn))
		return 1;

	return 0;
}


/** match external ports: ep2 is sink port
 * If ep has a name and/or iptype, they must match.
 * It may be necessary to match ports in some logical sequence by
 * ordering the external port list with more specifically defined ports first.
**/
static int isaMatch(Extport ep2, Extport ep)
{

	if (Matched(ep2))  
		return 0;

	if (!matchIpType(ep->iptype, ep2->iptype))
		return 0;

	if (ep->name) {
		if ((ep2->source_id < 0) && MatchName(ep->name, ep2->name))
			return 1;
		return 0;
	}

	if ((ep->sink_id == ep2->source_id))
		return 1;

	return 0;
}

static int typeOK(char *s1, char *s2)
{
	if (s1 == NULL || *s1 == 0)
		return 1;
	if (s2 == NULL || *s2 == 0)
		return 1;

	if (MatchName(s1, s2))
		return 1;

	return 0;
}

void checkIPtype(char *msg, char *srcType, char *snkType, char *srcName,
	    char *snkName)
{

	if (!typeOK(srcType, snkType)) {
		fprintf(stderr,
			"FATAL/%s: Type Mismatch for (%s) -%s>  and (%s) -%s>\n",
			msg, srcName, srcType, snkName, snkType);
		FAIL (checkIPtype, "");
	}
}

/** Slow, bubble sort to put ports for process p in order by port ID */
static void SortPorts(Process p)
{
	Port pt0, pt1, pt2, ptw;
	int more = 1;

	pt0 = p->port;
	if (!pt0->next)
		return;

	while (more) {
		pt1 = pt0;
		pt2 = pt0->next;
		more = 0;
		while (pt2 != pt0) {
			if (pt1->id > pt2->id) {
				more = 1;
				if (p->port == pt1) {
					pt1->next = pt2;
					pt1->prev->next = pt2;
					pt2->prev = pt1;
					pt2->next = pt1;
					pt1->prev = pt2;
					ptw = pt1;
					pt1 = pt2;
					pt2 = ptw;
					pt0 = p->port = pt1;
				} else {
					pt1->next = pt2->next;
					pt1->prev->next = pt2;
					pt2->prev = pt1->prev;
					pt2->next = pt1;
					pt1->prev = pt2;
					ptw = pt1;
					//pt1 = pt2;
					pt2 = ptw;
				}
			}
			pt1 = pt2;
			pt2 = pt1->next;
		}
	}
}


static char *pickType(char *t1, char *t2) {
    if(t1==NULL || t1[0]==0) 
            return t2;
            
    return t1;
}


/** Create a new stream structure. */
static void createStream(Model m, Extport ep, Extport ep2)
{
	Stream s;
	Port snkpt, srcpt, pt;

	srcpt = ep->source->port;

	pt = ep2->sink->port;
	while (pt->id != ep2->sink_id) {
		pt = pt->next;
		if (pt == ep2->sink->port) {
			FAIL(createStream, "No matching external sink port");
		}
	}
	snkpt = pt;

	while (srcpt->id != ep->source_id) {
		srcpt = srcpt->next;
		if (srcpt == ep->source->port) {
			FAIL(creatStream, "No matching external source port");
		}
	}

	checkIPtype("createStream", ep->iptype, ep2->iptype, ep->name,
		    ep2->name);

	s = makeStream(IS_NET, ep->source, ep2->sink,
		       MAX(ep->bufsz, ep2->bufsz), m, srcpt, snkpt,
		       pickType(ep->iptype,ep2->iptype));

	linkProc(m, ep->source);
	linkProc(m, ep2->sink);

	s->SourcePort->match = s->SinkPort;
	s->SinkPort->match = s->SourcePort;
	s->SourcePort->stream = s;
	s->SinkPort->stream = s;
	s->SourcePort->id = s->source_id = fixId(ep->source_id);
	s->SinkPort->id = s->sink_id = fixId(ep2->sink_id);

	SortPorts(s->source);
	SortPorts(s->sink);
	verifyStream(s);
}

static void removeDeadStreams(Model m)
{
	Stream s, sp;

	s = m->stream;
	while (s != NULL) {
		if (s->source->comp != NULL) {
			if (s->source->comp->path[0] == '_') {	/* if subnet, remove stream */
				if (s == m->stream) {
					m->stream = s->next;
				} else {
					sp->next = s->next;
					s = sp;
				}
				//free(s);
			}
		}
		sp = s;
		s = s->next;
	}
}




/** Create a new stream if external port is matched.*/
static int findSink(Model m, Extport ep)
{
	Extport ep2;		/* sink port */
	Process p;

	ep2 = extprtList;

	while (ep2) {
		if (ep2->type == SINK) {
			p = ep2->sink;
			if (p != ep->source) {
				if (isaMatch(ep2, ep)) {
					createStream(m, ep, ep2);
					return 1;
				}
			}
		}
		ep2 = ep2->next;
	}
	return 0;  
}


	/** Create new streams for matching external ports.
	    Then identify and mark any leftover orphan processes, 
	    creating orphan streams. 
	**/
static void autolink(Model m)
{
	Extport ep;
	Process p;

	ep = extprtList;
	stype = IS_NET;

	while (ep) {
		if (ep->type == SOURCE) {
			findSink(m, ep);  /** Create a new stream if external
			                          port is not already matched.*/
		}
		ep = ep->next;
	}

	p = m->proc;

	while (p) {
		if (p->nportsIn + p->nportsOut == 0) {
			p->kind = IS_ORPHAN;
			makeStream(IS_ORPHAN, p, NULL, -1, m, NULL, NULL, "");
		}
		p = p->next;
	}
}

		/** Fix  port stream pointers for this stream */
static void fixStream(Stream s2)
{
	Process p;
	Port pt;

	p = s2->source;
	pt = p->port;

	do {
		pt->id = fixId(pt->id);
		if (pt->id == s2->source_id) {
			pt->stream = s2;
			return;
		}
		pt = pt->next;

	}
	while (pt != p->port);

	/*  Fix Sink port for this stream */
	p = s2->sink;
	pt = p->port;

	do {
		pt->id = fixId(pt->id);
		if (pt->id == s2->sink_id) {
			pt->stream = s2;
			return;
		}
		pt = pt->next;

	}
	while (pt != p->port);

}
			/** Fix Fan in */
static void fixFan2(Model m, Process p, Port pt0, Port pt)
{
	Process j;		// New anonymous join process 
	Component c;
	Port pt1, pt2, ptn;
	Stream s0, s1, s2;

	/*              BEFORE 
	   (A)id <- x(B);    [ s0 pt0 psnk0]
	   (A)id <- y(C);    [ s1 pt  psnk1]  */

	/*              AFTER
	   (A)id <- 2(_ sw.Join);  [ s0 pt0 ptn]  
	   (j)1  <- x(B);          [ s2 pt2   ]  
	   (j)0  <- y(C);          [ s1 pt1   ] 
	 */

	c = makeComponent("Join", STDPACKAGE);
	j = makeProcess(m, "_", c, makeArg(NULL, NULL), NULL);
	j->depth = p->depth + 1;

	pt1 = makePort(0, "");
	pt2 = makePort(1, "");
	ptn = makePort(2, "");	/*Join output */

	s1 = pt->stream;
	s0 = pt0->stream;

	checkIPtype("FixFan2", s0->iptype, s1->iptype, s0->source->name,
		    s1->source->name);

	if (s0->iptype == NULL || s0->iptype[0] == 0)
		s0->iptype = s1->iptype;

	if (s1->iptype == NULL || s1->iptype[0] == 0)
		s1->iptype = s0->iptype;

	s2 = makeStream(IS_NET, pt0->stream->source, j,
			pt0->stream->bufsz, m, pt0, pt, pt0->stream->iptype);
	s2->SourcePort = s0->SourcePort;

	s0->source = j;
	s0->SourcePort = ptn;
	s0->SourcePort->stream = s0;
	s0->source_id = ptn->id;
	ptn->stream = s0;

	s2->sink_id = 1;
	assert(s0->SinkPort->stream == s0);
	s2->source_id = s2->SourcePort->id;
	s2->SinkPort = pt2;
	s2->SourcePort->stream = s2;
	pt2->stream = s2;

	s1->sink = j;
	s1->sink_id = 0;
	assert(s2->SourcePort->stream == s2);

	pt->next->prev = pt0;	// Delink pt
	pt0->next = pt->next;
	p->nportsIn--;

	/* Fix j ports */
	ptn->id = 2;
	ptn->name = "";

	j->port = pt1;
	pt1->next = pt2;
	pt2->next = ptn;
	ptn->next = pt1;

	pt2->next->prev = pt2;
	pt1->next->prev = pt1;
	ptn->next->prev = ptn;

	pt1->stream = s1;
	pt2->stream = s2;
	s1->SinkPort = pt1;
	j->nportsIn = 2;
	j->nportsOut = 1;
	fixStream(s2);
	fixStream(s1);

	s0->SinkPort->match = s0->SourcePort;
	s0->SourcePort->match = s0->SinkPort;
	s1->SinkPort->match = s1->SourcePort;
	s1->SourcePort->match = s1->SinkPort;
	s2->SinkPort->match = s2->SourcePort;
	s2->SourcePort->match = s2->SinkPort;
	verifyStream(s0);
	verifyStream(s1);
	verifyStream(s2);
}

/** Create anonymous Split process if output port directed to more than one process.*/
static void fixFanOut(Model m, Process p, Port pt0, Port pt)
{
	Process j;		// New anonymous split process 
	Component c;
	Port pt1, pt2;
	Stream s0, s1, s2;

	/*              BEFORE 
	   (B)x <- id(A);  [ s0 pt0]
	   (C)y <- id(A);  [ s1 pt ]  */
	/*              AFTER
	   (B)x <-  1(j);  [ s0 pt0]  
	   (C)y <-  2(j;   [ s1    ] 
	   (j)0 <- id(A);  [ s2    ]  */

	c = makeComponent("Split", STDPACKAGE);
	j = makeProcess(m, "_", c, makeArg(NULL, NULL), NULL);
	j->depth = p->depth + 1;

	pt1 = makePort(1, "");
	pt2 = makePort(2, "");
	s0 = pt0->stream;
	s1 = pt->stream;

	checkIPtype("fixFanOut", s0->iptype, s1->iptype, s0->source->name,
		    s1->sink->name);

	if (s0->iptype == NULL || s0->iptype[0] == 0)
		s0->iptype = s1->iptype;

	s2 = makeStream(IS_NET, pt0->stream->source, j,
			pt0->stream->bufsz, m, pt0, pt, pt0->stream->iptype);

	s0->iptype = s1->iptype = s2->iptype;

	s2->sink_id = 0;
	s2->source_id = pt0->id;

	s1->SourcePort = pt2;
	s1->source = j;
	s1->source_id = 2;

	s0->source = j;
	s0->source_id = 1;
	s0->SourcePort = pt1;
	s0->SinkPort->match = s0->SourcePort;
	s0->SourcePort->match = s0->SinkPort;

	pt->next->prev = pt0;	// Delink pt
	pt0->next = pt->next;
	p->nportsOut--;

	/* Fix j ports */
	j->port = pt;
	pt->id = 0;
	pt->stream = s2;
	pt->name = "";
	pt->next = pt1;
	pt1->next = pt2;
	pt2->next = pt;
	pt2->prev = pt1;
	pt1->prev = pt;
	pt->prev = pt2;
	pt1->stream = s0;
	pt2->stream = s1;
	j->nportsIn = 1;
	j->nportsOut = 2;
	s0->SourcePort->stream = s0;
	s1->SourcePort->stream = s1;
	s2->SourcePort->stream = s2;
	s0->SinkPort->stream = s0;
	s1->SinkPort->stream = s1;
	s2->SinkPort->stream = s2;
	assert(s1->SourcePort != s2->SinkPort);
	s0->source_id = s0->SourcePort->id;
	s1->source_id = s1->SourcePort->id;
	s2->source_id = s2->SourcePort->id;
	s0->SinkPort->match = s0->SourcePort;
	s0->SourcePort->match = s0->SinkPort;
	s1->SinkPort->match = s1->SourcePort;
	s1->SourcePort->match = s1->SinkPort;
	s2->SinkPort->match = s2->SourcePort;
	s2->SourcePort->match = s2->SinkPort;
	verifyStream(s0);
	verifyStream(s1);
	verifyStream(s2);

}

/** Search for fanin/fanout conditions */
static void fixFan(Model m, Process p)
{
	Port pt, pt0;
	int id = -999;

	pt = p->port;		/* pt may be = 0 */

	if (pt != 0) {
		do {
			pt->id = fixId(pt->id);
			if (pt->id == id) {
				if (pt0->stream->sink == p
				    && (pt->stream != NULL)
				    && pt->stream->sink == p) {
					fixFan2(m, p, pt0, pt);
					pt = p->port;	/* Go back to first port */
				} else {
					if (pt0->stream->source == p
					    && (pt->stream != NULL)
					    && pt->stream->source == p) {
						fixFanOut(m, p, pt0, pt);
						pt = p->port;	/* Go back to first port */
					}
				}
			}
			id = pt->id;
			pt0 = pt;
			pt = pt->next;
		}
		while (pt != p->port);
	}
}

/** For all processes(p) Fix fan in and fan out. 
   * Insert sw.Join  process wherever fanin occurs.
   * Insert sw.Split process wherever fanout occurs. 
*/
static void fixFanInOut(Model m)
{
	Process p;

	p = m->proc;

	while (p) {
		fixFan(m, p);
		p = p->next;
	}
}



/******************   Global Functions   *****************/
int verifyStream(Stream s){ /* Check proper Stream connections */
	Process src, snk;
	Port psrc, psnk;

	if (s == NULL) {
		FAIL(verifyStream, "No stream to verify.");
	};
	src = s->source;
	snk = s->sink;
	assert(src && snk);
	psrc = s->SourcePort;
	psnk = s->SinkPort;

	assert(psrc && psnk);
	assert(psrc->id == s->source_id);
	assert(psnk->id == s->sink_id);
	assert(psrc->stream == s);
	assert(psnk->stream == s);
	assert(s->SourcePort->stream->SourcePort == s->SourcePort);
	assert(s->SinkPort->stream->SinkPort == s->SinkPort);

	if (src->kind == IS_NET || src->kind == IS_STRUCT) {
		assert(psnk->match == psrc);
		assert(psrc->match == psnk);
	}

	return 1;
}

/** Free discarded process structure memory. */
static void freeExpandedProcesses(Process * fl)
{
	Process pn;

	while (*fl != NULL) {
		pn = (*fl)->next;
		free(*fl);
		*fl = pn;
	}
	*fl = NULL;
}

void expandModel(Model m) {    /* Called by sw.c after parsing */
	fixFanInOut(m);	/* Insert Join and Split processes as necessary. */
	explodeSubnets(m);
	fixFanInOut(m);
	autolink(m);	           /* Connect disconnected matching ports. */
	removeDeadStreams(m);      /*  Some streams could have 
	                                only subnet components. */
	freeExpandedProcesses(&fl);	/* Remove dead streams first.*/
}	

/************************   End of SWEXPAND.C   ****************/
