alias c='./run c'	
alias cl='./run cl'
alias d='./run d'
alias dir='ls -Fl'
alias doc='./run doc'
alias e='exit '
alias ga='git add -u'
alias gb='git branch '
alias gc='git commit -m $*'
alias gch='git checkout'
alias gm='git merge --no-ff'
alias gp='git push'
alias gpl='git pull'
alias gpm='git pull origin master'
alias gs='git status'
alias gt='git tag'
alias j='./run j' 
alias jl='./run jl'
alias p='./run p'
alias poc='./run poc'
alias r='./run'	
alias rr='./run r'
alias rl='./run rl'
alias x="$EDITOR"
alias xe='gedit `which sw.sh` '
alias h='./run --help '


parse_git_branch() {
     git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

export PS1="\u@\h \[\033[32m\]\w\[\033[33m\]\$(parse_git_branch)\[\033[00m\] $ "
export PATH="$HOME/go/bin:$PATH"	
	
Rest() { 
	cat << EOF
	c		. Build and check StreamWork
	cl       	. Show release check list. 
	d  [OPT]	. Build and run this script in docker.
	dir [PATH]	. ls -Fltr [PATH]  
	doc		. Run and browse Doxygen.
	e		. Exit shell.
	ga		. git add -u
	gb [OPTS}	. git branch [OPTS]
	gc MSG		. git commit -m MSG
	gch BRANCH	. git checkout BRANCH
	gp		. git push
	gpl BRANCH 	. git pull BRANCH
	gpm		. git Pull master
	gs		. git status
	j		. Generate collate .SVT
	jl		. Generage locusts .SVG
	p  [NAME..]	. Generate project(s) named NAME... 
	poc		. Build and run Proof of Concept 
	rc		. Build and run Collate program 
	rl		. Run locusts program
	xe		. Edit sw.sh script
	h		. Display help
EOF
}

Rest
