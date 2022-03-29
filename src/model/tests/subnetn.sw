# Recursive subnet -- experimental.  Causes segfault.



^s3 {
  0 -> (E);
  (C3)->(Level3);
};

^s2 {
  0 -> (D ^s3);
  (C2)->(Level2);
};

^s1 {
  0 -> a.0(S2 ^s2);  
  (C1)->(Level1);    
};

(A Gen) -> a.0(B ^s1);
