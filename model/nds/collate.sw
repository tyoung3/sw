# COLLATE.sw
   
(C std.Collate  )0 	    <- 0(G0  std.Gen1 "1" "2" "12"  );
(C)1  					<- 0(M);         
(M std.Merge)1	     	<- 0(G1  std.Gen1 "5"  "0" "3" );
(M)2				   	<- 0(G2  std.Gen1 "2" "3" "8" );

(Match0 strings.Print1)0 <- 2(C std.Collate  );
(Match1 strings.Print1)0 <- 3(C);
(Miss0  strings.Print1)0 <- 4(C);
(Miss1  strings.Print1)0 <- 5(C);

# End of COLLATE.sw

