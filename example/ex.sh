#!/bin/bash

# ex.sh:
#	Purpost:  Generate a Streamwork skeleton project 
#
#   Create project directory(if not existing) and skeleton files, generate and test example code. 
#   Projects are created inside ~/.sw/  
#   
#   Other useful options
#
pgm=ex.sh
version="0.0.0"  
HTML=example.html

Die() {
		echo "$0/Die $*"
		exit 1
}

[ -z $GOPATH ] && Die Please set GOPATH to something like ~/go
bdir=$GOPATH/mod 
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

NotesFBP() {
	cat << EOF
* * * * * * * * * * * 

#StreamWork-$version Notes

##TODO

###Standard arguments for sw 

###Create Components

###Generate Skeleton Components and tests

	* Make this a first class feature
		* Man page
	* See script, $pgm
	* See mod/sw, SW frontend
	* Option(s) to generate config 
		handlers(viper,env, etc)w/config Struct.
	
##Tutorials 
 
###Build a component 

####Component Skeleton Generation	
	* Run script with import path and component 
	  name(initial lower case letter). Ex. '$0 std foo bar 1 2' 
	  creates a new component, bar.go, and test, foo_test.go 
	  in $GOPATH/mod/std/ and executes a 'go test'.     
	* Modify foo_test.go (test driven development) 
	* cd .../std;  run 'go test foo*'  
	* Modify foo.go 
		
####Guidelines

	* defer wg.Done() at the beginning 
	* Test w/-race before committing
	* Avoid global variables -- Guarantee re-entrancy 
	* Include process name in messages (standard error code @TODO)
			  
##Trials

	* Try nesting fbp calls within a component.  
	* Try method calls.
	
##Roadmap 
	
###Frontend
See github.com/tyoung3/sw for converting a network definition to:
	* A Go module, 				(works)
	* A Graphviz .DOT file 		(works)
	* An abstract syntax tree 	(works)
	* A linearized tree 		(works)
	* A Java Program 		    (need volunteer)
	* A C language program 		(need volunteer)
	* Other languages		    (any interest?)
		  
###Backend 
	Backend prototype, sw, is working with subnets. 		  
		    	
##Signals
	. Trap signals
		. Print out network 
	
##Copyright 

##GitHub Flow
	. GoLand ?

###New branch 

	* git pull origin master 
	* git checkout -b "Usefull_Branch_Name" 
	* git push --set-upstream origin  "Usefull_Branch_Name" 
 https://github.com/tyoung3/streamwork/pull/new/Usefull_Branch_Name
		   
###Commit changes
		   
	* Make changes 
	* git status
		* git add --all
		* git commit -m "Good commit message"
		* git push 
	* git branch [-a]   [Check branch]
	 
	
###While in branch [example_branch_name]	

    * git pull origin master	
	* go get -u=patch			. Update to latest patch version(s)
	* go mod tidy 			      [Clean up  go.sum]
    * go test OR make check 	. Start over if not OK 
	* go list [-u] -m all		. See all dependencies
	* git status				. Everything committed before? 
								  If not, start over
	* git checkout master 	 	. Leave branch

###While in master 
	* git pull origin master	. Start over if error. 
	* git status  				  [must be master branch]
	* git merge --no-ff  example_branch_name
	* git add --all 
	
###If no version change	
	* git commit -m "Good commit message"
	* git push 
	
###If New version		
	* git tag	
	* git tag     -a v0.0.? -m "Version_Notice_wo_spaces"
	* git commit -m "v0.0.?"
	* git push origin v0.0.? (Ex. git push origin v.0.0.2 )
					OR
	* git push origin --tags  (Pushes all tags to remote)


###Remove Branch if not needed 	
	  * git branch -d branchname 
	  * git push origin --delete branchname
	  * git branch	       	  

##Changes


#DONE

    * Quick Start [in README.md]
	* Run Go doc
	* Replace Launch4
	* Collate component
	
	 
https://githubflow.github.io/	
	
	* Anything in the master branch is deployable
	* To work on something new, create a descriptively 
	  named branch off of master (ie: new-oauth2-scopes)
	* Commit to that branch locally and regularly push your work 
	  to the same named branch on the server
	* When you need feedback or help, or you think the branch is 
	  ready for merging, open a pull request
	* After someone else has reviewed and 
	  signed off on the feature, 
	  you can merge it into master
	* Once it is merged and pushed to 'master', you can and 
	  should deploy immediately
	
#$pgm
What follows are some thoughts on designing a comprehensive
FBP-based Go language program, $pgm.  

Such a system makes possible the direct invocation of a 
program from its editable flow graph or from the 
flow graph's stored network text file. 

A comprehensive system would allow a wide community of 
developers to  share code effectively.  

##Goroutines 
Goroutines are lightweight(green) threads communicating 
with each other within a single address space.  Go may 
schedule goroutines onto multiple operating system threads 
and therefore onto multiple CPU cores. 
 
Go provides a number of facilities to help solve and to 
avoid race and deadlock problems.  

##Channels
Go design is very FBP-like.  Goroutines typically communicate over
Go channels, which are ring buffers of specified 
capacity(default 1).  
Channels and goroutines are built into the Golang 
syntax(unlike thread libraries in other languages) clarifying 
and simplifying their operation.
Channels can help to avoid extensive locking of critical 
code sections. 

##Packaging
The basic Go unit is a package, which is imported into a 
main Go program or another Go package.  The single main 
Go program defines a Go command, an executable program.

Go 'modules' are collections of related packages.  
Modules will default with the advent of Go-2.0.  Go modules 
are a recent development. 
Go 'plugins' allow for third parties to create interfacing code. 
The Go ecosystem avoids complex make files by the way it 
arranges dependent code in sub-directories.  Package 
libraries are compiled into the ../pkg directory tree. 
$pgm uses modules to allow for third parties to develop $pgm code 
independently. 

##Performance
Much has been done to make Go programs fast.  
A benchmark go program, available at 
./github.com/tyoung3/flowfib, can run millions of goroutines
communicating over millions of channels in a few seconds.

##Implementation 
From a graphable text file, FOO.net (which may include other files
and reference subnets defined elsewhere), generate and run a Go
'main' program, FOO.go.  FOO.go will import and invoke
$pgm go components, passing a structure(interface), providing 
the component's process name, interface(s), and string arguments.  

###Components
All components are reentrant.  The same component
may be invoked multiple times in the network definition, but 
each time with a different name. 
Components compiled on the fly and cached.

###Ports  

###Nodes
EOF
	
}

Notesx() { 
	cat <<- EOF
		Workflow: https://gist.github.com/blackfalcon/8428401
		Code generation from BNF: https://github.com/goccmack/gocc
		Using gocc: https://medium.freecodecamp.org/write-a-compiler-in-go-quick-guide-30d2f33ac6e0
	Tutorial: https://tour.golang.org/welcome/1
	Specification: https://golang.org/ref/spec#Notation
		http://www.cs.sfu.ca/CourseCentral/383/tjd/	syntaxAndEBNF.html#defining-language-syntax-with-extended-backus-naur-form

EOF

}


MakeDir2() {
	dir2=$1
	ddate=`date`
	Verbose Making $dir2
	[ -d $dir2 ] 		\
	|| ( mkdir -p $dir2		\
	&& cat << EOF > $dir2/_README.md
	$dir2	generated by ${pgm}.sh-v$version on $ddate	 
EOF
	)
}

MakeDir() {
	for dir in $*; do 
		MakeDir2 $dir
	done
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
	file:///home/tyoung3/go/mod/streamwork/ 
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
    DefaultBufferSize:	 0    #default GO buffersize
    HTMLdir:		"/home/tyoung3/go/mod/sw/html/" #Where tooltips live
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
	    DefaultBufferSize:	 0    #default GO buffersize
	    HTMLdir:		"/home/tyoung3/go/mod/sw/html/" #Where tooltips live
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
	
	go test -v  && go build
	 
}

MakeProject() {
	if [ ! -z $1 ]; then  
		 BuildCustom $*
		 exit
	fi
	echo Building example project. 
	defSource=Ex1
	defSink=Ex2
	defFilter=Ex3
	BuildCustom example ex1 1 0  ex2 0 1 ex3 1 1 ex4 0 0 ex5 2 2
	pwd
	echo '(E1 Ex1)<-1(E3 Ex3)<-(E2 Ex2); E4 Ex4;' > $pkg.sw
	sw -cfg $pkg.yaml $pkg.sw > /tmp/mainex.go 
	less Ex1.go *.sw *.yaml
	echo Removing $bdir/$pkg
	mv $bdir/$pkg  /tmp/$pkg$$ || Die cannot rm $bdir/$pkg
}

pgm=`basename $0`
case  $pgm in 
	swskel|skel)GenSkel $* && exit 0 || Die $* failed.;;
esac
	
case $1 in	
	d)  shift; SeeDocs --new-window  $*;;
	gd) shift; export GOROOT=`pwd`   
		godoc -http=:6060  -index &Custom
		sleep 5
	 	$BROWSER localhost:6060/fbp &
		    ;;
	gs|skel)shift;GenSkel $*    \
	&& 	$BROWSER --new-window $* $HTML;;
	# r)  go run internal/$pgm/*.go;;  #/* */
	p)  shift; MakeProject $*;;
	t)  shift; go test $* ./... 2>&1 |less ;;
	v)	echo $pgm-v$version;;
	x)  $EDITOR ${pgm}  &;;
	*)  cat <<- EOFX
	
	$0-v$version USAGE:  
	 	d			. View GO docs 
	 	gd			. Run and view 'godocs'
	 	gs PKG	COMPNAME CONFIG_TYPE [INPORTS [OUTPORTS]] Generate skeleton components
					COMPNAME must begin with an upper case letter
					PKG directory will be created if missing.
					CONFIG_TYPE can be NONE,TOML, or YAML
	 	n			. Browse $pgm notes
	 	p  [PKG [module...]]	. Create a StreamWork Project
	 	t			. Test fbp packages 
	 	v			. Display version
	 	x			. Edit $0
	 	--help			. Display this usage
		
	 	Example: $0 x
EOFX
	;;

esac	
