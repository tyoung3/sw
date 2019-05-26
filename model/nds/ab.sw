{#
    AB.sw

#}

(B "a1" "a2" )     <-  OUT(D);
(A strings.Print1) <- 1.OK(B strings.Gen1 "1" "2" "3" ); 
(C strings.Print1) <- OUT.1(D strings.Gen1 "2"); 
(E strings.Print1 "S1" "S2" "S3")0.IN <- OUT(F strings.Gen1 "3" "7"); 

