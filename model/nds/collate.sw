# COLLATE.sw
   
(C std.Collate  ) 	    <1000-  (G0  std.Gen1 "12" "1" "2" );
(C)1  					<1000-  (M);         
(M std.Merge)1	    	<- 		(G1  std.Gen1 "5"  "5" "1" );
(M)IN.2				   	<- 		(G2  std.Gen1 "8"  "2" "3" );

(Match0 strings.Print1) <10- 2(C std.Collate  );
(Match1 strings.Print1) <10- 3(C);
(Miss0  strings.Print1)MISS <10- 4.MISS(C);
(Miss1  strings.Print1) <10- OUT.5(C);

# End of COLLATE.sw

