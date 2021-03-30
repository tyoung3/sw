# COLLATE.sw
 
(C)1	    		<1- (M   poc.Merge);       
(C poc.Collate) 	<1- (G0  poc.Gen1 "12" "1" "2" );    
(M)2	    		<1- (G1  poc.Gen1 "5"  "5" "1" );
(M)IN.1		    	<1- (G2  poc.Gen1 "8"  "2" "3" );

(Match0 poc.Print1) 	<1- 2(C poc.Collate  );
(Match1 poc.Print1) 	<1- 3(C);
(Miss0  poc.Print1)MISS <1- 4.MISS(C);
(Miss1  poc.Print1) 	<1- OUT.5(C);

# End of COLLATE.sw

