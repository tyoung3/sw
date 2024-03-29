/** @file s_wgo.c 
		  Greate a main Go program from the network model	
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>  // getcwd

#include "swsym.h"
#include "model.h"
#include "sw.h"

#define MAX_BUF 100

/** Print string.*/
#define P(s) printf("%s\n",(#s));	
#define PE(s) {};  			        /**<Print empty string */
#define C(s) printf("%s",(#s));		/**<Print defined string*/

/**Get timestamp*/
static String Timestamp()
{
    time_t ltime;		/* calendar time */
    ltime = time(NULL);		/* get current cal time */
    return (asctime(localtime(&ltime)));
}

/** Generate Suffix code */
void genSuffix(char *name)
{
    P(_wg.Wait());
    printf("\tfmt.Println(\"\\u001b[32m\",\"%s: Ended\",\"\\u001b[0m\")\n}\n",name);
}

String deleteBrace(char *s0) {
	char *s=s0;
		
	do {
		if(*s == '}') 
			*s=0;
		s++;
	} while(*s !=0);

	return s0; 
}

/** Print generated module path.*/
static void genPath(Component  c)
{
    char *s=c->path;
    char *importLib  = { defaultLibrary };
    
    if( strcmp(s,STDPACKAGE) == 0) 
    	 return;
    if(s[0] == '{') {
    	printf("import \"%s\"\n",  deleteBrace(s+1));
    } else {
    if(s[0] == '/') {
    	printf("import \"%s\"\n",   s);
    } else {
    	printf("import \"%s%s\"\n", importLib,   s);
    }}	
}

/** Return true if path is new.*/
int newPath(char *p)	
{

    if (getPath(p) == 1)
	return 1;

    return 0;
}

#define StringIt(X) #X

/** Create import paths from process structs.*/
static void genPaths(Model m)
{
    Process p;

    P(import "sync");
    P(import "fmt");

    p = m->proc;
    while (p) {
	if (newPath(p->comp->path)) {
	    genPath(p->comp);
	}
	p = p->next;
    };

    printf("\n\n");
}


/** Find process port from matching port id */
static Port findPort(Process p, int id)
{
    Port pt = p->port;
    Port pt0 = pt;


    do {
	if (pt->id == id) {
	    return pt;
	}
	pt = pt->next;
    } while (pt != pt0);

    snprintf(fbfr, BUFFSIZE, "Process %s Port %i mismatch\n", p->name, id);
    FAIL(findPort, fbfr);
}

/** Print arguments for process.*/
static void showArgs(Process p)
{
    int i = 1;

    if (!p->arg)
	return;

    while (p->arg[i] != NULL) {
	printf(" \"%s\"", p->arg[i]);
	i++;
    }


}

/** Print Sink process */
static void showSink(Process p, int id)
{

    printf("(%s %s.%s ", p->name, p->comp->path, p->comp->name);

    showArgs(p);


    printf(")");
    if (id > 0)
	printf("%d", id);
    printf(" ");
}

/** Print Source Process */
static void showSource(int kind, Process p, int id, int bfsz, char *iptype)
{
    char dash='-';
    
    
    if(iptype==NULL)
    	 iptype="";
    	 	
    switch (kind) {
        case IS_STRUCT:
            dash='=';
            break;
        default:
            dash='-';    
    }
    
    if (bfsz == defaultBufferSize) {
	    printf("\t<%s%c\t%d(%s %s.%s",
	       iptype, dash, id, p->name, p->comp->path, p->comp->name);
    } else {
	    printf("\t<%s %d%c\t", iptype, bfsz, dash);
	if (id > 0)
	    printf("%d", id);
	printf("(%s %s.%s", p->name, p->comp->path, p->comp->name);
    }

    showArgs(p);
    printf(");\t\n");
}

/** Assign channel number to source and sink ports.*/
static int assign_channel(int ch, Stream f)
{

    findPort(f->source, f->source_id)->channel = ch;
    findPort(f->sink, f->sink_id)->channel = ch;
    return ch;
}

/** For each stream; assign the channel to source and sink ports.  Must be done after expansion is complete*/ 
static void assignChannels(Model m)
{  
    int nstreams;
    int ch;
    Stream f = m->stream;

    nstreams = m->nstreams + m->nStructStreams + 
        m->nIntStreams + m->nStringStreams;
    ch = nstreams - 1;

    while (f) {
	switch (f->type) {
	   case IS_SUB:
	   case IS_ORPHAN:
	   case IS_IFACE:
		break;
	   case IS_NET:
	   case IS_STRUCT:
		assign_channel(ch--, f);
	    	break;
	}
	f = f->next;
    }
}

#ifdef NBRMULTIPLESrunning
/**  Count number of streams connecting identical nodes */
static int nbrMultiples(Model m)
{
    Stream s, s2;
    Process p1, p2, p3, p4;
    int n = 0;

    s = m->stream;
    while (s) {
	s2 = s->next;
	p1 = s->source;
	p2 = s->sink;
	while (s2) {
	    p3 = s2->source;
	    p4 = s2->sink;
	    if ((p1 == p3 && p2 == p4) || (p1 == p4 && p2 == p3)) {
		n++;
	    }
	    s2 = s2->next;
	}
	s = s->next;
    }

    return n;
};
#endif


/** @todo  Handle unmatched ports by autconnecting to dummy process.  
*/
static void ConnectProcess(Process p, int partn) {
	Port pt;

	if(p->partn==partn)
		return;

	p->partn=partn;
	pt=p->port;
	if(pt) {
		do {
		   if(pt->match) {
			if(pt->match->stream->source!=p) 
				ConnectProcess(pt->match->stream->source,partn);
			if(pt->match->stream->sink!=p)
				ConnectProcess(pt->match->stream->sink,partn);
		   }
		   pt=pt->next;
		} while(pt!=p->port);
	}	
}

/** For every disconnected process; 
    increment partn and
    set partn in every connected process;	
*/
static int ComputeNpartitions(Model m) {
	Process p;
	int nparts=0;

	p=m->proc;
	while(p) {
		p->partn=0;
		p=p->next;
	}

	p=m->proc;
	while(p) {
		if(p->partn==0) {
			nparts++;
			ConnectProcess(p,nparts);
		}
		p=p->next;
	}

	return nparts;
}

/** Return 's' or blank. */
String Plural(int n) {
	if(n==1) 
		return "";
	return "s";
}

/** Print orphan data */
static void ShowOrphan(Process p) {
    printf("%s %s.%s", p->name, p->comp->path, p->comp->name);
    showArgs(p);
    printf(";\n");
}

/** Show Network definition */
static void showND(Model m)
{
    Stream f;
    int nparts, ncycles;			/* Number of partitions */
    int nstreams;           /* Total nbr streams of all types */

    /** Generate commented Reconstructed Network Definition */
    printf
	("            ***  Expanded Network Definition  ***\n");
    f = m->stream;
    assignChannels(m);

  while (f) {
    char *ftype;
    if(f->iptype == NULL || f->iptype[0] == 0) {
        ftype=defaultChannelType;
    } else {
        ftype=f->iptype;
    }        
	switch (f->type) {
	    case IS_IFACE:
		case IS_SUB:
			break;
		case IS_STRUCT:
		case IS_NET:
	    		showSink(f->sink, f->sink_id);
	    		showSource(f->type,f->source, f->source_id, 
	    		    f->bufsz, ftype);
	    		break;    
		case IS_ORPHAN:
			ShowOrphan(f->source);
	} 
	f = f->next;
  }

    nparts=ComputeNpartitions(m);

    nstreams=m->nstreams + m->nStructStreams + 
        m->nIntStreams + m->nStringStreams;
    ncycles= nstreams - m->nprocs + nparts;  
    printf("%d stream%s, %d processes, %d component%s, %d partition%s, %d cycle%s.\n*/\n",
		nstreams, Plural(nstreams), 
		m->nprocs,
		m->ncomponents, Plural(m->ncomponents),
		nparts, Plural(nparts), 
		ncycles, Plural(ncycles));
}

#ifdef SHASUM
static void getSha(char *s) {
    char bfr[100]; 
    snprintf(bfr,100,"shasum %s",s);
    system(bfr); 

}
#endif

char *fixModule(Model m, char *ftype) {
		char bfr[MAX_BUF+1]; 
		int i=0;
		
		if(strncmp(ftype,"interface{}",30) == 0)  
		  	return "";
		
		if( ftype[0] < 'A' || ftype[0] > 'Z' ) 
			  return "";
			  
		while(m->name[i] != 0) {
				bfr[i]=m->name[i];
			  if(m->name[i] == '.') {
			  		bfr[i+1]=0;
			  		return strdup(bfr);	
			  }
				i++;
		}		
			
		bfr[i]='.';
		bfr[++i]=0;	
		return strdup(bfr);	
}

static int lowerCase(char c) {
		if( (c >= 'a') && (c <= 'z') )  
				return 1;
				
	  return 0;			
}

// If in package, type must be capitalized.
static int badType(char *t) {
		char *t2=t;
		char *t3=0;
		
		while(t2[0]!=0) {    /* find last period(.) */
				if( t2[0]=='.')	
					t3=t2;
				t2++;	
	  }
	  				
	  if( (t3!=0) && lowerCase(t3[1]) )  
						return 1;
						
		return 0;
}

#define red "\033[31m"

static void MakeChannels(Model m) {  
    int nstream=0;
    Stream f = m->stream;
    char *module="postage.";
    
    while (f) {
      if( (f->type != IS_ORPHAN) && (f->type != IS_SUB) ) {
      if( (defaultChannelType == NULL) || (defaultChannelType[0]=='_') ) {
        defaultChannelType="interface{}";
      }  
        char *ftype=defaultChannelType;
        if(    (f->iptype==NULL) 
        		|| (f->iptype[0]==0) ) {
            ftype=defaultChannelType;
        } else {		
        	if(f->iptype[0]=='_') { 
        	   ftype="interface{}";
        } else {
          ftype=f->iptype;
        }}
        if(badType(ftype)) {
        	fprintf(stderr,"%sExported Type from process, %s. ", red, f->source->name ); 
        	FAIL(GenPrefix," is not capitalized");
        }
        f->iptype=ftype;
        f->streamNum=nstream;
        module=fixModule(m, ftype);
	      printf("_ch%d := make(chan %s%s,%i)\t//%s.%d->%s.%d\n",
		    				nstream++,
		    				module, 
		    				ftype,f->bufsz,            
		    				f->source->name,f->SourcePort->id, 
		    				f->sink->name,f->SinkPort->id);
	   }  // End if not orphan 	    
	    f=f->next;
    }
}    

/** Generate Prefix code */
void genPrefix(Model m)
{
    char bfr[maxbfsz]; 

    P(package main);
    printf("\n/*\n"); 
    C(StreamWork Go code. \n\tGenerated by sw/s_wgo.c);
    printf("-%s %s", version, Timestamp());
    printf("\tfrom "); 
    
    printf("Network file: %s/%s\n",
        getcwd(bfr,sizeof(bfr)),
        m->name);  
        
    printf("\tConfiguration file: %s/%s\n",
        getcwd(bfr,sizeof(bfr)),
        configfile);   
    
    showND(m);			/* Show commented ND */
    printf("\n");

    genPaths(m);

    P(func main() {
	);
    PE(} Fixes indent);
    P(var _wg sync.WaitGroup);
    printf("\n");

    MakeChannels(m);
    printf("\n\t_wg.Add(%d)\n", m->nprocs);
}


/** Return rightmost path element */
char *stripPath( char *s1 ) {
	char *s;
	char *s2;
	
	s=s2=s1;
	
	while (*s != 0) {
		if (*s == '/') {
			s2=s+1;
		}
		s++;
	}
	return s2;
	
}

/** print launch process code. */
static void genLaunchComp(Process p)
{
    int i = 1;
    
    printf( "go\t%s.%s(&_wg,",stripPath(p->comp->path),p->comp->name );
    printf("[]string{\"%s\"", p->name);

    if (p->arg) {
			while (p->arg[i]) {
	    	printf(",\"%s\"", p->arg[i]);
	    	i++;
			}
			printf("}"); 
    }
}

#define BSIZE 5001
/* Assign channels to a process
 * Generate a slice when adjacent channels have the same type
*/ 
static void generateChannels(Process p, int nslice) {     
        Port pt;  
	  		char bfr[BSIZE+1];     /* Collect channels  */
	  		char bfr2[BSIZE+1];   
	     
	      
	      pt = p->port; 
	      bfr[0]=0;  
	      
        while(pt != NULL) {
            if(pt->next != p->port 
          			&& strncmp(pt->stream->iptype,
          			     pt->next->stream->iptype,100)==0)
          			{    	 
	        	    snprintf(bfr2,BSIZE,",_cs%d",nslice++);
	        	    strncat(bfr,bfr2,BSIZE);
	        	    while( (strncmp(pt->stream->iptype,
	        	            pt->next->stream->iptype,100)==0)
	        	      && pt->next != p->port) {
	        	    	pt=pt->next;
	        	    }
          	 } else { 
	        	    snprintf(bfr2,BSIZE,",_ch%d",pt->stream->streamNum);
	        	    strncat(bfr,bfr2,BSIZE);
        	   } 
  	      	 pt=pt->next;
        	   if(pt == p->port)
        	   		break;
        }
        
        printf("%s)\n",bfr); 
}  
      
static int generateSlices(Process p, int nslice) {
		Port pt;
		int n = nslice;
		char *ctype;
		char *pkgPath="";
		
		pkgPath=defaultTypePath;
		
		pt = p->port;
		
		if(pt != NULL ) {
		  do {
			  ctype = pt->stream->iptype;
			  if(strncmp(ctype,"interface{}",100) == 0) {
			    pkgPath="";
			  }
			  if(pt->next != p->port 
				   && strncmp(ctype, pt->next->stream->iptype,100) == 0) {
				      printf("\nvar _cs%d []chan %s%s\n", 
				                n, pkgPath,  ctype);
				      do {
				 	  			 printf("_cs%d = append(_cs%d,_ch%d)\n",
				 	  			 		n,n,pt->stream->streamNum);		
				 	  			 pt=pt->next;
				 	  	} while( pt != p->port && 
				 	  			 strncmp(pt->stream->iptype,ctype,MAX_BUF) == 0);
				 	  	n++;
				   }
				if(pt != p->port)   
			  		pt=pt->next;
		  } while(pt != p->port);
		}  
		
		return n;
}
    
/** Launch component goroutines. */
static void genLaunches(Process p)
{
    int nslice=0, lastSlice=0;
    while (p!=NULL) {
	       
	    lastSlice = nslice;
        nslice = generateSlices(p,nslice);
        genLaunchComp(p);
        generateChannels(p,lastSlice);
        p=p->next;
    }
    printf("\n");
}

/** Generate Go language Main package code from SW network model.*/
void genGo(Model model)
{
    Process p;
            
    genPrefix(model);		/* Generate Prefix code */
    p = model->proc;		/* Get first process    */
    genLaunches(p);		/* Expand processes     */
    genSuffix(model->name);		/* Generate Suffix code */
}

/** Generate Expanded Network Definition */
void genND(Model mod)
{
    Stream f;

				/** Generate Prefix code */
    printf("StreamWork Network Definition.  Generated by sw-%s. \n",
	   version);

    f = mod->stream;
    while (f) {
      char *ftype;
      char dash;
      if( f->type==IS_STRUCT ) 
            dash='='; 
      else 
            dash='-';   
      if(f->iptype == NULL || f->iptype[0] == 0) 
            ftype=defaultChannelType;
      else  
            ftype=f->iptype;              
      if( f->type==IS_NET || f->type==IS_STRUCT) {
		if (f->sink->port->id) {
	    		printf("(%s)%d<%s%c%d(%s); \n", f->sink->name,
		   		f->sink->port->id,
		   		ftype, dash,
		   		f->source->port->id,
		   		f->source->name);
		} else {
	    		printf(" (%s)%d<%s%c(%s); \n", f->sink->name,
		   		f->source->port->id, 
		   		ftype, dash, f->source->name);
		}
      }  else  {
	 if( f->type==IS_ORPHAN ) {
		printf("%s;\n",f->source->name);
	 }
      }	
      f = f->next;
    }

}

/***************   End of S_wgO.C   ********************/
