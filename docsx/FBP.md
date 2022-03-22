# Flow Based Programming Comments             
11/8/2021, 3/17/2022

##  StreamWork (v0.22.1) and 'Classical FBP'

We believe StreamWork is consistent with 'Classical Flow Based Programming'. 

### Wikipedia Definition of FBP

>In computer programming, flow-based programming (FBP) is a programming paradigm that defines applications as networks of "black box" processes, which exchange data across predefined connections by message passing, where the connections are specified externally to the processes. These black box processes can be reconnected endlessly to form different applications without having to be changed internally. FBP is thus naturally component-oriented.

>FBP is a particular form of dataflow programming based on bounded buffers, information packets with defined lifetimes, named ports, and separate definition of connections.

So, to summarize the Wikipedia definition, FBP is charactarized by:

   * Black box processes
   * Separate connection definitions
   * Message(information packet, IP) passing
   * Bounded buffers
   * IPs with defined lifetimes
   * Named Ports

Wikipedia does not mention concurrency -- in error, we maintain.  
Wikipedia also does not mention data ownership or back pressure and other features 
such as bracketed IPs.  StreamWork does not directly implement data ownership and defined
lifetimes, back pressure, or bracketed IPs.  There is no apparent reason why these features could not 
be implemented within the components.   

We claim here that StreamWork meets all the Wikipedia criteria and therefore 
StreamWork implements 'classical' FBP.  Note that StreamWork is highly concurrent and also 
provides for subnet definition and expansion. 

StreamWork, however, does not directly incorporate IP defined lifetimes or require specific create/copy/destroy
operations.  In StreamWork, IPs live only from the moment of sending to the GO channel by the source
process until consumed(received) by the sink process, unless the buffersize
is specified as greater than zero.  
For buffersizes greater than zero, the GO language allows data even in closed channels to be reaccessed, so 
for utmost security, zero sized buffers and encryption are recommended for sensitive data, like passwords.

StreamWork does not distinguish between IIPs (initialization information packets) and ordinary IPs and therefore does not require any special notation for IIPs within the network definition language. 

StreamWork does not implement dynamic networking.   
The recently introduced GO plugin feature might be usefull at run time. 

## [FBP tenets https://jpaulm.github.io/fbp](https://jpaulm.github.io/fbp)

 * If work is boring, let a robot do it!
 	* Corollary: using a design tool should be fun!
 * No one language should try to do everything!
 * The world is asynchronous - don't try to force the systems we build into a synchronous framework!
 * The von Neumann paradigm is only appropriate within a single process! Duh!
 * Any language or system that "talks data" should be able to talk to any other one that "talks data".
 * A process needs to be able to have more than one input port, and needs to be able to choose which one to receive from!
 * If a process's upstream connection fills up, the process feeding it will be suspended (unless the connection is marked "DropOldest") ("back pressure")

## Temporal

  * [Temporal docs](https://docs.temporal.io/docs/go-run-your-first-app/)

## APIs

APIs are typically implemented via function calls, as stated in 
[altexsoft](https://www.altexsoft.com/blog/engineering/what-is-api-definition-types-specifications-documentation/)
.  
We suggest most APIs would be better implemented by FBP.   


  * [Seven API challenges](https://www.mckinsey.com/business-functions/mckinsey-digital/our-insights/the-seven-make-or-break-api-challenges-cios-need-to-address#)
  * [Everything an API](https://thenewstack.io/the-exploding-endpoint-problem-why-everything-must-become-an-api/)

The discovery, access, interface, and format of APIs are not standardized leading to fragmentation of programming languages, frameworks and developer consumption models such as containers and serverless as a way to deal with complexity. 

An existing functional API can be incorporated into a FBP component which interacts via one or more structures.   The component can thus 
simplify and tailor the functional API rules into a more standard API information packet.  When several, diverse functional APIs are required to carry out a particular operation, it may be possible to subnet the whole thing into one FBP process with a standard interface.  

Functional APIs, particulary web-based APIs with their inherent delays, would benefit immediately from FBP's inherent concurrency.    

## API Info

  * [API2Cart](htps://api2cart.com/business/6-difficulties-api-integration-way-avoid/)
  * [How developers use](http://sigdoc.acm.org/cdq/how-developers-use-api-documentation-an-observation-study/)
  * [CMU paper](http://www.cs.cmu.edu/~cscaffid/old/papers/pr_20060601_api.pdf)
  * [Martin papers](https://www.cs.mcgill.ca/~martin/papers/software2009a.pdf)
  * [Springer PDF](https://link.springer.com/content/pdf/10.1007%2F978-3-642-34347-6_10.pdf)
  * [arxif PDF](https://arxiv.org/pdf/1705.06586.pdf)
  * [API Challenges](https://www.testingxperts.com/blog/Top-4-Challenges-of-API-Testing-and-How-to-Overcome-Them)
  * [Patient Access](https://www.healthit.gov/topic/patient-access-to-medical-records/learning-module-apis-and-health-data-sharing)

 * [Microservices problem](https://stackoverflow.blog/2020/11/23/the-macro-problem-with-microservices/)
 * [Temporal Project](https://github.com/temporalio/temporal)
	
## GO Design Guidelines

  * Separate concerns
   	* GUI, business logic, DB,  etc. should not be intermixed. 
   	* Try to make the business logic clear to the business experts and easily modifiable.  
   	  Use decision tables, graphs, etc.
  * Simple interfaces
  	* Limit each channel to one type of data.  Pass a structure, not multiple data elements.  
  	  Pass handles, not pointers.
  	* Strive for less than four channels per component, splitting into multiple components 
  	  if necessary.   
  	  Exception:  same IP type on multiple channels.     
  	* Don't over simplify and create too many processes.
  	* Don't buffer unnecessarily.   
 	* Use simple URI rules [URI Rules](https://dzone.com/articles/7-rules-for-rest-api-uri-design-1)
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

  * produces pure GO code, however the bin library and build process is linux centric;
    The generated code, and supplied components, should run on any platform GO supportsk;
  * does not process IPs; it merely assigns channels to the sending and receiving components;
  * has a number of rules for automatically connecting ports according to their names and modes(sink or source);  
  * implements a text based, context free, program language agnostic, network definition language, SW;
  
    
