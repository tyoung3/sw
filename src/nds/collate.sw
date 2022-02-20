#!/usr/local/bin/swgo

# COLLATE.SW: Streamwork Network Definition Example

# WARNING: Merge sends output on channel 0(Zero) contrary to convention(channel 1). 

$tip = "<p>You can specify tooltip and other dot attributes plus
other commnents <p>";

(C swutility/Collate ATTRIBUTES { size="large", fill="lightgreen"}) 
     <1-  (G0  Gen "12" "1" "2" );  
(C)1	    		<2- 0(M   swutility/Merge);      
(M)2	    		<int-  (G1  Gen "5"  "5" "1" );
(M)IN.1		    	<int 3-  (G2  Gen "8"  "2" "3" );

(Match0 Print ATTRIBUTES {fillcolor="lightgreen", tooltip=$tip }) 	<int- 2(C);
(Match1 Print ATTRIBUTES {fillcolor="lightgreen", tooltip="match1" }) 	<int- 3(C);
(Miss0  Print ATTRIBUTES {fillcolor="red", tooltip="MISS!!" })MISS 	<int- 4.MISS(C);
(Miss1  Print ATTRIBUTES {tooltip="MISS!!", fillcolor="red"}) 	<int- OUT.5(C);   

# End of COLLATE/sw

