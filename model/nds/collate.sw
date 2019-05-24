# COLLATE.sw

(C std.Collate "x" )0 <- 0(G0  std.Gen1 "3" "4" "4" "5" );
(C)1                  <- 0(G1  std.Gen1 "1" "4" "7");
(Match0 strings.Print1)0 <- 2(C std.Collate "y");
(Match1 strings.Print1)0 <- 3(C);
(Miss0  strings.Print1)0 <- 4(C);
(Miss1  strings.Print1)0 <- 5(C);

# End of COLLATE.sw

