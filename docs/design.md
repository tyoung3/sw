# StreamWork Design Guidelines
  

## GO Design Guidelines

  * Separate concerns
   	* GUI, business logic, DB,  etc. should not be intermixed. 
   	* Try to make the business logic clear to the business experts and easily modifiable.  
   	  Use decision tables, graphs, etc.
  * Do not avoid the GO init() function.  The init() function in all
    processes will execute, in parallel, prior to any main function.
    For instance, one process could set the DEBUG variable on within 
    its init() function, causing
    all processes to continue in DEBUG mode.   	  
  * Simple interfaces
    * Avoid global variables.  Ensure components are re-entrant.  
      Internal state data should be contained in IPs. 
  	* Limit each channel to one type of data.  Pass a structure, 
  	  not multiple data elements.  
  	  Pass structures or handles, not pointers.  Any data tree can 
  	  be passed in abstract syntax form. 
  	* Strive for less than four channels per component, 
  	  splitting into multiple components if necessary.   
  	  Exception:  same IP type on multiple channels.     
  	* Don't over simplify and create too many fine-grained processes.
 	* Use simple URI rules [URI Rules](https://dzone.com/articles/7-rules-for-rest-api-uri-design-1)
  * Don't buffer unnecessarily.   Zero-length buffers minimize latency.
  * Security and synchronization
 	* Alway defer synchronizing waits to help prevent deadlock 
 	  and zombies.
    * Avoid threats  (see [Go security practices](https://blog.sqreen.com/top-6-security-best-practices-for-go/) )
  	* Validate input entries
  	* Use HTML templates to help avoid cross site script(CSS) attacks
  	* Prevent SQL injections
  	* Encrypt sensitive data
  	* Use HTTPS, not http
  	* Use logs and error messages carefully, being sure to avoid leaking sensitive data.
  * Document at the component, subnet, and package levels.   
  * Test at the component and package levels. 

## StreamWork Features

StreamWork: 

  * does not process IPs; it merely creates and assigns channels to the sending and receiving components;
  * has a number of rules for automatically connecting ports according to their names and modes(sink or source)<!-- ?? show rules -->;  
  * implements a text based, context free, program language agnostic, network definition language, SWL;
  * produces pure GO code with no dependencies other than those required by the components themselves; 
   (The generated code, and supplied components, should run on any platform GO supports;)  
  * Component behavior can be controlled via arguments, environment
variables, in-stream commands, ordinary IPs, and signals. 
  * Each process runs as an independent Go routine.  Components are free
    to launch and synchonize Go routines of their own. 


