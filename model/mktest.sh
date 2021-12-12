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
	echo "cat << EOF.$swt | ./sw >/dev/null && echo ok $nn - $cmt || echo not ok $nn -  $cmt"
	cat  $swt 
	echo EOF.$swt
}

mkftest() {
	echo "cat << FAIL.$swt | ./sw >/dev/null && echo not ok $nn - $cmt || echo ok $nn - $cmt"
	cat  $swt 
	echo FAIL.$swt
}

mkfbptest() {
	echo "./sw -m 8 $swt >/dev/null && echo ok $nn - $cmt || echo not ok $nn - $cmt" 
}

mktests() { 
	pushd tests
	for swt in *.sw; do
	    nn=$((nn=$nn+1))
	    echo >> ../$swtest
	    cmt=$swt
		mkatest >> ../$swtest
	done
	
	# echo # OK to Fail: 
	  pushd ok2fail
	    echo # Test fails >> ../../$swtest
		for swt in *.sw; do
	    	nn=$((nn=$nn+1))
	    	echo >> ../../$swtest
	    	cmt=FAILOK/$swt
			mkftest >> ../../$swtest
		done
	  popd
	  
	  pushd gofbp
		for swt in *.sw; do
	    	nn=$((nn=$nn+1))
	    	echo >> ../../$swtest
	    	cmt=GOFBP/$swt
	    	swt="tests/gofbp/$swt"
			mkfbptest >> ../../$swtest
		done
	  popd 
	popd
}

mkend() {

	echo "echo  1..$nn # Number of tests to be executed." >> $swtest
}


mkinit 
mktests
mkend

