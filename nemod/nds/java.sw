#JAVA.SW

#	  JavaFBP Ex.

# JavaFBP Poc: 

# SUFFIX class;
# INITIAL Read_Masters 		    "c:\\mastfile" SOURCE;
# INITIAL Read_Details  		"c:\\detlfile" SOURCE;   
# INITIAL Write_New_Masters  	"c:\\newmast"  DESTINATION; 
# (Read_Masters Read)OUT 		 =>> IN,0(Collate Collate); 		// array port
# (Read_Details Read)OUT 		 =>> IN,1(Collate); 
# (Collate Proc)OUT 			 =>> IN(Process_Merged_Stream Proc);
# (Process_Merged_Stream)OUTSE =>> IN(Summary_&_Errors Report);
# (Process_Merged_Stream)OUTM  =>> IN(Write_New_Masters);

#        Or equally:
# (P)OUTSE       =>> IN(SE Report);
# (P)OUTM        =>> IN(M  Write);
# (R1 Read)OUT   =>> IN0(C Collate);
# (C)OUT         =>> IN(P  Proc);
# (R2 Read)OUT   =>> IN1(C);
# "c:\\newmast"  =>>    (M);
# "c:\\mastfile" =>>    (R1);
# "c:\\detlfile" =>>    (R2);

#      In Go: 
(C Collate)0   <-  0(R1 Read);
#(P)2    	  <-  1(C);
(SE Report)0   <-  0(P Proc);
#(M  Write)0    <-  1(P);
#(C)2    	   <-  0(R2 Read);

#(M)1  		   <-     "c:\\newmast";
#(R1)1 		   <-     "c:\\mastfile";
#(R2)1 		   <-     "c:\\detlfile";

# connect(component("Read Masters",Read.class),  port("OUT"), 
#	      component("Collate",    Collate.class),port("IN",0));  

#    connect(component("Read Details",Read.class),port("OUT"),
#      component("Collate"),port("IN",1));// array port  
      
#    connect(component("Collate"),port("OUT"),
#      component("Process Merged Stream",Proc.class),port("IN"));  
      
#    connect(component("Process Merged Stream"),port("OUTM"),
#      component("Write New Masters",Write.class),port("IN"));  
      
#    connect(component("Process Merged Stream"),port("OUTSE"),
#      component("Summary & Errors",Report.class),port("IN"));
      

#    initialize(new FileReader("c:\\mastfile"),
#      component("Read Masters"),
#      port("SOURCE"));
      
#     initialize(new FileReader("c:\\detlfile"),
#       component("Read Details"),
#       port("SOURCE"));

#     initialize(new FileWriter("c:\\newmast"),
#       component("Write New Masters"),
#       port("DESTINATION"));

