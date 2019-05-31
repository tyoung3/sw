#Subnets M and N

M { 0(R r) <- (S s)1; };

N { 
(A a)0;    /* External port, 0 */
(A)1 <- (B sub.M)1 <- 3;
(D d) <- 1(B);  
1<- 3(C c)2;    
(A)2 <- 0(C)3 <- 4; 
};

(X N)<- 1(Y sub.N);
(X)1 <- 2(Y);
(Y)2 <- 3(X);
(X)3 <- 4(Y);
(X)4 <- 0(Y);
