#!/bin/bash 





Default() {
p="WS:"
read line 
echo "$p recvd" $line
read line 
echo "$p recvd" $line
read line 
echo "$p recvd" $line
read line 
echo "$p recvd" $line
echo "$p stdout" 
echo "$p stderr" >&2 
cat wrap.txt
}

Succeed() {
	n=$(($n+1))
	echo  $n > /tmp/wrap.out
}

Benchmark() {
	pushd ../
	loop=0
	while [ $loop -lt $1 ]; do  
		go test -v >/dev/null && echo -n   "$loop " > /dev/shm/wrap.out      || exit 2
		loop=$(($loop+1))
	done	
	popd
}

case $1 in 
	b) shift; Benchmark $* ;;
	*) Default;;
esac	
