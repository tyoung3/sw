#!/bin/bash

# project.sh:
#	Purpose:  Generate a Streamwork skeleton project 
#
#   Create GO FBP project(s) from .SW file(s).   
#   Create directory(if not existing) and skeleton files, 
#     generate and test example code, and run the example.   
#   Project sub-directories are created in the current directory.
#   
#   Example:
#	$ ./$pgm g test/X.sw
#

        black="\u001b[30m"
        red="\u001b[31m"
        green="\u001b[32m"	
        lightgreen="\u001b[32;1m"	 
        yellow="\u001b[33m"
        blue="\u001b[34m"
        magenta="\u001b[35m"
        cyan="\u001b[36m"
        white="\u001b[37m"
        reset="\u001b[0m"
        
# @@TODO:  List of banned Modules.   Push Data to file, then have script read file. 
#    git branch to PS1
#    all packages import project code.

version="0.0.6"  
targetdir=$GOPATH/src
pgm=swproject.sh

Die() {
	echo -e "${red}$self/DIE: $*$reset"
	exit 1
}

swdir=/usr/local/bin
[ -e $swdir/sw ] || swdir=/usr/local/bin
SW=$swdir/sw
[ -e $SW     ] || Die $SW is missing 

Debug() {
        [ "$DEBUG" == "y" ] && echo -e "$yellow$pgm/DEBUG: $* $reset " 
        # echo -e $red Debug $* $reset
        echo -n 
}


#pat  is github Personal Access Token: "SW Project Generation"
pat=c7587f442e2bb2a7784dfa776dc949693aa43ed7 

self=$pgm
[ -z $GOPATH ] && Die GOPATH is not set
modpath="github.com/tyoung3/sw"
#modpath=/tmp/MODPATH
#modpath=$targetdir
dir=$targetdir

Debug Running ${pgm}-$version w/DEBUG args: $*

Display() {
	Debug $*
}

[ -d $dir ] || Die Missing directory: $dir

Init() {
	pushd $dir || Die Cannot pushd $dir
}	

GenCFG() {
	echo #  Project $p  SW.CFG file.Generated by $0 `date` 
	#       
	cat <<- EOF 
	StreamWork:
  defaults:  
    DefaultSourceComp: 	"Gen"
    DefaultSinkComp: 	"Print"
    DefaultPath: 	"def"
    DefaultFilterComp: 	"Pass"  
    DefaultBufferSize: 	  0    #default GO buffersize
    HTMLdir:	"${HOME}/go/src/github.com/tyoung3/sw/swbase/html/"    
    DefaultLibrary: "$modpath/$p"
  limits:
    Maxbfsz:   	1000    #Maximum GO buffer size
  SymbolTable:
    Tablesize:	1000     
	
EOF
}

GenGo() {
	 module=$p
	 Debug GenGo:  $*  module=$module
	 $SW -m 5 ${p}.sw > ./gen_$pgm
	 chmod a+x ./gen_$pgm				 
	 ./gen_$pgm
	 		 
}    

selectExample() {   # Reverse for _test.go
	cat <<- EOF
	var wg2 sync.WaitGroup
	wg2.Add(2)
	state := 3
	
	go  func() {
		defer wg2.Done()
		cs[1]   <- state
		fmt.Println("A/sent state:",state)
			
	}()
	
	go func() {
		defer wg2.Done()	
		msg1,ok  := <-cs[0]
		for ok==true {
			fmt.Println("A/receivedx:", msg1)
			msg1,ok  = <-cs[0]
		}	
	}()
	
        wg2.Wait()
EOF
}	

Genp() {
	Display Genp/$GENPy: $*
	sw=$1
	[ -f $sw ] || sw="${sw}.sw"
	p=`basename -s .sw $sw`|| Die $sw not MODULE.sw  
	
	[ $sw == "sw" ]       &&Die Module sw is already in github/tyoung3  
	
	if [ -f `pwd`/$sw ]; then 
		sw=`pwd`/$sw
	fi
	
	Debug sw=$sw p=$p $* 
	[ -f $sw ] || Die Genp: Cannot locate $sw 
	shift 1
	[ -f $dir/$p/.git ] && Die Found .git in source directory -- FAILED 
	echo; Display Generating  go module $p  from `pwd`/$cfg 
	[ -d $dir/$p ] && echo Updating go module $p  from $sw || echo Generating  go module $p  from $sw in $dir/$p
	[ -d $dir/$p ] || mkdir $dir/$p || Die Cannot mkdir $dir/$p
	replace="replace github.com/$USER/$p => $GOPATH/src/$p"
	pushd $dir/$p							\
	   && ( [ -d internal ] || mkdir $* internal )			\
	   && ( [ -f go.mod ]  						\
	      || (go mod init $modpath/$p; echo $replace >> go.mod  ))	\
	   && pushd internal || Die Cannot pushd internal		
	         [ -f ${p}.go ] && mv  ${p}.go ${p}.go.bak
	   	    ([ -f ${p}.sw ] && mv ${p}.sw ${p}.sw.bak) || true  \
	   	 && cp  $sw ${p}.sw					\
	   	 && [ -f sw.cfg ]  || GenCFG  > sw.cfg			\
	   	 && Debug internal run sw `pwd`/${p}.sw			\
	   	 && sw ${p}.sw > ${p}.go				\
	   	 && go mod tidy						\
	   	 ; GenGo $* 						\
	   	 && swgraph ${p}.sw 					\
	   	 && wait						\
	   && popd							\
	   && echo -e "${green}$self: Create project from $sw: Success!$reset" 		\
	   || Die "${red}$self: Create project from $sw: FAILED.$reset"	\
	   && go mod tidy						\
	   && go fmt  ./...						\
	   && go test ./...						\
	   && go run internal/${p}.go			\
	   && echo -e "${green}$self: ${p}.go Succeeded. $reset" 		\
	   || Die "${red}$self:  ${p}.go FAILED.$reset"			 
	   # && (pushd internal; go build *.go; popd)		
	echo
				 
}

GenProjectP() {
	nd=$1
	exam=nds/postage.sw
	[ -z $1 ] && Die Missing PROJECT_NAME.  Try \'genproject g $exam\' 
	Display GenProject for $nd	 
	Genp $nd 
}

GenProject() {
	[ -z $1 ] && ( Genp X Y ; exit 0 )  	\
	|| Display GenProject for $*		\
	, Genp $* 
}

KillEm() {
	for p in $*; do
		echo Kill $p
	done

}

case $1 in
	XXX)shift; Die option OBSOLETE;;   
	g)shift; GenProjectP $*;;
	XXX)shift; Init; KillEm $*;;
	XXX)shift; Init; tree --noreport  -L 2 $*;;
	x)shift; $EDITOR $self;;
	*)cat <<- EOF 

	Usage: ${self}  v$version 
	 	g [PROJECT ...]	. Generate project(s) from PROJECT.sw 
	 	x Edit this script
	 	* Display this help

EOF
	;;
esac
