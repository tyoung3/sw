^a {  
   (A)	<1- IN ;
};  

^b {  
    OUT	<2- (B);
};  


^c {  
    OUT	<3- (B);
};  

^ab {
X ^a; Y ^b; 
};

^ac {
X ^a; Y ^c; 
};

^dummy {
D ^a; E ^c;
};

T ^ab;
U ^ac;
