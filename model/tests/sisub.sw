'w {
0  	<15- (F f);
(F f)1  <13-   (G g);
(G g)1  <14-   (H  h);
};


'v {
0       <11-   (E 'w);
};


'u {
0       <12-   (D 'v);
};

'a {
(Y)0	<1- 1;
0 	<2-  (V v);
(V)1    <10- 1(W w);
(W)     <3-  (X);
};

'b {
1	<4-  1(S s);
(S)0	<9-  1(T);
(T)2 	<5-  (U 'u);
(T t)0  <6-  0;
};
#(_b_T def.t )0 		<7- 0(_a_V def.v);  #S.B.
#(_a_Y def.Print1 )0 		<7- 0(_a_V def.v);	
#(_b_T def.t )2 		<15- 0(_b_U_D_E_F def.f);
#(_b_T def.t )2 		<15- 0(_b_U_D_E_F def.f);  #S.B.	

{#
(_a_V def.v )1 		<10- 1(_a_W def.w);	
(_a_W def.w )0 		<3- 0(_a_X def.Gen1);	
(_b_U_D_E_F def.f )1 		<13- 0(_b_U_D_E_G def.g);	
(_b_U_D_E_G def.g )1 		<14- 0(_b_U_D_E_H def.h);	
(_b_S def.s )0 		<9- 1(_b_T def.t);	
(_b_T def.t )2 		<15- 0(_b_U_D_E_F def.f);	
((null) '.a )1 		<8- 1(_b_S def.s);	
(_a_Y def.Print1 )0 		<7- 0(_a_V def.v);	
#}

(_ 'b)0	<1-  0(_ 'a);
(_ 'a)1 <2-  1(_ 'b);
