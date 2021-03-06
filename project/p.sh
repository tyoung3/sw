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
#	$ ./p.sh g test/X
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
	p=`basename $pn` 
	echo; echo Generating  $p project
	[ -f ${pn}.sw ] || Die Missing ${pn}.sw 
	sw=$dir/$p/${p}.sw 
	[ -d $dir/$p ] || mkdir $dir/$p || Die Cannot mkdir $dir/$p
	[ -f $dir/$p/${p}.sw ] || cp  ${pn}.sw $dir/$p/${p}.sw	
	pushd $dir/$p					\
	   && /home/tyoung3/go/mod/sw/bin/sw -m 5 ${p}.sw > ${p}.sh \
	   && echo;echo Running `pwd`/${p}.sh 	\
	   && /bin/bash ./${p}.sh  
	popd
}

GenProject() {
	Display GenProject for $*
	for pn in $*; do
		Genp $pn & 
	done

}

KillEm() {
	for p in $*; do
		echo Kill $p
	done

}

case $1 in
	g)shift;  GenProject $*;;
	k)shift; Init; KillEm $*;;
	l)shift; Init; tree --noreport  -L 2 $* * ;;
	x)shift; $EDITOR $self;;
	*)cat <<- EOF 

	Usage: $self 
	 	g [PROJECT ...]	. Generate project(s) from PROJECT.sw 
	 	k [JOB...]	. Kill [JOB](s)
	 	l [PROJECT ...] . List PROJECT(s)	
	 	x Edit this script
	 	* Display this help

EOF
	;;
esac
