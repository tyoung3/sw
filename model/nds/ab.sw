{#
    AB.sw

#}

(B "a1" "a2" )     			  <- (D);
(A strings.Print1)SLOT 				  <- 1.TAB(B strings.Gen1 "1" "2" "3" ); 
(C strings.Print1)IN 				  <- OUT.1(D strings.Gen1 "2"); 
(E strings.Print1 "S1" "S2" "S3")0.IN <- OUT.0(F strings.Gen1 "3" "7"); 

