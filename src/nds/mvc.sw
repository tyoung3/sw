#!/usr/local/bin/swgraph

# MVC.SW:  Streamwork Network Definition Example
 
(m  mdl/Model)1  	-change>  	 (v vw/View);
(c)2  		-update> 	1(v);
(v)2		-event 1>  	 (c ctl/Control); 
(c)1		-request 2>       (m);

