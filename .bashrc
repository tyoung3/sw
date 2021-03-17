export SPS1="$PS1"
export PS1="\w> "
alias c='./run c'	
alias cl='./run cl'
alias d='./run d'
alias doc='./run doc'
alias e='exit '
alias j='./run j'
alias jl='./run jl'
alias p='./run p'
alias poc='./run poc'
alias r='./run'	
alias rr='./run r'
alias rl='./run rl'
alias x="$EDITOR"
alias xe='./run x'
alias h='./run --help '
Rest() { 
	cat << EOF
	c		. Build and check StreamWork
	cl       	. Show release check list. 
	d  [OPT]	. Build and run this script in docker. 
	doc		. Run and browse Doxygen 
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
