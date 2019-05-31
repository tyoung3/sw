#Subnets M and N

M { 0(R r) <- (S s)1; };

N {    
0    <- 1(C); 
1	 <- 0(C sub.M); 
(A)1 <- 2; 
(A a)<- 3;  

(A)3 <- (B  sub.M);
(D d)<- 1(B);     
(A)2 <- 2(C); 
};

(X N)<- 1(Y sub.N);
(X)1 <- 2(Y);
(Y)2 <- 3(X);
(Y)4 <- 0(X);
