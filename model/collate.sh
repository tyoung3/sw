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

ShowCheck() {
	cat << EOF
	
					Release Checklist 
    	 	* git pull origin master	
		* make check OK?
		* git status
		* git push  	
				
		* git checkout master
    	 	* git pull origin master	
    	 	* make check OK?	
		* git merge --no-ff BRANCH_NAME(Ex. Fix_Comp_names)
		* git tag	
		* [git tag -a  New_VERSION ] 
		* git commit -m "v0.0.?"
		* git push origin VERSION (Ex. git push origin v.0.0.2 )
					OR
		  git push origin --tags  (Pushes all tags to remote)
		  
EOF
}

case $1 in	
	c) make check && echo Success! || echo Check Failed.;;
	j) GenJPG;;
	l) ShowCheck;;
	poc) RunPoC;;
	r) RunCollate;;
	x) $EDITOR collate.sw;;
	*) cat << EOF 
	
USAGE: 
		c		. Make check
		j		. Generate collate jpeg
		l       . Show release check list. 
		poc		. Build and run Proof of Concept 
		r		. Build and run Collate program 
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
	
	

