package swutility // import "github.com/tyoung3/sw/swutility"

Package swutility provides merge and collate StreamWork components.

FUNCTIONS

func Collate(wg *sync.WaitGroup,
	arg []string,
	cs []chan interface{})
    Collate compares IPs from two channels(0,1). Matching IPs are sent to
    channels 2 and 3, while mismatches from (0,1) are sent to (4,5)
    respectively.

func Merge(wg *sync.WaitGroup,
	arg []string,
	cs []chan interface{})
    Merge compares input from channels 1 and 2 sending the lowest data to
    channel 0.

func MergeInt(wg *sync.WaitGroup, cs ...chan interface{})
    MergeInt sends all input from channels cs[1:n] to channel cs[0] in order of
    arrival.

