/** @file swgraph.c
		  Generate Graphviz input(.dot file)  
		  
    @todo remove braces from path here or previously.		  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "sw.h"
#include "swconfig.h"


#define P(s) printf("%s\n",(#s));	/**<Print String*/
#define FIXINDENT(s) {};		/**<Nullify FIXINDENT */
#define C(s) printf("%s,\n",(#s));	/**<Print String*/

/** Define to remove process ports from graph */

/** Type of Component name */
typedef enum
{ NOCOMP, COMPNAME, WITHPATH } SHOWC;
static SHOWC showcomp = COMPNAME; /**<??*/
static char *twoline = "";	  /**<??*/

/** Find port for id */
static Port
findPort (Port pt, int id)
{
  Port pt0 = pt;

  do
    {
      if (pt->id == id)
	{
	  return pt;
	}
      pt = pt->next;
    }
  while (pt != pt0);

  return NULL;	       /** @todo SWGRAPH error message on error   */
}

/** Assign channel to ports for stream */
static int
assign_channel (int ch, Stream f)
{

  findPort (f->source->port, f->source_id)->channel = ch;
  findPort (f->sink->port, f->sink_id)->channel = ch;
  return ch;
}

/** For each stream; assign the channel */
static void
assignChannels (Model m)
{
  int ch = m->nstreams - 1;
  Stream f = m->stream;

  while (f)
    {
      if (f->type == IS_NET)
	assign_channel (ch--, f);
      f = f->next;
    }
}

///////////////////////////////////////////////////
#define RB "}"	/**<Right Brace*/
#define LB "{"	/**<Left Brace*/

/** Generate End Of Block */
static void
genSuffix ()
{
  printf ("%s\n", RB);
}

/** Generate beginning of .dot file */
static void
genPrefix (char *gname, int nstreams)
{

  printf ("#Prefix here. %d streams\n", nstreams);
  printf ("digraph \"%s\" %s", gname, LB);

  printf
    ("URL=\"https://github.com/tyoung3/sw/blob/master/nds/%s\" graph [",
     gname);
  printf ("\tname=\"Streamwork/swgraph:  v%s\",\n", version);
  C (fontcolor = black);
  printf ("\tlabel=\"https://github.com/tyoung3/sw\",\n");
  P (fontname = "Helvetica");
  printf ("]");

  // FIXINDENT(\();
  C (node[shape = record);
     C (fontsize = "18"); C (fontcolor = black); C (fontname = "Helvetica");
     C (color = black); C (fillcolor = powderblue); C (style = filled);
     P (height = .2);
     P (];);
  C (edge[color = blue);
     C (style = bold);
     // NG in dot.    C(              len=0.1);
     C (fontsize = "18"); C (labelfontcolor = black);
     C (fontcolor = blue);
     P (]);

}

#ifdef SHOW_PORTS
/** Generate port data */
static void
genPort (int n)
{
  printf ("<%i> %i  ", n, n);
}
#else 
#define genPort(X) 
#endif

/** Generate arguments */
static void
genArgs (char **a)
{
  int i = 1;

  while (a[i] != NULL)
    {
      printf (" \\\"%s\\\"", a[i++]);
    }
}

/** return generated URL */
static char *
makeURL (char *comp)
{
  char bfr[110];

  snprintf (bfr, sizeof (bfr) - 1, "%s%s.html", htmldir, comp);   /* htmldir is guaranteed to have a trailing slash('/'). */
  return strndup (bfr, sizeof (bfr) - 1);
}

    /**  EXAMPLE: label="{<P> G1 Gen1 \"xyz\" |{<0> 0 |<1> 1 } }"  */
    
	  // genProc (p->name, p->comp->name, p->comp->path, "taos_", p->arg);
static void genProc1(Process p,  char *host) {
  char **args=p->arg;
  char *comp=p->comp->name;
  char *name=p->name;
  char *path=p->comp->path;
  
  printf ("       \"%s\" ", name);
  printf ("[shape = record,");
  C (color = "black");
  printf ("  URL=\"%s\"\n", makeURL (comp));
  printf (" host=\"%s\" \n", host);
  printf (" tooltip=\"%s.%s ", path, comp);
  genArgs (args);
  printf ("\"\n");
  
  switch (showcomp)
    {
    case NOCOMP:
      printf ("label=\"{<P> %s ", name);
      break;
    case COMPNAME:
      printf ("label=\"{<P> %s %s %s", name, twoline, comp);
      genArgs (args);
      break;
    case WITHPATH:
      printf ("label=\"{<P> %s %s %s.%s", name, twoline, path, comp);
      genArgs (args);
    }
}

 
/** End code for process */
static void
endProc ()
{
  printf ("\"\n");
  printf ("];\n");		// End proc 
}

/** Generate graph cluster code */
static void
genCluster1 (char *name)
{

  printf ("subgraph \"cluster%s\" %s\n", name, LB);
  printf ("label = \"%s\"; name=\"%s\";\n", name, name);
  printf ("URL=\"%s.html\";\n\n", name);
}

/** Find channel for port */
static int
findChannel (Port p, int id)
{
  Port p0;

  p0 = p;

  do
    {
      if (p->id == id)
	{
	  return p->channel;
	}
      p = p->next;
    }
  while (p != p0);

  return -1;
}

/** Generate port code */
static void
showPorts (Stream f, Process src, Process snk, int channel)
{
#ifdef SHOW_PORTS
  printf
    ("\"%s\":%i -> \"%s\":%i [label=\"%i\"]\",headlabel=\"%.i\",taillabel=\"%.i\"",
     tooltip = \"%i[%i]\"];\n",
#else
  printf
    ("\"%s\" -> \"%s\" [label=\"%i\",headlabel=\"%.i\",taillabel=\"%.i\",	tooltip=\"%i[%i]\"];\n",
#endif
     src->name,
     snk->name, channel, f->sink_id, f->source_id, channel, f->bufsz);
}

static void
genLinks (Model m)
{				// [label="C Miss"];
  Stream f;
  Process src, snk;
  int channel = 7;
  char *edgeColor = "purple";
  f = m->stream;
  while (f)
    {
      if (f->type == IS_NET)
	{
	  edgeColor = "black";
	  src = f->source;
	  snk = f->sink;
	  channel = findChannel (src->port, f->source_id);
	  if(f->bufsz > 1) {
	  	edgeColor="orange";
	  }	
	  if(f->bufsz == 1) {
	  	edgeColor="green";
	  }
	  if(f->bufsz > 99) {
	  	edgeColor="red";
	  }
	 	
	  if (f->bufsz < 1000000)  // ? < 2 
	    {
#ifdef SHOW_PORTS
	      printf
		("\"%s\":%i -> \"%s\":%i [label=\"%i %s\",headlabel=\"%.i\",taillabel=\"%.i\",tooltip=\"%i\"];\n",
#else
	      printf
		("\"%s\"  -> \"%s\"  [color=%s,label=\"%i %s\",headlabel=\"%.i\",taillabel=\"%.i\",tooltip=\"%i\"];\n",
#endif
		src->name, snk->name, edgeColor, channel, f->iptype, f->sink_id, f->source_id,
		   f->bufsz);
	    }
	  else
	    {
	      showPorts (f, src, snk, channel);
	    }
	}			// End if IS_NET             
      f = f->next;
    }				// End while
}


static void
genProcs (Process p)
{

  while (p)
    {
      if (p->kind == IS_NET)
	{
	  printf ("#(%s %s.%s) %d ports\n",
		  p->name,
		  p->comp->path, p->comp->name, p->nportsIn + p->nportsOut);
	  // genProc (p->name, p->comp->name, p->comp->path, "taos_", p->arg);
	  genProc1 (p, "taos_");
#ifdef SHOW_PORTS	
	  Port pt;
	  pt = p->port;
	  printf ("|{");
	  do
	    {
	      genPort (pt->id);
	      pt = pt->next;
	      if (pt != p->port)
		{
		  printf ("|twy");
		}
	    }
	  while (pt != p->port);
	  printf (" }");
#endif	  
	  printf (" }");
	  endProc ();
	}
      else if (p->kind == IS_ORPHAN)
	{
	  printf ("#(%s %s.%s) %d ports\n",
		  p->name,
		  p->comp->path, p->comp->name, p->nportsIn + p->nportsOut);
	  genProc1(p, "taos_");
	  printf (" }");
	  endProc ();
	}			// End if IS_NET      
      p = p->next;
    }


  printf ("\n");
}


/** Generate .dot file from network model. */
void
genGraph (Model model)
{
  Stream f;
  Process p;
  assignChannels (model);
  //* Generate commented Reconstructed Network Definition */
  printf ("#########   Expanded Network Definition   ######### \n");
  f = model->stream;

  while (f)
    {
      switch (f->type)
	{
	case IS_NET:
	  printf ("# (%s %s/%s)%d\t\t<- %d(%s %s/%s) \n",
		  f->sink->name, f->sink->comp->path,
		  f->sink->comp->name, f->sink_id,
		  f->source_id, f->source->name,
		  f->source->comp->path, f->source->comp->name);
	  break;
	case IS_SUB:
	  break;
	case IS_ORPHAN:
	  printf ("# %s %s/%s\n",
		  f->source->name, f->source->comp->path,
		  f->source->comp->name);
	}
      f = f->next;
    }

  printf ("\n");
  //* Generate Prefix code */
  genPrefix (model->name, model->nstreams);
  genCluster1 (model->name);
  p = model->proc;
  /* Get first process */
  genProcs (p);			/*{ */
  printf ("%s", RB);		/* End Cluster1 */
  genLinks (model);
  genSuffix ();			//* Generate Suffix code */
}

/*    End of SWGRAPH.C  */
