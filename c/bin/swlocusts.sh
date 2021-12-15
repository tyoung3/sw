#!/bin/bash 

# locusts.sh

Die() {
	echo "Locusts.sh/DIE: $*"
	exit 1
}

[ -z $VIEWOR ] && VIEWOR=eog

swdir=./model
[ -e $swdir/sw ] || swdir=/usr/local/bin
SW=$swdir/sw
[ -e $SW     ] || Die $SW is missing 

temp=/tmp
dir=$temp/sw
[ -d $dir ] || mkdir -p  $dir || Die Cannot mkdir $dir

RunLocusts () {
	[ -d /tmp/x/ ] || mkdir /tmp/x || Die Cannot mkdir /tmp/x/
	#mv $dir/* /tmp/x/ 2>&1 >/dev/null
	$SW nds/locusts.sw >  $dir/locusts.go
	pushd $dir
	go mod init locusts/locusts
	go mod tidy
	echo;echo "Dates for Missouri brood XIX(13 year) and brood IV(17 year) locusts" 
	go run $dir/locusts.go 		\
	|tee $dir/locusts.txt \
	| grep MISSOURI 	\
	&& echo&&echo Dates for Washington brood XIX and brood X, appearing two years early  \
	&&grep WASH $dir/locusts.txt  \
	&& echo&&echo  Matches in 2019	\
	&& grep MATCH_QQ $dir/locusts.txt
}


		# Create  .jpg 		
GenJPG() {  
	cd model   \
	&& sw -m 3 ../nds/locusts.sw  > /tmp/sw/locusts.dot		\
	&& dot -Tpng /tmp/sw/locusts.dot > /tmp/sw/locusts.png	\
	&& $VIEWOR /tmp/sw/locusts.png &
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

