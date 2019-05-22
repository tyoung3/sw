#!/bin/bash 

# COLLATE.sh

RunCollate() {
	temp=/tmp
	[ -d $temp/sw ] || mkdir $temp/sw
	echo "(Si strings.Print1)0 <- 0(Source strings.Gen1); " | ./sw >  $temp/sw/main.go
	pushd $temp/sw
	[ -f go.mod ] || go mod init collate/collate
	go run main.go 	
}

		# Create collate.jpg 		
GenJPG() {  
	make jpeg
	
	#./sw */coll* 1 > /tmp/collate_SW.dot 
	#dot -Tjpg  /tmp/collate_SW.dot > /tmp/collate_SW.JPG
	#gimp /tmp/collate_SW.JPG
}	

case $1 in	
	j) GenJPG;;
	r) RunCollate;;
	x) $EDITOR collate.sw;;
	*) cat << EOF 
	
USAGE: 
		j		. Generate collate jpeg 
		r		. Build and run Collate program (BUGGY)
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
	
	

