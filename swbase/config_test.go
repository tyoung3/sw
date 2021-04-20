package swbase

import "testing"
import "fmt"

func TestConfig(t *testing.T) {
	cfg 	 := PkgConfig()
	bs, _ 	 := cfg.IntOr("swbase.buffersize", -1)
	seqno, _ := cfg.IntOr("swbase.seqno", 2)
	title, _ := cfg.StringOr("swbase.title", "n/a")
	version  := "v0.0.0"
	
	fmt.Print(title,
		" \u001b[36mTesting Config ",
		version,
		" bs=", bs,
		" seqno: ", seqno)

	fmt.Println(
		"\u001b[0m")

	if seqno != 1234 {
		fmt.Println(
			"\u001b[31mmerge/def/Print1: Seqno is", seqno, "not = 1234.  Missing config file?\u001b[0m")
	}

type ip_t struct {   /* Information Packet type */ 
P string   /* Process Name  */
S string   /* modulepath/component */
I int      /* Port number */
}


	fmt.Println("TestPrint1 done.")
}
