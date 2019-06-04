
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
(Y v)	<1- 1;
0 		<2- (V v);
W 		<3-  X;
};

'b {
1 		<4- (S s);
(T) 	<5-  U;
(T t)1 	<6-  0;
};

(B 'b)	<7-   (A 'a);
(A)1 	<8-  1(B);
