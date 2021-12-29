#!/usr/local/bin/swgraph

# SWEDIT.SW

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
$E="/usr/local/src/swedit";
$base="/usr/local/src/swedit/FileIoBase";

^model {
(M $E/model)1 -> Change;
Request -> 0(M);
(_ $base/getfile) -Swl> 2(M);
(M)3 -Swl> (_ $base/putfile);
};

^view {
(V $E/view)2 -> Event;
Change -> 0(V);
Update -> 1(V);
};


^control {
(C $E/control)2 -> Update;
Event -> 0(C);
(C)1 -> Request;
};

_ ^model;
_ ^view; 
_ ^control;
