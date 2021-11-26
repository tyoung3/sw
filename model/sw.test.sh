#!/bin/bash


## (e.g. $(builddir)/filereader $(srcdir)/data/file1.bin)
## .  . $(builddir  $subdir @subdir@ $(subdir)

prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
srcdir=.
echo bindir = $bindir  srcdir = $srcdir

pgm=./sw

tt() {
	nn=$(($nn+1));cmt="$1 $2"; tdata=$2
	$pgm "$GOPATH/sw/model/$tdata" && echo "ok $nn - $cmt" || echo "not ok $nn - $cmt"
}

ttf() {
	nn=$(($nn+1));cmt=$1; tdata=$2
	$pgm "$GOPATH/sw/model/$tdata" && echo "not ok $nn - $cmt " || echo "ok $nn - $cmt" 
}

nn=1; $pgm -v && echo "ok 1 - Version test" || echo "not ok 1 - Version test"
nn=$(($nn+1))
$pgm "$GOPATH/sw/model/tests/aa.sw" && echo "ok $nn - $cmt" || echo "not ok $nn - $cmt"
## tt "Version test" -v; 
#tt "tests/aa.sw"  tests/aa.sw  

for sw_nd in tests/*.sw; do
	tt "$sw_nd" $sw_nd
done

##for sw_nd in tests/ok2fail/*.sw; do
#	ttf "$sw_nd" $sw_nd
#done

echo   1..$nn # Number of tests to be executed.
## ?? breaks  github workflow ../bin/sw.sh poc     
