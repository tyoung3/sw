{#  SUBNET3.sw
 FAIL: SW/msg: createStream: Type Mismatch for (Eb) -type_A>  and (Eb) -type_N2>
#}
  
######################################################### 
^M5 {
Eb	<type_A 14-	0(B);
Ea	<type_B 15-	0(A); 
};
#####################   N_   ############################ 
^N1 {    
(C)0	<type_N1 2- 	Ea;  
(D)0 	<type_N2 3- 	Eb;
};

#################################iptype_save=iptype_save=########################
(X5 ^N1)0	<type_D- 0(Y5 ^M5);
(X5)1 		<type_C- 1(Y5);

#################   The End   ###########################
