#!/bin/bash 

# locusts.sh


RunLocusts () {
	temp=/tmp
	[ -d $temp/sw/locusts ] || mkdir -p $temp/sw/locusts 
	./sw */locusts.sw >  $temp/sw/locusts/main.go
	pushd $temp/sw/locusts
	[ -f go.mod ] || go mod init locusts/locusts
	go run main.go 	| grep Match_IV
}


		# Create  .jpg 		
GenJPG() {  
	make /tmp/sw/locusts.jpg && gimp /tmp/sw/locusts.jpg &
}	


case $1 in	
	j) GenJPG;;
	r) RunLocusts;;
	x) $EDITOR locusts.sh nds/locusts.sw;;
	*) cat << EOF 
	
USAGE: 
		j		. Generate locusts jpeg
		r		. Build and run locusts program 
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
	
	

