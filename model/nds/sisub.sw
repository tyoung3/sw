
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
0 <7- (_ v);
W <- X;
};

'b {
0 <5- (S s);
T <- U;
};

(A 'a) <4-  (B 'b);

