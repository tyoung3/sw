# StreamWork Design Guidelines
  

## GO Design Guidelines

	* Begin component with defer _wg.Done(). 
	* defer Close(CHANNEL) for all output channels.
	* Do not close input channels. 
  * Separate concerns
   	* GUI, business logic, DB,  etc. should not be intermixed. 
   	* Try to make the business logic clear to the business experts and easily modifiable.  
   	  Use decision tables, graphs, etc.
  * Use the GO init() function.  The init() function in all
    processes will execute, in parallel, prior to any main function.
    For instance, one process could set the DEBUG variable on within 
    its init() function, causing
    all processes to continue in DEBUG mode.   	  
  * Simple interfaces
    * Avoid global variables.  Ensure components are re-entrant.  
  	* Limit each channel to one type of data.  Pass a structure, 
  	  instead of multiple data elements.  
  	  Pass structures or handles, rather than pointers.  
  	  A data tree can be passed in abstract syntax form, then
  	  reconstructed on receipt. 
  	* Strive for less than four channels per component, 
  	  splitting into multiple components if necessary.   
  	  Exception:  same IP type on multiple channels, as in merging.    
  	* Don't over simplify and create too many fine-grained processes.
 	  * Use simple URI rules [URI Rules](https://dzone.com/articles/7-rules-for-rest-api-uri-design-1)
    * Don't buffer unnecessarily.   Zero-length buffers are a bit more secure and minimize latency.  
  	 In some cases, particularly in cyclic networks, however, non-zero buffers may be 
  	 necessary to prevent deadlock.  Non-zero buffers may also speed processing sometimes. 
  	 Note that Go uses ring buffers, implying that IPs can be received even when the buffer 
  	 is not full.  Buffers can be useful when input arrives erratically.  
  	  
  	 
  * Security and synchronization
  
 	* Always defer synchronizing waits to help prevent deadlock 
 	  and zombies.
    * Avoid threats  (see [Go security practices](https://blog.sqreen.com/top-6-security-best-practices-for-go/) )
  	* Validate input entries
  	* Use HTML templates to help avoid cross site script(CSS) attacks
  	* Prevent SQL injections
  	* Encrypt sensitive data
  	* Use HTTPS, not http
  	* Use logs and error messages carefully, being sure to avoid leaking sensitive data. (5,000 secrets/day are leaked to GitHub, it has been claimed.)
  * Document at the component, subnet, and package levels.   
  * Test at the component and package levels. 

## StreamWork Features

StreamWork: 

  * does not complicate debugging with subnet logic.  Subnets are purely
    design aids.
  * does not process or examine IPs; it merely creates a channel for every stream, assigning the channels to the sending and receiving components;
  * has a number of rules for automatically connecting ports according to their names and modes(sink or source)
     * Matches (upper and lower case port names) 'OUT' to 'IN'; 
       'TAB' to 'SLOT'; and 'PLUG' to 'SOCKET'.  
     * Also matches output ports to input ports with the same name.     
  * implements a text based, context free, program language agnostic, network definition language, SWL;
  * produces pure Go code with no dependencies other than those required by the components themselves; 
   (The generated code, should run on any platform Go supports. Non-standard components may contain OS dependent code, however.)  
  * Component behavior can be controlled via arguments, environment
variables, in-stream commands, ordinary IPs, and signals. 
  * Each process runs as an independent Go routine.  Components are free
    to launch and synchonize Go routines of their own. 


