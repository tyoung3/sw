/** @file swgraph.c
		  Generate Graphviz input(.dot file)  	  
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"
#include "sw.h"
#include "swconfig.h"       
#include <unistd.h>


/** @todo Declutter option
    @todo Config file color palette option
    @toeo Config file .dot parameters
*/

#define P(s) printf("%s\n",(#s));	/**<Print String*/
#define FIXINDENT(s) {};		/**<Nullify FIXINDENT */
#define C(s) printf("%s,\n",(#s));	/**<Print String*/

/* Process colors in graph */  
String fcolors[]={"lightblue", "gold", "red", "orange",  "yellow", "lightgreen",  "violet",  "brown", "gray", "white"}; 

/** Type of Component name */
typedef enum { NOCOMP, COMPNAME, WITHPATH } SHOWC;
static SHOWC showcomp = COMPNAME; /**<??*/
static char *twoline = "";	  /**<??*/

/** Find port for id */
static Port findPort (Port pt, int id)
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

  return NULL;	       /** @todo SWGRAPH.C: error message on error   */
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
      if (f->type == IS_NET || f->type == IS_STRUCT)
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
    ("URL=\"https://github.com/tyoung3/sw\" graph [");
  printf ("\tname=\"Streamwork/swgraph:  v%s\",\n", version);
  C (fontcolor = black);
  printf ("\tlabel=\"https://github.com/tyoung3/sw\",\n");
  P (fontname = "Helvetica");
  printf (",bgcolor=\"gray65\"]");

  // FIXINDENT(\();
  C (node[shape = Mrecord);
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

#undef SHOW_PORTS   // Do not show ports in table format 
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

  snprintf (bfr, sizeof (bfr) - 1, "%s/%s.html", htmldir, comp);   /* htmldir is guaranteed to have a trailing slash('/'). */
  return strndup (bfr, sizeof (bfr) - 1);
}

    /**  EXAMPLE: label="{<P> G1 Gen1 \"xyz\" |{<0> 0 |<1> 1 } }"  */
    
	  // genProc (p->name, p->comp->name, p->comp->path, "taos_", p->arg);
static void genProc1(Process p,  char *host) {
  Attribute attr;
  char **args=p->arg;
  char *comp=p->comp->name;
  char *name=p->name;
  char *path=p->comp->path;
  
  printf ("       \"%s\" ", name);
  printf ("[shape = Mrecord,");
  C (color = "black");
  
  printf ("fillcolor=%s", fcolors[getPathColor(p->comp->path)]);
  
  
  printf ("  URL=\"%s\"\n", makeURL (comp));
  printf (" host=\"%s\" \n", host);
  
  
  printf (" tooltip=\"%s.%s ", path, comp);
  
  genArgs (args);
  printf ("\"\n");
  
  attr=p->attr;
  while(attr != NULL) {
    switch (attr->type) {
    case STRING:
         printf("       %s=\"%s\",\n", attr->key, attr->val.s );
         break;
    case INT:    
         printf("       %s=%d,\n", attr->key, attr->val.i );
         break;
    default:
        badkind(attribute Type);     
    }
    attr = attr->next;
  }
  
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
genCluster1 (char *name, char *filename)
{
  char bfr[maxbfsz];	

  printf ("subgraph \"cluster%s\" %s\n", name, LB);
  printf ("label = \"%s\"; name=\"%s\";\n", name, name);
  printf ("URL=\"%s\";\n\n", filename);
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
char *arrowhead="normal";  // diamond, ediamond, dot, tee, empty, box, open,

    if ( f->type == IS_ORPHAN ) {
        return;
     }
        
#ifdef SHOW_PORTS
  printf("\"%s\":%i -> \"%s\":%i [label=\"%i\"]\",headlabel=\"%.2i\",taillabel=\"%.2i\",tooltip = \"%i[%i]\",arrowhead=\"%s\"];\n", 
     src->name,f->source_id,
     snk->name, f->sink_id, channel, 
        f->sink_id, f->source_id, channel, 
        f->bufsz,arrowhead);
#else
  printf("\"%s\" -> \"%s\"       [label=\"%i]\",  headlabel=\"%.i\",taillabel=\"%i\",	tooltip=\"%i[%i]\",arrowhead=\"%s\"];\n",
     src->name,
     snk->name, channel, f->sink_id, f->source_id, channel, 
        f->bufsz,arrowhead);
#endif
}

static char *addDot(char *n) {
	static char s[100];
	
	
	if(n==NULL) 
		return ".";
		
	strncpy(s,n,99);
	if(n[0] != 0) 
		strncat(s,".",99);
	return strdup(s);
}

static void
genLinks (Model m)
{				// [label="C Miss"];
  Stream f;
  Process src, snk;
  char *srcPortName;
  char *snkPortName;         
  int channel = 7;
  char *edgeColor = "purple";
  char *sourceColor = "pink";
  char *arrowhead="normal"; 
  char *style="solid";  //dashed", "dotted", "solid", "invis" "bold"     "tapered" 
  
  f = m->stream;
  while (f) {
        arrowhead="normal"; style="solid";
    switch (f->type) {
    case IS_STRUCT:
        arrowhead="diamond"; style="tapered";
    case IS_NET:
	  edgeColor = "black";
	  src = f->source;
	  snk = f->sink;
	  sourceColor=fcolors[getPathColor(src->comp->path)];
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
	 	
	  srcPortName=addDot((findPort(src->port, f->source_id)->name));
	  
	  snkPortName=addDot(findPort(snk->port, f->sink_id)->name);	
	  if (f->bufsz < 1000000)  // ? < 2 
	    {
#ifdef SHOW_PORTS
	      printf
		("\"%s\":%i -> \"%s\":%i [color=%s,fontcolor=%s, label=\"%i %s\",headlabel=\"%i\",taillabel=\"%i\",tooltip=\"%i\"];\n",
		src->name, f->source_id, snk->name, f->sink_id,  edgeColor,sourceColor,  channel, f->iptype, f->sink_id, f->source_id,
		   f->bufsz);
#else
	      printf("\"%s\"  -> \"%s\"  [color=%s, fontcolor=%s, label=\"%i %s\",headlabel=\"%s%i\",taillabel=\"%s%i\",tooltip=\"%i\",arrowhead=\"%s\",style=\"%s\"];\n",
		src->name, snk->name, edgeColor, sourceColor, channel, 
		f->iptype, snkPortName, f->sink_id, srcPortName,f->source_id,
		   f->bufsz,arrowhead,style);
#endif
	    }  // End if bfsz
	    break;
	  default:
	      showPorts (f, src, snk, channel);
	}			// End switch on type            
    f = f->next; 		// Get next stream
  }				// End while
}


static void
genProcs (Process p)
{

  while (p)
    {
      if (p->kind == IS_NET || p->kind == IS_STRUCT)
	{
	  printf ("#(%s %s.%s) %d ports\n",
		  p->name,
		  p->comp->path, p->comp->name, p->nportsIn + p->nportsOut);
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
  char dash;  // - OR =     
  
  assignChannels (model);
  //* Generate commented Reconstructed Network Definition */
  printf ("#########   Expanded Network Definition   ######### \n");
  f = model->stream;

  while (f)  {
      dash='-';
      switch (f->type)
	{
	case IS_STRUCT:
	    dash='=';
	case IS_NET:
	  printf ("# (%s %s/%s)%d\t\t<%c %d(%s %s/%s) \n",
		  f->sink->name, f->sink->comp->path,
		  f->sink->comp->name, f->sink_id,
		  dash,
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
  genCluster1 (model->name, model->filename);
  p = model->proc;
  /* Get first process */
  genProcs (p);			/*{ */
  printf ("%s", RB);		/* End Cluster1 */
  genLinks (model);
  genSuffix ();			//* Generate Suffix code */
}

/*    End of SWGRAPH.C  */

/**************************************************   X11  color names  *************************************
aliceblue	antiquewhite	antiquewhite1	antiquewhite2	antiquewhite3
antiquewhite4	aqua	aquamarine	aquamarine1	aquamarine2
aquamarine3	aquamarine4	azure	azure1	azure2
azure3	azure4	beige	bisque	bisque1
bisque2	bisque3	bisque4	black	blanchedalmond
blue	blue1	blue2	blue3	blue4
blueviolet	brown	brown1	brown2	brown3
brown4	burlywood	burlywood1	burlywood2	burlywood3
burlywood4	cadetblue	cadetblue1	cadetblue2	cadetblue3
cadetblue4	chartreuse	chartreuse1	chartreuse2	chartreuse3
chartreuse4	chocolate	chocolate1	chocolate2	chocolate3
chocolate4	coral	coral1	coral2	coral3
coral4	cornflowerblue	cornsilk	cornsilk1	cornsilk2
cornsilk3	cornsilk4	crimson	cyan	cyan1
cyan2	cyan3	cyan4	darkblue	darkcyan
darkgoldenrod	darkgoldenrod1	darkgoldenrod2	darkgoldenrod3	darkgoldenrod4
darkgray	darkgreen	darkgrey	darkkhaki	darkmagenta
darkolivegreen	darkolivegreen1	darkolivegreen2	darkolivegreen3	darkolivegreen4
darkorange	darkorange1	darkorange2	darkorange3	darkorange4
darkorchid	darkorchid1	darkorchid2	darkorchid3	darkorchid4
darkred	darksalmon	darkseagreen	darkseagreen1	darkseagreen2
darkseagreen3	darkseagreen4	darkslateblue	darkslategray	darkslategray1
darkslategray2	darkslategray3	darkslategray4	darkslategrey	darkturquoise
darkviolet	deeppink	deeppink1	deeppink2	deeppink3
deeppink4	deepskyblue	deepskyblue1	deepskyblue2	deepskyblue3
deepskyblue4	dimgray	dimgrey	dodgerblue	dodgerblue1
dodgerblue2	dodgerblue3	dodgerblue4	firebrick	firebrick1
firebrick2	firebrick3	firebrick4	floralwhite	forestgreen
fuchsia	gainsboro	ghostwhite	gold	gold1
gold2	gold3	gold4	goldenrod	goldenrod1
goldenrod2	goldenrod3	goldenrod4	gray	gray0
gray1	gray10	gray100	gray11	gray12
gray13	gray14	gray15	gray16	gray17
gray18	gray19	gray2	gray20	gray21
gray22	gray23	gray24	gray25	gray26
gray27	gray28	gray29	gray3	gray30
gray31	gray32	gray33	gray34	gray35
gray36	gray37	gray38	gray39	gray4
gray40	gray41	gray42	gray43	gray44
gray45	gray46	gray47	gray48	gray49
gray5	gray50	gray51	gray52	gray53
gray54	gray55	gray56	gray57	gray58
gray59	gray6	gray60	gray61	gray62
gray63	gray64	gray65	gray66	gray67
gray68	gray69	gray7	gray70	gray71
gray72	gray73	gray74	gray75	gray76
gray77	gray78	gray79	gray8	gray80
gray81	gray82	gray83	gray84	gray85
gray86	gray87	gray88	gray89	gray9
gray90	gray91	gray92	gray93	gray94
gray95	gray96	gray97	gray98	gray99
green	green1	green2	green3	green4
greenyellow	grey	grey0	grey1	grey10
grey100	grey11	grey12	grey13	grey14
grey15	grey16	grey17	grey18	grey19
grey2	grey20	grey21	grey22	grey23
grey24	grey25	grey26	grey27	grey28
grey29	grey3	grey30	grey31	grey32
grey33	grey34	grey35	grey36	grey37
grey38	grey39	grey4	grey40	grey41
grey42	grey43	grey44	grey45	grey46
grey47	grey48	grey49	grey5	grey50
grey51	grey52	grey53	grey54	grey55
grey56	grey57	grey58	grey59	grey6
grey60	grey61	grey62	grey63	grey64
grey65	grey66	grey67	grey68	grey69
grey7	grey70	grey71	grey72	grey73
grey74	grey75	grey76	grey77	grey78
grey79	grey8	grey80	grey81	grey82
grey83	grey84	grey85	grey86	grey87
grey88	grey89	grey9	grey90	grey91
grey92	grey93	grey94	grey95	grey96
grey97	grey98	grey99	honeydew	honeydew1
honeydew2	honeydew3	honeydew4	hotpink	hotpink1
hotpink2	hotpink3	hotpink4	indianred	indianred1
indianred2	indianred3	indianred4	indigo	invis
ivory	ivory1	ivory2	ivory3	ivory4
khaki	khaki1	khaki2	khaki3	khaki4
lavender	lavenderblush	lavenderblush1	lavenderblush2	lavenderblush3
lavenderblush4	lawngreen	lemonchiffon	lemonchiffon1	lemonchiffon2
lemonchiffon3	lemonchiffon4	lightblue	lightblue1	lightblue2
lightblue3	lightblue4	lightcoral	lightcyan	lightcyan1
lightcyan2	lightcyan3	lightcyan4	lightgoldenrod	lightgoldenrod1
lightgoldenrod2	lightgoldenrod3	lightgoldenrod4	lightgoldenrodyellow	lightgray
lightgreen	lightgrey	lightpink	lightpink1	lightpink2
lightpink3	lightpink4	lightsalmon	lightsalmon1	lightsalmon2
lightsalmon3	lightsalmon4	lightseagreen	lightskyblue	lightskyblue1
lightskyblue2	lightskyblue3	lightskyblue4	lightslateblue	lightslategray
lightslategrey	lightsteelblue	lightsteelblue1	lightsteelblue2	lightsteelblue3
lightsteelblue4	lightyellow	lightyellow1	lightyellow2	lightyellow3
lightyellow4	lime	limegreen	linen	magenta
magenta1	magenta2	magenta3	magenta4	maroon
maroon1	maroon2	maroon3	maroon4	mediumaquamarine
mediumblue	mediumorchid	mediumorchid1	mediumorchid2	mediumorchid3
mediumorchid4	mediumpurple	mediumpurple1	mediumpurple2	mediumpurple3
mediumpurple4	mediumseagreen	mediumslateblue	mediumspringgreen	mediumturquoise
mediumvioletred	midnightblue	mintcream	mistyrose	mistyrose1
mistyrose2	mistyrose3	mistyrose4	moccasin	navajowhite
navajowhite1	navajowhite2	navajowhite3	navajowhite4	navy
navyblue	none	oldlace	olive	olivedrab
olivedrab1	olivedrab2	olivedrab3	olivedrab4	orange
orange1	orange2	orange3	orange4	orangered
orangered1	orangered2	orangered3	orangered4	orchid
orchid1	orchid2	orchid3	orchid4	palegoldenrod
palegreen	palegreen1	palegreen2	palegreen3	palegreen4
paleturquoise	paleturquoise1	paleturquoise2	paleturquoise3	paleturquoise4
palevioletred	palevioletred1	palevioletred2	palevioletred3	palevioletred4
papayawhip	peachpuff	peachpuff1	peachpuff2	peachpuff3
peachpuff4	peru	pink	pink1	pink2
pink3	pink4	plum	plum1	plum2
plum3	plum4	powderblue	purple	purple1
purple2	purple3	purple4	rebeccapurple	red
red1	red2	red3	red4	rosybrown
rosybrown1	rosybrown2	rosybrown3	rosybrown4	royalblue
royalblue1	royalblue2	royalblue3	royalblue4	saddlebrown
salmon	salmon1	salmon2	salmon3	salmon4
sandybrown	seagreen	seagreen1	seagreen2	seagreen3
seagreen4	seashell	seashell1	seashell2	seashell3
seashell4	sienna	sienna1	sienna2	sienna3
sienna4	silver	skyblue	skyblue1	skyblue2
skyblue3	skyblue4	slateblue	slateblue1	slateblue2
slateblue3	slateblue4	slategray	slategray1	slategray2
slategray3	slategray4	slategrey	snow	snow1
snow2	snow3	snow4	springgreen	springgreen1
springgreen2	springgreen3	springgreen4	steelblue	steelblue1
steelblue2	steelblue3	steelblue4	tan	tan1
tan2	tan3	tan4	teal	thistle
thistle1	thistle2	thistle3	thistle4	tomato
tomato1	tomato2	tomato3	tomato4	transparent
turquoise	turquoise1	turquoise2	turquoise3	turquoise4
violet	violetred	violetred1	violetred2	violetred3
violetred4	webgray	webgreen	webgrey	webmaroon
webpurple	wheat	wheat1	wheat2	wheat3
wheat4	white	whitesmoke	x11gray	x11green
x11grey	x11maroon	x11purple	yellow	yellow1
yellow2

**************************************************************************/
