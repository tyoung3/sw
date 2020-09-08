{#
    AB.sw

#}

(A strings.Print1)SLOT 	<- 0.TAB(B strings.Gen1 "1" "2" "3"  $_BROWSER ); 
(C strings.Print1)IN 	<- OUT.0(D strings.Gen1 "2"); 
(E strings.Print1 "S1" "S2" "S3")0.IN <- OUT.0(F strings.Gen1 "3" "7"); 

(X1 a)0.SOCKET  <- PLUG.0(Y1 b); 
(X2 a)0.SLOT    <- TAB.0(Y2 b);

	 # This fails: (X3 a)TAB    <- TAB(Y3 b); 
