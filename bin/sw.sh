#!/bin/bash 

# SW.sh

#https://coderwall.com/p/fasnya/add-git-branch-name-to-bash-prompt

pgm=sw.sh

Die() {
	echo "$pgm/DIE: $*"
	exit 1
}

[ -z $EDITOR  ] && Die  Need to set environment variable: EDITOR
[ -z $BROWSER ] && Die  Need to set environment variable: BROWSER

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
	echo "(Hello Print1)0 <- 0(World Gen1 \"3\"); " 	\
	 | tee /tmp/poc.echo 				\
	 | bin/sw >  $temp/sw/poc/main.go 
	pushd $temp/sw/poc
	[ -f go.mod ] || go mod init poc/poc
	go run main.go 	
}

		# Create collate.jpg 		
GenSVG() { 
	pushd model 
#	make svg && $BROWSER --nosandbox /tmp/collate.svg &
	make svg && $BROWSER  /tmp/collate.svg &
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

GenProject() {
	[ -f ${1}.sw ] || Die Missing PROJECT.SW: ${1}.sw
	 p.sh g  $*
}

Browse () {
	[ -f $1 ] && $BROWSER $1
}

Shell() {
	export sps1="$PS1"
	export PS1="\w> "
	export PATH=$GOPATH/mod/sw/bin:$PATH
	echo Entering StreamWork shell  
	exec bash --rcfile .bashrc  
}

case $1 in	
	c) pushd ./model&& make -j8&&make check&& echo Success! || echo Check Failed.;;
	cl) ShowCheck;;
	d) shift ; RunDocker $*;;
	doc)shift; doxygen&&Browse ./doxy/html/todo.html	\
		&&Browse ./doxy/html/bug.html ;;
        ex)shift; cd example; make;;   
	j) GenSVG;;
	jl) bin/locusts.sh j & ;;	#Display locusts map;
	p)  shift;export DEBUG=y;GenProject $*;;
	poc) RunPoC;;
	rc) RunCollate;;
	rl) bin/locusts.sh r ;;
	s) shift; Shell $;;
	x) $EDITOR sw.sh;;
	*) cat << EOF 
	
USAGE: 
		c		. Make check
		cl       	. Show release check list. 
		d  OPT		. Build and run this script in docker. 
		doc		. Run and browse Doxygen 
		ex		. Run make in ../example/
		j		. Generate collate .SVT
		jl		. Generage locusts .SVG
		p  [NAME..]	. Generate project(s) named NAME... 
		poc		. Build and run Proof of Concept 
		rc		. Build and run Collate program 
		rl		. Run locusts program
		s		. Enter SW shell.  'e' or 'exit' to return
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
	
	

