#!/usr/local/bin/swgo

# LOCUSTS.SW:  Streamwork Network Definition Example

# Ref: https://www/cicadamania/com/where/html

#   (Brood X Magicicada periodical cicadas[locusts]) appearing two years early in DC and Cincinnati 
#   (Brood VIII Magicicada periodical cicadas[locusts]) predicted for Ohio and Pennsylvania 

#          914 + 13*A = 2019 = 914 + 17*B  = 914 + 221*A/17   

#              Partition I 
# Broods IV and XIX in Missouri in 2019   ?
(C  sw/swutility/Collate  )0 	  <- 0(IV_MO   Gen "108" "910" "17" );
(C)1 	     	    		  <- 0(XIX_MO   Gen "140" "919" "13" );

(MISSOURI_IV Print) <0- 2(C);
(MO_XIX      Print) <0- 3(C);
(MISS_IV     Print) <0- 4(C);
(MISS_XIX    Print) <0- 5(C);

#              Partition II 
(C2 sw/swutility/Collate  )0 		 <- 0(X_WASH   Gen "108" "916" "17" );
(C2)1 	     	          	 <- 0(XIX2_MO  Gen "140" "919" "13" );

(WASH_X      Print) <- 2(C2);
(MATCH_XIX_2 Print) <- 3(C2);
(MISS_X      Print) <- 4(C2);
(MISS_XIX_2  Print) <- 5(C2);
  
#              Partition III     Broods IV and XIX in Missouri in 2019 ?
(C3 sw/swutility/Collate)0 	 		 <- 0(QQ        Gen "140" "914" "13" );
(C3)1	 	 		 <- 0(VIII_OHIO Gen "108" "914" "17" );

(OHIO_VIII Print) <- 2(C3);
(MATCH_QQ  Print)  <- 3(C3);
(MISS_VIII Print) <- 4(C3);
(MISS_QQ   Print)  <- 5(C3);
  
# End of LOCUSTS.sw

