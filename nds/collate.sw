# COLLATE.sw
# WARNING: pocMerge sends output on channel 0(Zero) contrary to convention. 
#          This will cause collate to deadlock if sw.sh p .../collate.sw
#	   is run.
 
(C)1	    		<- 0(M   poc/Merge);       
(C poc/Collate) 	<- (G0  poc/Gen1 "12" "1" "2" );    
(M)2	    		<- (G1  poc/Gen1 "5"  "5" "1" );
(M)IN.1		    	<- (G2  poc/Gen1 "8"  "2" "3" );

(Match0 poc/Print1) 	<- 2(C poc/Collate  );
(Match1 poc/Print1) 	<- 3(C);
(Miss0  poc/Print1)MISS <- 4.MISS(C);
(Miss1  poc/Print1) 	<- OUT.5(C);

# End of COLLATE/sw

