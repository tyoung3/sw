#!/usr/local/bin/swgo

# COLLATE.SW: Streamwork Network Definition Example

# WARNING: Merge sends output on channel 0(Zero) contrary to convention(channel 1). 

$tip = "You can specify your own attributes plus color, tooltip and other dot attributes.";  

(C sw/swutility/Collate [size="large", fill="lightgreen"]) 
     <1-  (G0  Gen "12" "1" "2" );  
(C [test="yes" ])1	    		<2- 0(M   sw/swutility/Merge);      
(M)2	    		<-  (G1  Gen "5"  "5" "1" );
(M)IN.1		    	< 3-  (G2  Gen "8"  "2" "3" );

(Match0 Print [fillcolor="lightgreen", tooltip=$tip]) 	<- 2(C);
(Match1 Print [fillcolor="lightgreen", tooltip="match1"]) 	<- 3(C);
(Miss0  Print [fillcolor="red", tooltip="MISS!!"])MISS 	<- 4.MISS(C);
(Miss1  Print [tooltip="MISS!!", fillcolor="red"]) 	<- OUT.5(C);   

# End of COLLATE/sw

