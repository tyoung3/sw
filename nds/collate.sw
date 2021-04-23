# COLLATE.sw
# WARNING: pocMerge sends output on channel 0(Zero) contrary to convention. 
#          This will cause collate to deadlock if sw.sh p .../collate.sw
#	   is run.
 
(C swutility/Collate) 	<1-  (G0  Gen "12" "1" "2" );  
(C)1	    		<2- 0(M   swutility/Merge);      
(M)2	    		<int-  (G1  Gen "5"  "5" "1" );
(M)IN.1		    	<int 3-  (G2  Gen "8"  "2" "3" );

(Match0 Print) 	<int- 2(C);
(Match1 Print) 	<int- 3(C);
(Miss0  Print)MISS 	<int- 4.MISS(C);
(Miss1  Print) 	<int- OUT.5(C);   

# End of COLLATE/sw

