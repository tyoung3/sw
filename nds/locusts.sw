# LOCUSTS.sw

# Ref: https://www.cicadamania.com/where.html

#   (Brood X Magicicada periodical cicadas[locusts]) appearing two years early in DC and Cincinnati 
#   (Brood VIII Magicicada periodical cicadas[locusts]) predicted for Ohio and Pennsylvania 

#          914 + 13*A = 2019 = 914 + 17*B  = 914 + 221*A/17   

#              Partition I 
# Broods IV and XIX in Missouri in 2019   ?
(C std.Collate  )0 			  <- 0(IV_MO    poc.Gen1 "108" "910" "17" );
(C)1 	     	    		  <- 0(XIX_MO   poc.Gen1 "140" "919" "13" );

(MISSOURI_IV poc.Print1) <- 2(C);
(MO_XIX      poc.Print1) <- 3(C);
(MISS_IV     poc.Print1) <- 4(C);
(MISS_XIX    poc.Print1) <- 5(C);

#              Partition II 
(C2 poc.Collate  )0 		 <- 0(X_WASH  poc.Gen1 "108" "916" "17" );
(C2)1 	     	          	 <- 0(XIX2_MO poc.Gen1 "140" "919" "13" );

(WASH_X      poc.Print1) <- 2(C2);
(MATCH_XIX_2 poc.Print1) <- 3(C2);
(MISS_X      poc.Print1) <- 4(C2);
(MISS_XIX_2  poc.Print1) <- 5(C2);
  
#              Partition III     Broods IV and XIX in Missouri in 2019 ?
(C3 poc.Collate)0 	 		 <- 0(QQ        poc.Gen1 "140" "914" "13" );
(C3)1	 	 				 <- 0(VIII_OHIO poc.Gen1 "108" "914" "17" );

(OHIO_VIII poc.Print1) <- 2(C3);
(MATCH_QQ poc.Print1)  <- 3(C3);
(MISS_VIII poc.Print1) <- 4(C3);
(MISS_QQ  poc.Print1)  <- 5(C3);
  
# End of LOCUSTS.sw

