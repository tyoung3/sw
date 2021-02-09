#!/bin/bash

# p.sh:
#	Purpose:  Generate a Streamwork skeleton project 
#
#   Create GO/FBP project(s) from .SW file(s).   
#   Create directory(if not existing) and skeleton files, 
#     generate and test example code, and run the example.   
#   Project sub-directories are created in the current directory.
#   
#   Example:
#	$ ./p.sh Ex1 
#
self=p.sh
version="0.0.0"  
dir=/tmp/x
dir0=`pwd`

Die() {
	echo "$self/DIE: $*"
	exit
}

Display() {
	echo $self/$*
}

[ -d $dir ] || mkdir $dir || Die Cannot mkdir $dir

Init() {
	pushd $dir || Die Cannot pushd $dir
}

Genp() {
	[ -f $dir0/${p}.sw ] || Die Missing $dir0/${p}.sw 
	
	( [ -d $p ] && echo Found project $p )		\
	   || ( mkdir $p || Die Cannot mkdir $p ) 	\
	   &&  pushd $p						\
	   &&  echo Generating  $p project  
	ln -s $dir0/${p}.sw && sw -m 2 ${p}.sw
	popd
}

GenProject() {
	Display GenProject $*
	for p in $*; do
		Genp $p & 
	done

}

KillEm() {
	for p in $*; do
		echo Kill $p
	done

}

case $1 in
	g)shift; Init; GenProject $*;;
	k)shift; Init; KillEm $*;;
	l)shift; Init; tree --noreport  -L 1 * ;;
	x)shift; $EDITOR $self;;
	*)cat <<- EOF 

	Usage: $self g|k|l|x|*

EOF
	;;
esac
