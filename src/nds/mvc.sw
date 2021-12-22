#!/usr/local/bin/swgraph

# MVC.SW:  Streamwork Network Definition Example
 
(m  Model)1  	-change>  	 (v mvc/View);
(c)2  		-update> 	1(v);
(v)2		-event>  	 (c mvc/Control); 
(c)1		-request>       (m);

