# Recursive subnet -- experimental.  Causes segfault.


^s2 {
  0 -> (D);
};

^s {
  0 -> a.0(C ^s2);      # Changing ^s to ^s2 works. 
};

(A Gen) -> a.0(B ^s);
