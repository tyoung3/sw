/*Package sw contains the basic FBP engine to launch a network of Streamwork Go components.

The program 'sw' can create a main/Go program(cmd) from a Streamwork network definition. 
 
The generated cmd uses this package to launch the components specified in the  network definition.
This package also contains basic Streamwork components: Gen, Pass, Print, etc.
Other sw/... components are: swutility/Collate,Merge and linux/Wrap

Sw components have a very simple interface.  There are no required import statements and just one exported function, with the Component name, is required.   
*/
package sw
