#!/bin/bash 

# locusts.sh

Die() {
	echo "Locusts.sh/DIE: $*"
	exit 1
}

RunLocusts () {
	temp=/tmp
	dir=$temp/sw/locusts
	[ -d /tmp/x/ ] || mkdir /tmp/x || Die Cannot mkdir /tmp/x/
	mv $dir/* /tmp/x/ 2>&1 >/dev/null
	[ -d $dir ] || mkdir -p  $dir || Die Cannot mkdir $dir
	bin/sw nds/locusts.sw >  $dir/main.go
	pushd $dir
	[ -f go.mod ] || go mod init locusts/locusts
	echo;echo "Dates for Missouri brood XIX(13 year) and brood IV(17 year) locusts" 
	go run main.go 		\
	|tee $dir/locusts.txt \
	| grep MISSOURI 	\
	&& echo&&echo Dates for Washington brood XIX and brood X, appearing two years early  \
	&&grep WASH $dir/locusts.txt  \
	&& echo&&echo  Matches in 2019	\
	&& grep MATCH_QQ $dir/locusts.txt
}


		# Create  .jpg 		
GenJPG() {  
	pushd model
	make /tmp/sw/locusts.png  && gimp /tmp/sw/locusts.png &
}	


case $1 in	
	j) GenJPG;;
	r) RunLocusts;;
	x) $EDITOR bin/locusts.sh nds/locusts.sw;;
	*) cat << EOF 
	
USAGE: 
		j		. Generate locusts jpeg
		r		. Build and run locusts program 
		x		. Edit this script
		--help	. Display this help
		
EOF
	;;	
					
esac	 
	
	

