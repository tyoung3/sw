#Subnets M and N

M { 
(S2)1  <100-  1;
0      <- 	1(B2);
(B2 r) <- 	0(S2 s);
};

N {    
0     <- 1(C1); 
1	  <- 0(C1 c1); 
(A1)1 <- 2; 
(A1 a)<- 3;  
(A1)3 <- 0(B1 b1);
(D1 d)<- 1(B1);     
(A1)2 <- 2(C1); 
};

(X  'N)0<- 2(Y 'N);
(X)1 <- 3(Y);
(Y)0 <- 2(X);
(Y)1 <- 3(X);
