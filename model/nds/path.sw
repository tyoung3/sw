#Pathalogical flows:
(B c.d)4 <- 0(A a.b);
(A a.b)1 <- 3(B c.d);
(A a.b)2 <- 5(B c.d);

(C a.b)0 <- 0(B c.d);
(C a.b)1 <- 7(B c.d);

(B c.d)1 <- 0(D a.b);
(D a.b)1 <- 6(B c.d);
(D a.b)2 <- 2(B c.d);

{#
/* (D a.b)2 <- 2(B c.d) */
/* (D a.b)1 <- 6(B c.d) */
/* (B c.d)1 <- 0(D a.b) */
/* (C a.b)1 <- 7(B c.d) */
/* (C a.b)0 <- 0(B c.d) */
/* (A a.b)2 <- 5(B c.d) */
/* (A a.b)1 <- 3(B c.d) */
/* (B c.d)4 <- 0(A a.b) */

fbp.Launch(&wg, []string{"D"}, a.b, cs2[0:3])
fbp.Launch(&wg, []string{"C"}, a.b, cs1[0:2])
fbp.Launch(&wg, []string{"B"}, c.d, cs0[0:8])
fbp.Launch(&wg, []string{"A"}, a.b, cs3[0:3])

#}