# COLLATE.sw
   
(C poc.Collate) 	    <-      (G0  poc.Gen1 "12" "1" "2" );
(C)1  					<1000-  (M);         
(M poc.Merge)1	    	<- 		(G1  poc.Gen1 "5"  "5" "1" );
(M)IN.2				   	<- 		(G2  poc.Gen1 "8"  "2" "3" );

(Match0 poc.Print1) <10- 2(C poc.Collate  );
(Match1 poc.Print1) <10- 3(C);
(Miss0  poc.Print1)MISS <10- 4.MISS(C);
(Miss1  poc.Print1) <10- OUT.5(C);

# End of COLLATE.sw

