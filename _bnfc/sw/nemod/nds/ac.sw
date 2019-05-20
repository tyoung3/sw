{#
      AC.sw
      
      This file contains semantic errors, but not syntax errors.
      I.e. it will parse successfully, but fail later.
#}

(A strings.Print1)0 <- 0(B strings.Gen1); 
(C strings.Print1)0 <- 0(D strings.Gen1 "2"); 
(E strings.Print1)0 <- 3(F strings.Gen1 "3" "7"); 
(F)2 <- 7(D);
(F "8")2 <- 8(D);
