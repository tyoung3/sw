# LOCUSTS.sw


#              Partition I 
# Broods IV and XIX in Missouri in 2019   
(C std.Collate  )0 	<- 0(IV_MO    std.Gen1 "108" "914" "17" );
(C)1 	     	    <- 0(XIX_MO   std.Gen1 "140" "914" "13" );
(MISSOURI_IV  strings.Print1)0 <- 2(C std.Collate  );
(Match_XIX strings.Print1)0 <- 3(C);
(Miss_IV   strings.Print1)0 <- 4(C);
(Miss_XIX  strings.Print1)0 <- 5(C);

#              Partition II 
#    G17-DC (Brood X Magicicada periodical cicadas[locusts]) appearing two years early in DC and Cincinnati 
(CDC std.Collate  )0 	<- 0(X_DC    std.Gen1 "108" "912" "17" );

(CDC)1 	     	        <- 0(XIX2_MO std.Gen1 "140" "914" "13" );

(WASHINGTON  strings.Print1)0 <- 2(CDC std.Collate  );
(Match_XIX2 strings.Print1)0 <- 3(CDC);
(Miss_X   strings.Print1)0 <- 4(CDC);
(Miss_XIX2  strings.Print1)0 <- 5(CDC);

#    G17_OHIO (Brood VIII Magicicada periodical cicadas[locusts]) predicted for Ohio and Pennsylvania   
#(C std.Collate  )0 	 <- 0(VIII-OHIO std.Gen1 "108" "914" "17" );

# End of LOCUSTS.sw

