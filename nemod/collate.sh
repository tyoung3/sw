#!/bin/bash 

# COLLATE.sh


RunCollate () {
	temp=/tmp
	[ -d $temp/sw/collate ] || mkdir $temp/sw/collate 
	./sw */collate.sw >  $temp/sw/collate/main.go
	pushd $temp/sw/collate
	[ -f go.mod ] || go mod init collate/collate
	go run main.go 	
}

RunPoC() {
	temp=/tmp
	[ -d $temp/sw/poc ] || mkdir -p $temp/sw/poc
	echo "(Si strings.Print1)0 <- 0(Source strings.Gen1); " 	\
	 | ./sw >  $temp/sw/poc/main.go 
	pushd $temp/sw/poc
	[ -f go.mod ] || go mod init poc/poc
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
	c) make check && echo Success! || echo Check Failed.;;
	j) GenJPG;;
	poc) RunPoC;;
	r) RunCollate;;
	x) $EDITOR collate.sw;;
	*) cat << EOF 
	
USAGE: 
		c		. Make check
		j		. Generate collate jpeg 
		poc		. Build and run Proof of Concept 
		r		. Build and run Collate program 
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
	
	

