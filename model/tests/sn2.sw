{#Subnets M and N

#}

^M { 
0     	<- 0(B);
1	<- 0(C);
2	<- 1(C);
};

^N {     
(A) 	<- 0;
(A)1 	<- 1; 
(A)2 	<- 2; 
};

(X ^N)0 <- 0(Y ^M);
(X ^N)1 <- 1(Y ^M);
(X ^N)2 <- 2(Y ^M);

