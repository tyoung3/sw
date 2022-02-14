#!/bin/bash 

# sw/bin/sw.sh
# Lorca/pipes:  https://github.com/zserge/lorca/issues/43

version="0.19.1"
sw=/usr/local/bin/sw

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

#			Run in swgo/sw (project root)

pushd /usr/local/src/sw/src || Die Cannot find /usr/local/src/sw/src

RunCollate () {
	sw=/usr/local/bin/sw
	[ -x $sw ]|| sw=../bin/sw || Die Cannot find $sw -- run make ? 
	tdir=/tmp/sw$$
	[ -d $tdir ] || mkdir -p $tdir
	$sw nds/collate.sw  >  $tdir/collate.go
	pushd $tdir
	go mod init main
	echo "require github.com/tyoung3/sw latest" >> go.mod
	go mod tidy
	# [ -f go.mod ] || go mod init collate/collate
	go run collate.go 	 
}

RunPoC() {
	temp=/tmp
	## [ -x $sw  ] || pushd ../ 
	[ -x $sw ] || Die  $sw is missing.  Run make install
	tdir=$temp/sw/poc
	[ -d $tdir ] || mkdir -p $tdir
	echo "(Hello Print)0 <- 0(World Gens \"3\"); " 	\
	 | tee $tdir/poc.echo 				\
	 | $sw >  $tdir/poc.go 
	 pushd $tdir
	 	[ -f go.mod ] || (go mod init main && go mod tidy)
	 	go run poc.go  	
}

		# Create collate.jpg 		
GenSVG() { 
	pushd nds || pushd $GOPATH/src/sw/nds
#	make svg && $BROWSER --nosandbox /tmp/collate.svg &
	swgraph collate.sw &
	
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
	## echo /opt/google/chrome/chrome $* 
	[ -f $1 ] && $BROWSER $1
}


## @Shell   Enters a bash subshell 
Shell() {
	pushd ../
	exec bash --rcfile .bashrc  
	echo Entering StreamWork shell  PS1=$PS1
	[ -z $1 ] || pushd ../$1 && bash
	export PATH=`pwd`/bin:$PATH
}

case $1 in	
    bw|buildw) cd ../;
    	make distclean 
        ./configure --host=x86_64-w64-mingw32 && make || Die configure/make failed.
    	pushd ./build-aux || Die Cannot pushd ./build-aux
        [ -z $rtn ] || make -j8  distcheck 
   	;;
    auto|b|build) 
    	cd ../
    	[ -f src/Makefile.am ] || Die Missing src/Makefile.am
    	pushd src/model
    		./mktest.sh || Die Failed making sw.test script
    	popd
        aclocal # Set up an m4 environment && \
        autoconf # Generate configure from configure.ac && \
        automake  --add-missing # Generate Makefile.in from Makefile.am && \
        ./configure # Generate Makefile from Makefile.in && \
        # make -j8  distcheck # Use Makefile to build and test a tarball to distribute	&& echo Success!! || echo Build Error
        ;; 
    c)pushd model; make -j8 check    && echo -e ${green}Success!$reset || echo  -e ${red}Check Failed.$reset;; 
	cxxx) pushd ./model&& make -j8&&make check&& echo -e ${green}Success!$reset || echo  -e ${red}Check Failed.$reset;;
	cl) ShowCheck;;
	dbuild) shift ; BuildDocker $*;;
	d)shift; RunDocker $*;;
	doc)cd ../; shift; doxygen docs/Doxyfile&&Browse ./docs/doxy/html/index.html;;
    ex)shift; cd example; make;; 
	j) GenSVG;;
	jl) ../bin/swlocusts j & ;;	#Display locusts map;
	p)  echo $*; shift
		nd=$1 
		[ -z $1 ] && export nd="postage.sw" && pushd nds ; # Get good sw.cfg
		shift
		swproject g  $nd $*  ;;
	poc) RunPoC;;
	rc) RunCollate;;
	rl) ../bin/swlocusts r ;;
	rm) pushd ../
	    #pandoc -r gfm SECURITY.md > /tmp/SW_SECURITY.html;$BROWSER /tmp/SW_SECURITY.html &
	    pandoc -r gfm README.md > /tmp/SW_README.html;$BROWSER /tmp/SW_README.html &
	    $BROWSER https://sw.twyoung.com 
	   ;;
	s) shift; Shell $*;;
	v|version) echo sw.sh-v$version;;
	x) $EDITOR $0 &;;
	*) cat << EOF 
	
sw.sh-$version USAGE: 
		b|build		. Build project with Autotools.
		c		. Make check
		cl       	. Show release check list. 
		d  [OPTs]	. Switch to docker container. 
		e		. Exit SW shell.
		d build [OPTs]	. Build SWdemo docker container. 
		doc		. Run and browse Doxygen 
		j		. Graph collate.sw with swgraph
		jl		. Generate and view locusts.png 
		p  [NAME..]	. Generate project(s) named NAME[default nds/postage.sw]
		poc		. Build and run Proof of Concept 
		rm		. View README in $BROWSER 
		rc		. Build and run Collate program 
		rl		. Run locusts program
		s		. Enter SW shell.  'e' to exit the shell. 
		v		. Display this script version
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
#########################   End of script   ############################
