# COLLATE2.sw
 
(C)1  					<-     2(M poc.Collate "--merge");       
(C poc.Collate) 	    <-      (G0  poc.Gen1 "12" "1" "2" );    
(M)0	    			<- 		(G1  poc.Gen1 "5"  "5" "1" );
(M)IN.1				   	<- 		(G2  poc.Gen1 "8"  "2" "3" );

(Match0 poc.Print1) <10- 2(C poc.Collate  );
(Match1 poc.Print1) <10- 3(C);
(Miss0  poc.Print1)MISS <10- 4.MISS(C);
(Miss1  poc.Print1) <10- OUT.5(C);

# End of COLLATE2.sw

