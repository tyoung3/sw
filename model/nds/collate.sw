# COLLATE.sw
   
(C std.Collate  )0 	    <1- 0(G0  std.Gen1 "12" "1" "2" );
(C)1  					<2- 0(M);         
(M std.Merge)1	     	<3- 0(G1  std.Gen1 "5"  "5" "1" );
(M)2				   	<4- 0(G2  std.Gen1 "8"  "2" "3" );

(Match0 strings.Print1)0 <5- 2(C std.Collate  );
(Match1 strings.Print1)0 <6- 3(C);
(Miss0  strings.Print1)0 <7- 4(C);
(Miss1  strings.Print1)0 <8- 5(C);

# End of COLLATE.sw

