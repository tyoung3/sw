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

# $E="github.com/tyoung3/sw/swedit";
# $base="github.com/tyoung3/sw/swedit/FileIoBase";
$E="/usr/src/swedit";
$base="/usr/src/swedit/FileIoBase";

^model {
(M $E/model)1 -change> CHANGE;
REQ -req> 0(M);
(_ $base/getfile) -nd> 2(M);
(M)3 -nd> (_ $base/putfile);
};

^view {
(V $E/view)2 -event> EVENT;
CHANGE -change> 0(V);
UPDATE -update> 1(V);
};


^control {
(C $E/control)2 -update> UPDATE;
EVENT -event> 0(C);
(C)1 -req> REQ;
};

_ ^model;
_ ^view; 
_ ^control;
