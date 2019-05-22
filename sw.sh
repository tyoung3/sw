#!/bin/bash

scr=sw.sh	

Die() {
	echo "$scr/DIE: $*"
	exit 1
}

ToDO() {
	cat <<- EOF 
	
	#SW/ToDo:
	 . Fix Go channels  
	 . Color Go processes and edges green in Dot 
	 . Switch to GoLand
	 . Commit this script 
	 . Generate Go/Component skeleton code
	 . Generate JavaFBP network definitions  [BRANCH: Generate_Graph_Input]
	 . Build C programs                      [BRANCH: Generate_C_code]
	 
EOF
}

# curl https://raw.githubusercontent.com/golang/dep/master/install.sh | sh
BuildModel() {
	pushd nemod || Die xx
	# Die Cannot cd to ./nemod
	[ -f sw.c ] || Die Missing sw.c 
	[ -f Makefile ] || Die Missing ../nemod/Makefile 
	make all
}

BuildIt() {
	if [ -f Makefile ]
		then bnfc --c    $* SW.cf && make && BuildModel
	else		   
		bnfc --c -m $* SW.cf && make && BuildModel
	fi	
}

case $1 in
	b)BuildIt;;
	j)cd nemod; ./collate.sh j;;
	poc) cd nemod; ./collate.sh r;;
	v)gimp /tmp/collate.jpg;;
	x)$EDITOR $scr;;
	*)cat << EOF
	
USAGE:  $scr
	b		. Build sw from SW.cf
	j		. Generate and view /tmp/collate.jpg 
	poc 		. Run PoC (Build and run simplistic Go program)  
	v		. View collate.jpg
	x		. Edit this script
	--help		. Show this usage 
	   		
EOF
	;;
esac

