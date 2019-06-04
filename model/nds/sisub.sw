
{# 
'N {
foo <- bar;
};


'M { 
Sub <- Net;
_  'N;
}; 

_ 'M;
_ 'M;
_ 'M;


'T {
(S s)0 <7- 0;
};

(A 'T)0 <- 0(B b);  
# Expand to:  (A-S s)0  <7- 0(B b);

#}

'a {
0 		<7-  (V v);
1 		<6- 1(V v);
W 		<-  X;
};

'b {
1 		<5- (S s);
(T) 	<2-  U;
(T t)1 	<0-  0;
};

(B 'b)	<4-   (A a);
(A)1 	<3-  1(B);
