/*Package sw contains a number of basic, standard StreamWork components.

The program 'sw' can create a main/Go program(cmd) from a Streamwork network definition. 
 
The generated cmd launches the component processes specified in the  network definition as separate go routines.

This package contains basic Streamwork components: Split, Join, Gen, Pass, Print, etc.  Other .../sw/ packages are: config, swutility, and linux.

Sw components have a simple interface.  There is no complex API; there are no StreamWork required import statements. Just the exported function is required.  This makes it easy to create your own components. The bash script, **_swproject_** generates an entire project tree from a network definition 
*/
package github.com/tyoung3/sw
