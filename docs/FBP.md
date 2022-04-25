# Flow Based Programming  
  
##  StreamWork and 'Classical FBP'

We believe StreamWork is consistent with 'Classical Flow Based Programming'. 

### Wikipedia Definition of FBP

>"In computer programming, flow-based programming (FBP) is a programming paradigm that defines applications as networks of "black box" processes, which exchange data across predefined connections by message passing, where the connections are specified externally to the processes. These black box processes can be reconnected endlessly to form different applications without having to be changed internally. FBP is thus naturally component-oriented.

>FBP is a particular form of dataflow programming based on bounded buffers, information packets with defined lifetimes, named ports, and separate definition of connections."
   <br>--- [Flow Based Programming -- Wikipedia](https://en.wikipedia.org/wiki/Flow-based_programming)

So to summarize, the Wikipedia definition of FBP is charactarized by:

   * Black box processes
   * Separate connection definitions
   * Message(information packet, IP) passing
   * Bounded buffers
   * IPs with defined lifetimes
   * Named Ports

Wikipedia does not mention concurrency -- in error, we maintain. 
The core concept of flow-based programming is that of concurrent processes
communicating with each other asynchronously. 
 
Wikipedia also does not mention subnets, 
back pressure, data ownership, or bracketed IPs.  
StreamWork does not directly implement all these features,
but there is no obvious reason why these features could not 
be implemented within the components. 

StreamWork considers subnets to be an essential design tool.  StreamWork allows unlimited numbers of subnets and components and a ridiculously large(100) number of subnet levels.  Note that 
StreamWork is highly concurrent and allows for high degrees of parallelism.   

We claim here that StreamWork meets all the Wikipedia criteria 
and therefore StreamWork implements 'classical' FBP.  
StreamWork, however, does not directly incorporate IP defined 
lifetimes or require specific create/copy/destroy
operations.  In StreamWork, IPs live only from the moment of sending to
the GO channel by the source process until received by the sink process. 
For buffersizes greater than zero, the GO language allows data even in
closed channels to be reaccessed, so 
for utmost security, zero sized buffers and encryption are recommended 
for sensitive data, like passwords.

Component behavior can be controlled via arguments, environment
variables,  in-stream commands, ordinary IPs, and signals.

StreamWork does not distinguish between IIPs (initialization information 
packets) and ordinary IPs and therefore does not require any special 
processing or notation for IIPs within the network definition language.    

## [FBP tenets https://jpaulm.github.io/fbp](https://jpaulm.github.io/fbp)

 1. If work is boring, let a robot do it!
    <br>Corollary: using a design tool should be fun!
 2. No one language should try to do everything!
 3. The world is asynchronous - don't try to force the systems we build into a synchronous framework!
 4. The von Neumann paradigm is only appropriate within a single process! Duh!
 5. Any language or system that "talks data" should be able to talk to any other one that "talks data".
 6. A process needs to be able to have more than one input port, and needs to be able to choose which one to receive from!
 7. If a process's upstream connection fills up, the process feeding it will be suspended (unless the connection is marked "DropOldest") ("back pressure")


## Flow Based Programming References
  * [J Paul Morrison](https://jpaulm.github.io/fbp/)
  * [Other FBP Projects SpreadSheet](https://fbp.twyoung.com/)
  * [Flow Based Programming (Wiki)](https://en.wikipedia.org/wiki/Flow-based_programming)

