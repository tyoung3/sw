#!/usr/local/bin/swgraph

# TEE.SW: derived from swedit.sw adding tee function to record trafic.

# SWEDIT is a visual editor for StreamWork networks.

# https://github.com/zserge/lorca
# https://github.com/zserge/webview

{#
Scenario_2: 
    . Record View inputs for later playback 
Scenario_3: 
    . Record View outputs for later testing
#}

$E="swedit";
$base="swedit";

^tee {
(T $E/Tee)1 -> OUT;
IN -> 0(T); 
};

(M ^model)1.Change -> IN(T ^tee)OUT -> Change(V ^view);

^model {
(M $E/Model)1 -> Change;
Request -> 0(M);
(_ $base/Getfile) -Swl> 2(M);
(M)3 -Swl> (_ $base/Putfile);
};


^view {
(V $E/View)2 -> Event;
Change -> 0(V);
Update -> 1(V);
};


^control {
(C $E/Control)2 -> Update;
Event -> 0(C);
(C)1 -> Request;
};

_ ^model;
_ ^view; 
_ ^control;
