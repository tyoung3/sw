#!/bin/bash

# MKTEST.SH:  Create sw.test because cannot copy testdata to distribution.

swtest=./sw.test

mkinit() {
	cat <<- EOF > $swtest
#!/bin/bash


pgm=./sw
EOF
}

mkatest() {
	echo 'nn=$((nn=$nn+1))'
	echo 'cat << EOF | $pgm >/dev/null && echo "ok $nn - $cmt" || echo "not ok $nn - $cmt"'
	cat  $swt 
	echo EOF
}

mkftest() {
	echo 'nn=$((nn=$nn+1))'
	echo 'cat << EOF | $pgm >/dev/null && echo "not ok $nn - $cmt" || echo "ok $nn - $cmt"'
	cat  $swt 
	echo EOF
}

mktests() { 
	pushd tests
	for swt in *.sw; do
	    echo "cmt=$swt" >> ../$swtest
		mkatest >> ../$swtest
	done
	 pushd ok2fail
		for swt in *.sw; do
	    	echo "cmt=$swt" >> ../../$swtest
			mkftest >> ../../$swtest
		done
	 popd
	popd
}

mkend() {

echo 'echo   1..$nn # Number of tests to be executed.' >> $swtest
}


mkinit 
mktests
mkend

