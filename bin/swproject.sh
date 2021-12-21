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

version="0.18.9"  
targetdir=/usr/src
pgm=swproject.sh

Die() {
	echo -e "${red}$self/DIE: $*$reset"
	exit 1
}

[ -d $targetdir ] || Die Cannot find directory: $targetdir 
swdir=/usr/local/bin
[ -e $swdir/sw ] || swdir=/usr/local/bin
SW=$swdir/sw
[ -e $SW     ] || Die $SW is missing 

Debug() {
        [ "$DEBUG" == "y" ] && echo -e "$yellow$pgm/DEBUG: $* $reset " 
        # echo -e $red Debug $* $reset
        echo -n 
}


self=$pgm
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
	Debug $0/GenCFG *$* 
	echo "# Generated by swproject.sh-v$version/GenCFG $* for Project $p `date`" > sw.cfg
	
	case $# in
		0) 
		cat <<- EOF >> sw.cfg	
	StreamWork:
  defaults:  
    DefaultSourceComp: 	"Gen"
    DefaultSinkComp: 	"Print"
    DefaultPath: 	"sw"
    DefaultFilterComp: 	"Pass"  
    DefaultBufferSize: 	  0    #default GO buffersize
    HTMLdir:	    "$dir/html/"    
    DefaultLibrary: "$modpath/$p"
  limits:
    Maxbfsz:   	1000    #Maximum GO buffer size
  SymbolTable:
    Tablesize:	10000     
	
EOF
	;;
		*)	 
			cat $1 > sw.cfg	
			    ;;
esac	
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
	sw=$1; cfg=$2
	[ -f $sw ] || sw="${sw}.sw"
	p=`basename -s .sw $sw`|| Die $sw not MODULE.sw  
	
	[ $sw == "sw" ]       &&Die Module sw is already in github/tyoung3  
	
	if [ -f `pwd`/$sw ]; then 
		sw=`pwd`/$sw
	fi
	
	Debug sw=$sw p=$p $* 
	icfg=$2
	[ -f $sw ] || Die Genp: Cannot locate $sw 
	shift 2
	[ -f $dir/$p/.git ] && Die Found .git in source directory -- FAILED 
	echo; Display $0/GenP: Generating  go module $p  from $sw
	[ -d $dir/$p ] && echo Updating go module $p  from $sw || echo Generating  go module $p  from $sw in $dir/$p
	[ -d $dir/$p ] || mkdir $dir/$p || Die Cannot mkdir $dir/$p
	pushd $dir/$p							\
	   && ( [ -d internal ] || mkdir $* internal )			\
	   && ( [ -f go.mod ]  						\
	      || (go mod init $modpath/$p; echo $replace >> go.mod  ))	\
	   && pushd internal || Die Cannot pushd internal		
	         [ -f ${p}.go ] && mv  ${p}.go ${p}.go.bak
	   	 ([ -f ${p}.sw ] && mv ${p}.sw ${p}.sw.bak) || true  \
	   	 && cp  $sw ${p}.sw					\
	   	 && [ -f sw.cfg ]  || GenCFG $cfg 		\
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
	nd=$1; cfg=$2
	exam=nds/postage.sw
	[ -z $1 ] && Die Missing PROJECT_NAME.  Try \'genproject $exam\' 
	Display GenProject for $nd	$cfg 
	Genp $nd $cfg
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
	XXX)shift; Init; KillEm $*;;
	XXX)shift; Init; tree --noreport  -L 2 $*;;
	x)shift; $EDITOR $self;;
	--help|/?|?)cat <<- EOF 

	Usage: ${self}  v$version 
	 	PROJECT   [ CONFIG_FILE ] . Generate project(s) from PROJECT[.sw] 
	 	--help 			  . Display this help

EOF
	;;
	-v) echo genproject-v$version;;
	*) GenProjectP $*;;
esac
