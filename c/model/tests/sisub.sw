^w {
0      <15-  1(F F);
(F F)  <13-  1(G G);
(G G)  <14-   (H  H);
};


^v {
0       <11-   (E ^w);
};


^u {
0       <12-   (D ^v);
};

^a {
(Y) 	<1- 0;
1 	<2-  1(V V);
(V)     <10- 1(W W);
(W)     <3-  (X);
};

^b {
1	<4-  1(S S);
(S)0	<9-  2(T);
(T)1 	<5-  (U ^u);
(T T)0  <6-  0;
};

(b ^b)	<1- 1(a ^a);
(a ^a)  <2-  1(b ^b);



##########################   The rest is commentary   #############################
#(_b_T def/T )0 		<7- 0(_a_V def/V);  #S/B/
#(_a_Y def/Print1 )0 		<7- 0(_a_V     );	
#(_b_T       )2 		<15- 0(_b_U_D_E_F def/F);
#(_b_T       )2 		<15- 0(_b_U_D_E_F );  #S/B/	

{#
(_a_V def/V )1 		<10- 1(_a_W def/W);	
(_a_W def/W )0 		<3- 0(_a_X def/Gen1);	
(_b_U_D_E_F def/F )1 		<13- 0(_b_U_D_E_G def/G);	
(_b_U_D_E_G def/G )1 		<14- 0(_b_U_D_E_H def/H);	
(_b_S def/S )0 		<9- 1(_b_T def/T);	
(_b_T def/T )2 		<15- 0(_b_U_D_E_F def/F);	
((null) '/a )1 		<8- 1(_b_S def/S);	
(_a_Y def/Print1 )0 		<7- 0(_a_V def/V);	
#}

