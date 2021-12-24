#!/usr/local/bin/swgraph

# SWEDIT is a visual editor for StreamWork networks.

# https://github.com/zserge/lorca
# https://github.com/zserge/webview

{#
Scenario_1: 
        USER					  BROWSER
        ----					----------
  * Run swedit myapp			. Displays myapp.sw graph 
  * Right click on BG			. Displays action menu
  * Right click on process		. Displays process action menu
  * Drag from process to process	. Creates a new stream 
  * Drag from process to BG		. Creates a new external port

#}

$E="github.com/tyoung3/swedit";
$base =  "FileIoBase";

^model {
(M $E/model)CHANGE.1 -> 1;
0 -> REQ.0(M);
(N $base/getfile) -nd> ND.2(M);
(M)ND.3 -nd> (P $base/putfile);
};


^view {
(V $E/view)EVENT.2 -> 2;
0 -> CHANGE.0(V);
1->  UPDATE.1(V);
};


^control {
(C $E/control)UPDATE.2 -> 2;
0 -> EVENT.0(C);
(C)REQ.1 -> 1;
};

(m  ^model)CHANGE.1  	-change>  	 (v ^view);
(c)2  		-update> 	1(v);
(v)2		-event >  	 (c ^control); 
(c)1		-request>       (m);

