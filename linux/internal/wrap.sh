#!/bin/bash 

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
