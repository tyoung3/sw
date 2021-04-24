#!/bin/bash

# ex.sh:
#	Purpose:  Generate a Streamwork skeleton project 
#
#   Create GO/FBP project(s) from .SW file(s).   
#   Create directory(if not existing) and skeleton files, 
#     generate and test example code, and run the example.   
#   Project sub-directories are created in the current directory.
#   
#
pgm=ex.sh
version="0.0.0"  
HTML=example.html

Die() {
		echo "$0/Die $*"
		exit 1
}

[ -z $GOPATH ] && Die Please set GOPATH to something like ~/go
bdir=$GOPATH/src/github.com/tyoung3
[ -d $bdir ] || Die Please create $bdir 
src=$bdir

# NOTE: Go ignores files and directories beginning with '_', as in _OLD/

Debug() {
	[ "$DEBUG" == "y" ] && echo $pgm/DEBUG: $*  
}

Verbose() {
	if [ ! -z $verbose ]; then
	 	echo "${pgm}: $*"
	fi 	
} 




SeeDocs() {

	URLSx="
	https://golang.org/
	https://www.commonwl.org/
	https://gist.github.com/blackfalcon/8428401/
	https://githubflow.github.io/	
	https://appliedgo.net/flow/ 
	https://medium.com/@benbjohnson/standard-package-layout-7cdbc8391fc1
	http://scipipe.org/
	http://reo.project.cwi.nl/v2/projects/
	"
	URLS=" 
	https://godoc.org/github.com/tyoung3/streamwork/def#Github
	https://godoc.org/github.com/tyoung3/streamwork/poc#Github
	https://github.com/tyoung3/sw/
	https://goreportcard.com/report/github.com/tyoung3/streamwork
	file:///home/tyoung3/go/src/github.com/tyoung3/streamwork/ 
	http://localhost:6060/poc
	$HTML
	"
	$BROWSER $* $URLS &
	echo
}


IdSkel() {
	cat << EOF
	/*  Generated StreamWork component, $name, 
	    by $pgm on `date` 
		$inp  input  ports 
		$outp output ports 
	*/ 
EOF
}

lb='{'
rb='}'
for="for"

GenOutP() {	 
	 if [ $po -eq 1 ]; then 
	 	cat << EOFX >> ${name}.go	
	 	
			cs[$inp] <- $inp
			
EOFX
	 else 	
	 	
	 	cat << EOFX >> ${name}.go
	 	
	 	i := $po
	 	
		$for i >= $inp $lb
			cs[i] <- i
			close(cs[i])
			i--
		$rb

EOFX
	fi
}

makeFile() {
	red="\u001b[31m"
	reset="\u001b[0m"
	cat <<- EOF > $1
	# $HOME/.sw/${pkg}.toml generated by swskel `date` 
StreamWork:
  defaults:  
    DefaultSourceComp: 	"Ex1"
    DefaultSinkComp: 	"Ex2"
    DefaultPath: 	"example"
    DefaultFilterComp: 	"Ex3"  
    DefaultOrphanComp: 	"Ex4"  
    DefaultBufferSize:	 0    #default GO buffersize
    HTMLdir:		"/home/tyoung3/go/mosrc/github.com/tyoung3/sw/html/" #Where tooltips live
    DefaultLibrary: 	"example"
  limits:
    Maxbfsz:   	10000    #Maximum GO buffer size
  SymbolTable:
    Tablesize:	4000


[$pkg]   # Options for all components in $pkg  
  title: 		"\u001b[31mStreamWork Example Package\u001b[0m" 
  seqno: 1234    	#Used to check for valid config file. 
  buffersize: 1  	#Integer example. 
  #bornon: 2020-09-09T17:08:17-04:00  
	seqno=1234    #Used to check for valid config file. 
	buffersize=1  #Integer example. 
	title="${red}StreamWork Example Package${reset}" 
	#bornon=`date -I'seconds'`
	
	# Add additional options here -- e.g.
	[bar]
	title="Foo.bar Example"
EOF
	
}

makeYAML() {
	red="\u001b[31m"
	reset="\u001b[0m"
	cat <<- EOF > $1
	# $HOME/.sw/${pkg}.yaml generated by swskel `date` 
	StreamWork:
	  defaults:  
	    DefaultPath: 	"$pkg"
	    DefaultSourceComp: 	"$defSource"
	    DefaultSinkComp: 	"$defSink"
	    DefaultFilterComp: 	"$defFilter"  
	    DefaultOrphanComp: 	"$defOrphan"  
	    DefaultBufferSize:	 0    #default GO buffersize
	    HTMLdir:		"/home/tyoung3/go/src/github.com/tyoung3/sw/html/" #Where tooltips live
	    DefaultLibrary: 	"$pkg"
	  limits:
	    Maxbfsz:   	10000    #Maximum GO buffer size
	  SymbolTable:
	    Tablesize:	4000 

	${pkg}:   
	  #bornon: `date -I'seconds'`
	  title: "${red}StreamWork Example Package${reset}" 
	  seqno: 1234    #Used to check for valid config file. 
	  buffersize: 1  #Integer example. 
	
EOF
	
}

genPkgConfig() {	
	fconfig="
/** pkgConfig initializes the go-config package.
See: https://github.com/zpatrick/go-config for details
*/
func pkgConfig(configFile string)  *config.Config {
	mappings := map[string]string{
		\"${pkg^^}_BUFFERSIZE\": \"${pkg}.buffersize\",
	}
	
	return config.NewConfig([]config.Provider  {
		config.New${config}File(configFile), 
		config.NewEnvironment(mappings)} )	
}
" 	    
	go_config='config "github.com/zpatrick/go-config"'	
	go_config2="$fconfig"
	go_config3="cfg := pkgConfig(\"${pkg}.toml\")
    bs, _ := cfg.IntOr(\"${pkg}.buffersize\", 1)
    seqno, _ := cfg.IntOr(\"${pkg}.seqno\", 1)
    title, _ := cfg.StringOr(\"${pkg}.title\", \"n/a\")
    
    fmt.Println(title, 
    		\"Running\", 
    		arg[0], 
    		version, 
    		\"bs =\", bs, 
    		\"seqno = \", seqno) 
    
    if seqno != 1234 {
    	fmt.Println(
    	  \"Seqno not = 1234.  Missing config file?\")
    } 
    "	 
}


noPkgConfig() {	 
	Debug noPkgConfig $* $config
	go_config="" 	 
	go_config2=""
	go_config3="cfg := pkgConfig(\"${pkg}.toml\") 
    seqno, _ := cfg.IntOr(\"${pkg}.seqno\", 1)
    bs, _ := cfg.IntOr(\"${pkg}.buffersize\", 1)
	fmt.Println(
		\"Running\", arg[0], version, \"bs =\", bs)  
	
    if seqno != 1234 {
    	fmt.Println(
    	  \"Seqno not = 1234.  Missing config file?\")
    } "
}

genPkgYAML() {	
	Debug genPkgYAML

fconfig="
/** pkgConfig initializes the go-config package.
See: https://github.com/zpatrick/go-config for details
*/
func pkgConfig(configFile string)  *config.Config {
	mappings := map[string]string{
		\"${pkg^^}_BUFFERSIZE\": \"${pkg}.buffersize\",
	}
	
	return config.NewConfig([]config.Provider  {
		config.New${config}File(configFile), 
		config.NewEnvironment(mappings)} )	
}
" 	    
	go_config='config "github.com/zpatrick/go-config"'	
	go_config2="$fconfig"
	go_config3="cfg := pkgConfig(\"${pkg}.${config,,}\")
    bs, _ := cfg.IntOr(\"${pkg}.buffersize\", 1)
    seqno, _ := cfg.IntOr(\"${pkg}.seqno\", 1)
    title, _ := cfg.StringOr(\"${pkg}.title\", \"n/a\")
    
    fmt.Println(title, 
    		\"Running\", 
    		arg[0], 
    		version, 
    		\"bs =\", bs, 
    		\"seqno = \", seqno) 
    
    if seqno != 1234 {
    	fmt.Println(
    	  \"Seqno not = 1234.  Missing config file?\")
    } 
    "	 
}	

noPkgYAML() {	 
	Debug noPkgYAML $* $config
	go_config="" 	 
	go_config2=""
	go_config3="cfg := pkgConfig(\"${pkg}.yaml\") 
    seqno, _ := cfg.IntOr(\"${pkg}.seqno\", 1)
    bs, _ := cfg.IntOr(\"${pkg}.buffersize\", 1)
	fmt.Println(
		\"Running\", arg[0], version, 
		\"bs =\", bs, 
		\"seqno =\", seqno)  
	
    if seqno != 1234 {
    	fmt.Println(
    	  \"Seqno not = 1234.  Missing config file?\")
    } "
}

	# See:  https://github.com/zpatrick/go-config
GenGo() {	
	 Debug GenGo1 $* $config
	 case $config in 
	 	 TOML)
	 	    cfg_file="$HOME/.sw/$pkg.toml" 
	 	    [ -f $cfg_file ] || makeFile $cfg_file	
	 	    [ ${pkg^^} == ${name^^} ] 	\
	 	    && genPkgConfig				\
	 	    || noPkgConfig 
	 	 	;;
	 	 YAML)
	 	 	Debug GenGo2 YAML G=$genedpkg
	 	    cfg_file="$pkg.yaml" 
	 	    [ -f $cfg_file ] || makeYAML $cfg_file
		    if [ "$genedpkg" == "Y" ]; then 
			fconfig=""
			go_config=""
			go_config2=""
			go_config3=""
			noPkgYAML
		    else
			genedpkg="Y" 	
		 	genPkgYAML	
		    fi
	 	 	;;
	 	 *)go_config3="fmt.Println(
		\"Running\", arg[0], version)" 
		   ;;	
	 esac
	 	 
	 cat << EOF > ${name}.go 
	    /* package $pkg is generated by StreamWork.*/
	 	package $pkg
	 	
		`IdSkel` 
		 
		import (
			"fmt"
			"sync"
			$go_config
		)
		
		$go_config2
		
	    func $name(wg *sync.WaitGroup, arg []string, cs []chan interface{} ){
	    	var version string="v0.0.0"
	    	
	    	defer wg.Done()
	    	$go_config3
EOF
	    	
	 # For each output port, send one ip and close the port.
	 
	 if [ $outp -gt 0 ]; then  
		outp=$(($outp-1))
	 	po=$(($outp+$inp))
	 	GenOutP
	 fi
	 
	 # For each input port, receive one ip.
	 if [ $inp -gt  0 ]; then
	 	inp=$(($inp-1))
	 	pi=$inp
	 	cat << EOFZ >> ${name}.go  
	 	
	 	j := $inp
	 	$for j >=0 $lb
			ip, ok := <-cs[j]
			if ok != true {
				break
			}
			fmt.Println(arg[0], "chan:", j, "IP:", ip)
	    	j--
	    $rb	  
EOFZ
	 fi
	    	
	 cat << EOF >> ${name}.go 
	    }
EOF

	gofmt -w -s ${name}.go
	echo Debug: $EDITOR $cfg_file
}

GenTestOutP() {	 	
	 	cat << EOFX >> ${name}_test.go
	 	
	 	i := $ni
		$for i >= 0 $lb
			cs[i] <- i
			close(cs[i])
			i--
		$rb
EOFX
}

GenTestGo() {	
	 ni=$1
	 no=$2
	 cat << EOFY > ${name}_test.go
		package $pkg

	`IdSkel`
	
import "testing"
import "fmt"
import "sync"

func TestSkel_${name}(t *testing.T) {
	var cs  []chan interface{}
	var wg  sync.WaitGroup
	
	arg := []string{"TestSkel_${name}"}
	
	fmt.Println(arg[0])
EOFY
    
    nports=$(($no + $ni))
    if [ $nports -gt 0 ]; then      
	 	cat << EOFY >> ${name}_test.go	
		$for i :=0; i < $no + $ni; i++ $lb
			cs = append(cs,make(chan interface{}))
		$rb
EOFY
	fi
	
	 cat << EOFY >> ${name}_test.go
	
	wg.Add(2) 
	go func() { 
EOFY
			 # For each input port, receive one ip.
	 if [ $no -gt  0 ]; then
	 	no=$(($no-1))
	 	po=$(($no+$ni))
	 	cat << EOFZ >> ${name}_test.go  
 
	 	j := $po
	 	$for j >= $ni $lb
			ip, ok := <- cs[j]
			if ok != true {
				break
			}
			fmt.Println("chan:",j,"IP:",ip);
	    	j--
	    $rb	  
	    
EOFZ
	 fi
     
     if [ $ni -gt 0 ];  then
     	ni=$(($ni-1))
     	#echo ni=$ni
	 	GenTestOutP
	 fi
	 
	 cat << EOFY >> ${name}_test.go
			fmt.Println("TestSkel_${name} Ended")
			wg.Done()
			return
	}() 
	
	go $name(&wg, arg,  cs)
	wg.Wait()	

}
	
EOFY
	go fmt ${name}_test.go
}
	

#  Generate a skeleton component
GenSkel() {
	echo GenSkel $* $src
	pkg=$1; shift; 
	name=${1^}
	config=${2^^};   # NONE, TOML, YAML, other later  
	inp=$3
	outp=$4
	[ -z $inp ] && inp=0
	[ -z $outp ] && outp=0
	shift 3
	[ -z $pkg ] && Die  Usage: $0 gs PKG NAME ... 
	[ -z $name ] && Die Usage: $0 gs PKG NAME ...
	[ -f ${name}_test.go ]  || GenTestGo $inp $outp
	[ -f ${name}.go ]  		|| GenGo 	 $inp $outp
	
}


CheckOut() {
	go get github.com/tyoung3/dummy_repository 
}


BuildCustom(){
	pkg=$1;shift 
	[ -d $bdir/$pkg ] && Die $bdir/$pkg exists -- try another package name.
	echo Creating project $bdir/$pkg with modules $*
        mkdir -p $bdir/$pkg&&pushd $bdir/$pkg || Die Cannot cd $bdir/$pkg
	go mod init $pkg/$pkg
	N=1

	echo -n "(E1 $1)" > $pkg.sw
	while [ ! -z $1 ]; do
		mod=$1;nin=$2;nout=$3; shift 3
		echo -n "1<-(E$N $mod)" >> $pkg.sw
		GenSkel $pkg $mod YAML $nin $nout  
		N=$(($N+1))
	done
	echo ';' >> $pkg.sw	
	sw -cfg $bdir/$pkg.yaml $pkg.sw > /tmp/main.go 
	[ -z $cfg_file ] || $EDITOR $cfg_file &
	tree  $bdir/$pkg

	echo "swgraph -cfg *yaml  $pkg.sw &" >> run	\
	&& echo "swgo -cfg *yaml $pkg.sw &" >> run    		\
	&& chmod a+x run 

	go test -v  && go build
	./run
	 
}

MakeProject() {
	if [ ! -z $1 ]; then  
		 BuildCustom $*
		 exit
	fi
	echo Building example project. 
	defSource=XSource
	defSink=XSink
	defFilter=XFilter
	defOrphan=XOrphan
	BuildCustom example $defSource 1 0  $defSink 0 1 $defFilter 1 1 $defOrphan 0 0  
	# pwd
	echo "(E1 $defSink)<-1(E3 $defFilter)<-(E2 $defSource); E4 $defOrphan;" > $pkg.sw
	sw -cfg $pkg.yaml $pkg.sw > /tmp/mainex.go 
	less *.go *.sw *.yaml
	echo Removing $bdir/$pkg
	mv $bdir/$pkg  /tmp/$pkg$$ || Die cannot mv $bdir/$pkg
}

pgm=`basename $0`
case  $pgm in 
	swskel|skel)GenSkel $* && exit 0 || Die $* failed.;;
esac
	
case $1 in	
	gs|skel)shift;GenSkel $*    \
	&& 	$BROWSER  $* $HTML;;
	# r)  go run internal/$pgm/*.go;;  #/* */
	n)  shift; cat <<- EOF | /usr/bin/multimarkdown >/dev/shm/$$.html 

		
	Purpose:  Generate a Streamwork skeleton project 
	================================================
  	. Create GO/FBP project(s) from .SW file(s).    
   
   	. Create directory(if not existing) and skeleton files. 

      	* Generate, build, test, and run the project.

    	* Project sub-directories are created in the current directory.

	Named Ports
	-----------

	Ports are numbered 0...N; where N+1 is the number of process ports. 
	Input ports appear before output ports.   Port names may be appended 
	as in: NNN.name; where NNN is the7 port number and 'name' is the port
	name.  If there exists a format file for 'name',  that file will be
	attached to the port.  If not, string data will be assumed.  

	Certain 
	port names are reserved:  
		* n+     . is short for numeric data; ex.  1.nnn.7 will generate
					seven, random, three digit numbers. 
    

EOF
	$BROWSER  /dev/shm/$$.html &
	 ;;
	p)  shift; MakeProject $*;;
	v)	echo $pgm-v$version;;
	x)  $EDITOR ${pgm}  &;;
	*)  cat <<- EOFX
	
	$0-v$version USAGE:  
	 	gs PKG	COMPNAME CONFIG_TYPE [INPORTS [OUTPORTS]] Generate skeleton components
					COMPNAME must begin with an upper case letter
					PKG directory will be created if missing.
					CONFIG_TYPE can be NONE,TOML, or YAML
	 	n			. Browse $pgm notes
	 	p  [PKG [module NIN NOUT] ... ]	 Create a StreamWork Project
	 	v			. Display version
	 	x			. Edit $0
	 	--help			. Display this usage
		
	 	Example: $0 x
EOFX
	;;

esac	
