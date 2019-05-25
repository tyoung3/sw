# LOCUSTS.sw

# Broods IV and XIX in Missouri in 2019   
# G17 (Brood VIII Magicicada periodical cicadas[locusts]) predicted for Ohio and Pennsylvania   

(C std.Collate  )0 	    <- 0(IV    std.Gen1 "54" "2002" "17" );
(C)1 	     	        <- 0(XIX   std.Gen1 "70" "2006" "13" );

(Match_IV  strings.Print1)0 <- 2(C std.Collate  );
(Match_XIX strings.Print1)0 <- 3(C);
(Miss_IV   strings.Print1)0 <- 4(C);
(Miss_XIX  strings.Print1)0 <- 5(C);

# End of LOCUSTS.sw

