#!/usr/local/bin/swgo

$sw="github.com/tyoung3/sw";
(_) -> 0.IN(SWGO $sw/linux/Wrap "./swbal.sw" )STDOUT.1 -> (P);  (SWGO)STDERR.2 -> (P);

