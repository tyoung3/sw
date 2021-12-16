#!/bin/bash

n=10

[ -z $1 ] || n=$1

mkMany() {
	
	while [ $((i=i+1)) -lt $n ] ; do
		echo "(A$i a) -> (B$i b);"
	done

}

mkMany 
