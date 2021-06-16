#!/bin/bash 

# SW.sh

version="0.0.1"

ShowGitBranch() {
	cat <<EOF >/dev/null
#https://coderwall.com/p/fasnya/add-git-branch-name-to-bash-prompt
~/.bash_profile
parse_git_branch() {
     git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

export PS1="\u@\h \[\033[32m\]\w\[\033[33m\]\$(parse_git_branch)\[\033[00m\] $ "

EOF
}

pgm=sw.sh

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
        
Die() {
	echo -e "$red$pgm/DIE: $*$reset"
	exit 1
}

# [ -z $EDITOR  ] && Die  Need to set environment variable: EDITOR
# [ -z $BROWSER ] && Die  Need to set environment variable: BROWSER

RunCollate () {
	temp=/tmp
	[ -d bin ] || pushd ../
	[ -x bin/sw ]|| Die Cannot find bin/sw -- run make ? 
	[ -d $temp/sw/ ] || mkdir -p $temp/sw/ 
	bin/sw nds/collate.sw  >  $temp/sw/collate.go
	pushd $HOME
	# [ -f go.mod ] || go mod init collate/collate
	go run $temp/sw/collate.go 	 
}

RunPoC() {
	temp=/tmp
	[ -x bin/sw  ] || pushd ../ 
	[ -x bin/sw  ] || Die  bin/sw is missing.  Run make 
	[ -d $temp/sw/poc ] || mkdir -p $temp/sw/poc
	echo "(Hello Print)0 <- 0(World Gens \"3\"); " 	\
	 | tee /tmp/poc.echo 				\
	 | bin/sw >  $temp/sw/poc.go 
	 pushd $HOME
	# [ -f go.mod ] || go mod init poc/poc
	go run $temp/sw/poc.go  	
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
	Release Checklist
	
	Make all changes in a subsidiary(not master) branch 
	Run 'go test ./...'  before release	
	(g?) commands are sw shell aliases
	
On Branch:	
					 
		* git add -u (ga) 
    	 	* git pull origin master	
		* make check OK?
		* git status(gs) 
		* git push  	

On Master 		
		* git checkout master	
    	 	* git pull origin master	
    	 	* make check OK?	
		* gb NEW_BRANCH 	
		* git merge --no-ff BRANCH_NAME(Ex. Fix_Comp_names) (gm BRANCH) 

New version?:		
		* Change version in README.md, Makefile, and Doxygen and rebuild.
		* git tag	
		* [git tag -a  New_VERSION ] 
		* git commit -m "v0.0.?"  (gc "COMMIT MESSAGE")
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

RunDocker() {    # To install see:  https://docs.docker.com/engine/install/ubuntu/#prerequisites
	myapp=sw 	
	docker run -it --rm -e MY_APP=ma -e EDITOR=nano -e BROWSER=none --name SWdemo   $myapp
 
}

BuildDocker() {    # To install see:  https://docs.docker.com/engine/install/ubuntu/#prerequisites
	myapp=sw
	docker ps |grep SWdemo 			\
	|| docker build --build-arg EDITOR=nano -t  $myapp .   
	RunDocker 	
}

Browse () {
	[ -f $1 ] && $BROWSER $1
}


## @Shell   Enters a bash subshell 
Shell() {
	#export sps1="$PS1"
	#export PS1="\u@\h \[\033[32m\]\w\[\033[33m\]\$(parse_git_branch)\[\033[00m\] $ "
	# export PS1="\u@\h \[\033[32m\]\[\033[33m\]\$(parse_git_branch)\[\033[00m\] $ "
	export PATH=`pwd`/bin:$PATH
	echo Entering StreamWork shell  PS1=$PS1
	exec bash --rcfile .bashrc  
}

case $1 in	
	c) pushd ./model&& make -j8&&make check&& echo -e ${green}Success!$reset || echo  -e ${red}Check Failed.$reset;;
	cl) ShowCheck;;
	dbuild) shift ; BuildDocker $*;;
	d)shift; RunDocker $*;;
	doc)shift; doxygen docs/Doxyfile&&Browse ./docs/doxy/html/todo.html	\
		&&Browse ./docs/doxy/html/bug.html ;;
        ex)shift; cd example; make;;   
	j) GenSVG;;
	jl) bin/locusts.sh j & ;;	#Display locusts map;
	p)  shift;project.sh g  $*;;
	poc) RunPoC;;
	rc) RunCollate;;
	rl) bin/locusts.sh r ;;
	rm) pandoc -r gfm README.md > /tmp/SW_README.html; $BROWSER /tmp/SW_README.html;;
	s) shift; Shell $;;
	x) $EDITOR $0;;
	*) cat << EOF 
	
sw.sh-$version USAGE: 
		c		. Make check
		cl       	. Show release check list. 
		d  [OPTs]	. Switch to docker container. 
		dbuild [OPTs]	. Build SWdemo docker container. 
		doc		. Run and browse Doxygen 
		j		. Generate collate .SVT
		jl		. Generage locusts .SVG
		p  [NAME..]	. Generate project(s) named NAME... 
		poc		. Build and run Proof of Concept 
		rm		. View README in $BROWSER 
		rc		. Build and run Collate program 
		rl		. Run locusts program
		s		. Enter SW shell.  'e' or 'exit' to return
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
#########################   End of script   ############################
