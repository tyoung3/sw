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
	echo "cat << EOF.$swt | ./sw >/dev/null && echo ok $nn - $cmt || echo not ok $nn - # $cmt"
	cat  $swt 
	echo EOF.$swt
}

mkftest() {
	echo "cat << FAIL.$swt | ./sw >/dev/null && echo not ok $nn - $cmt || echo ok $nn - # $cmt"
	cat  $swt 
	echo FAIL.$swt
}

mktests() { 
	pushd tests
	for swt in *.sw; do
	    nn=$((nn=$nn+1))
	    echo >> ../$swtest
	    cmt=$swt
		mkatest >> ../$swtest
	done
	 pushd ok2fail
	    echo # Test fails >> ../../$swtest
		for swt in *.sw; do
	    	nn=$((nn=$nn+1))
	    	echo >> ../../$swtest
	    	cmt=$swt
			mkftest >> ../../$swtest
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

