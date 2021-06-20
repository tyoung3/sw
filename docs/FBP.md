[FBP tenets https://jpaulm.github.io/fbp](https://jpaulm.github.io/fbp)

 * If work is boring, let a robot do it!
 	* Corollary: using a design tool should be fun!
 * No one language should try to do everything!
 * The world is asynchronous - don't try to force the systems we build into a synchronous framework!
 * The von Neumann paradigm is only appropriate within a single process! Duh!
 * Any language or system that "talks data" should be able to talk to any other one that "talks data".
 * A process needs to be able to have more than one input port, and needs to be able to choose which one to receive from!
 * If a process's upstream connection fills up, the process feeding it will be suspended (unless the connection is marked "DropOldest") ("back pressure")

Temporal
--------

https://docs.temporal.io/docs/go-run-your-first-app/

APIs
====

APIs are typically implemented via function calls, as stated in 
(https://www.altexsoft.com/blog/engineering/what-is-api-definition-types-specifications-documentation/).  
I suggest most APIs would be better implemented by FBP.   


(https://www.mckinsey.com/business-functions/mckinsey-digital/our-insights/the-seven-make-or-break-api-challenges-cios-need-to-address#)
(https://thenewstack.io/the-exploding-endpoint-problem-why-everything-must-become-an-api/)
The discovery, access, interface, and format of APIs are not standardized leading to fragmentation of programming languages, frameworks and developer consumption models such as containers and serverless as a way to deal with complexity. 

An existing functional API can be incorporated into a FBP component which interacts via one or more structures.   The component can thus 
simplify and tailor the functional API rules into a more standard API information packet.  When several, diverse functional APIs are required to carry out a particular operation, it may be possible to subnet the whole thing into one FBP process with a standard interface.  

Functional APIs, particulary web-based APIs with their inherent delays, would benefit immediately from FBP's inherent concurrency.    

API Info
--------

[API2Cart](htps://api2cart.com/business/6-difficulties-api-integration-way-avoid/)
(http://sigdoc.acm.org/cdq/how-developers-use-api-documentation-an-observation-study/)
(http://www.cs.cmu.edu/~cscaffid/old/papers/pr_20060601_api.pdf)
(https://www.cs.mcgill.ca/~martin/papers/software2009a.pdf)
(https://link.springer.com/content/pdf/10.1007%2F978-3-642-34347-6_10.pdf)
(https://arxiv.org/pdf/1705.06586.pdf)
(https://www.testingxperts.com/blog/Top-4-Challenges-of-API-Testing-and-How-to-Overcome-Them)
(https://www.healthit.gov/topic/patient-access-to-medical-records/learning-module-apis-and-health-data-sharing)

(https://stackoverflow.blog/2020/11/23/the-macro-problem-with-microservices/)
	(https://github.com/temporalio/temporal)
	
Design Guidelines
-----------------

  * Separate concerns
   	* GUI, business logic, DB,  etc. should not be intermixed. 
   	* Try to make the business logic clear to the business experts and easily modifiable.  Use decision tables, graphs, etc.
  * Simple interfaces
  	* Limit each channel to one type of data.  Pass a structure, not multiple data elements.  Pass handles, not pointers.
  	* Strive for less than four channels per process.   Exceptions:  same IP type on multiple channels.  Split the process up
	  if possible.    
    	* Don't over simplify and create too many processes.
    	* Don't buffer unnecessarily.   
    	* [URI Rules](https://dzone.com/articles/7-rules-for-rest-api-uri-design-1)
  * Document at the component, subnet, and package levels.   
  * Test at the component and package levels.  	
    	
  	  
  	  	
   	
   	
