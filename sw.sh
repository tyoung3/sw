#!/bin/bash 

# COLLATE.sh

Die() {
	echo "$0/DIE: $*"
	exit 1
}

RunCollate () {
	temp=/tmp
	[ -d bin ] || pushd ../
	[ -x bin/sw ]|| Die Cannot find bin/sw -- run make ? 
	[ -d $temp/sw/collate ] || mkdir -p $temp/sw/collate 
	bin/sw nds/collate.sw |gofmt >  $temp/sw/collate/main.go
	pushd $temp/sw/collate
	[ -f go.mod ] || go mod init collate/collate
	go run main.go 	 
}

RunPoC() {
	temp=/tmp
	[ -x bin/sw  ] || pushd ../ 
	[ -x bin/sw  ] || Die  bin/sw is missing.  Run make 
	[ -d $temp/sw/poc ] || mkdir -p $temp/sw/poc
	echo "(Hello Print1)0 <- 0(World Gen1\"3\"); " 	\
	 | bin/sw >  $temp/sw/poc/main.go 
	pushd $temp/sw/poc
	[ -f go.mod ] || go mod init poc/poc
	go run main.go 	
}

		# Create collate.jpg 		
GenSVG() { 
	pushd model 
	make svg && $BROWSER --nosandbox /tmp/collate.svg &
	#./sw */coll* 1 > /tmp/collate_SW.dot 
	#dot -Tjpg  /tmp/collate_SW.dot > /tmp/collate_SW.Jnetwork_languagePG
	#gimp /tmp/collate_SW.JPG
}	

ShowCheck() {
	cat << EOF

		* git add -u 
On Branch:	
					Release Checklist 
    	 	* git pull origin master	
		* make check OK?
		* git status
		* git push  	

On Master 				
		* git checkout master
    	 	* git pull origin master	
    	 	* make check OK?	
		* git merge --no-ff BRANCH_NAME(Ex. Fix_Comp_names)

New version?:		
		* git tag	
		* [git tag -a  New_VERSION ] 
		* git commit -m "v0.0.?"
		* git push origin VERSION (Ex. git push origin v0.10.0 )
					OR
		  git push origin --tags  (Pushes all tags to remote)

Remove Branch:		
	  * git branch -d branchname 
	       * git push origin --delete branchname
		   * git branch	 
			* git checkout -b NEWBRANCH      	  
EOF
}

RunDocker() {
	myapp=sw
	docker build -t  $myapp . &&  	\
	docker run -it --rm --name SWdemo  $myapp ./sw.sh $*
}

case $1 in	
	c) pushd ./model&& make -j8&&make check&& echo Success! || echo Check Failed.;;
	cl) ShowCheck;;
	d) shift ; RunDocker $*;;
	doc)shift; doxygen&&$BROWSER ./doxy/html/index.html;;
	j) GenSVG;;
	jl) bin/locusts.sh j ;;	#Display locusts map;
	poc) RunPoC;;
	r) RunCollate;;
	rl) bin/locusts.sh r ;;
	x) $EDITOR nds/collate.sw sw.sh;;
	*) cat << EOF 
	
USAGE: 
		c		. Make check
		cl       	. Show release check list. 
		d  OPT		. Build and run this script in docker. 
		doc		. Run and browse Doxygen 
		j		. Generate collate .SVT
		jl		. Generage locusts .SVG
		poc		. Build and run Proof of Concept 
		r		. Build and run Collate program 
		rl		. Run locusts program
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
	
	

