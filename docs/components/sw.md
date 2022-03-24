package sw // import "github.com/tyoung3/sw"

Package sw contains the basic FBP engine to launch a network of Streamwork
Go components.

The program 'sw' can create a main/Go program(cmd) from a Streamwork network
definition.

The generated cmd uses this package to launch the components specified in
the network definition. This package also contains basic Streamwork
components: Gen, Pass, Print, etc. Other sw/... components are:
swutility/Collate,Merge and linux/Wrap

Sw components have a very simple interface. There are no required import
statements and just one exported function, with the Component name, is
required.

FUNCTIONS

func Gen(wg *sync.WaitGroup, arg []string, cs []chan interface{})
    Gen sends 'nbr' integers, beginning with 'start', incremented by 'inc';
    argcuments 1, 2, and 3 respectively over port 0.

    #####Examples

        	(Gen will send:
        	1 2 3 4 5 6 7

         	(Gen "-i" "9" "2" "3") will send:
        2 5 8 11 14 17 20 23 26

            (Gen "-i" "3" "17") will send:
        17 18 19

        	(Gen "-i" "4" "-2" "-1") will send:
        -2 -3 -4 -5

func Gens(wg *sync.WaitGroup, arg []string, cs []chan interface{})
    Gens sends arg[1], arg[2] long strings to channel cs[0] (out1)

         Strings consist of the process name
        and seq. no; i.e. G3-1, G3-2, etc.

        BUG cannot set length, yet.

func Join(wg1 *sync.WaitGroup, arg []string, cs []chan interface{})
    Join sends all input from channels [1:n] to channel [0], port 0.

func Pass(wg *sync.WaitGroup, arg []string, cs []chan interface{})
    Pass delays input from chanell 0 for arg[1] milliseconds, then sends it out
    on channel 1.

func Print(wg *sync.WaitGroup,
	arg []string,
	cs []chan interface{})
    Print prints integers and strings received from port 0, prefixed with the
    process identifier(arg[0]) string,

func Split(wg *sync.WaitGroup, arg []string, cs []chan interface{})
    Split copies all input from port 0, to all active ports 1,..N

