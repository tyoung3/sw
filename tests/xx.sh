#check_go
PGM=../model/sw
tests=../model/tests
${PGM}  $tests/java.sw 

t() {
 cat << EOF
        ${PGM}  tests/java.sw tests/ac.sw tests/aa.sw  tests/ab.sw  >/dev/null
        ${PGM}  -v 
        ! ${PGM} tests/ac.sw 2>&1 >/dev/null && echo OK_TO_FAIL
        ! ${PGM} tests/e4.sw 2>&1 >/dev/null && echo OK_TO_FAIL
        ! ${PGM} tests/e3.sw 2>&1 >/dev/null && echo OK_TO_FAIL
        ! ${PGM} tests/fail_include.sw 2>&1 >/dev/null && echo OK_TO_FAIL
        ${PGM}  tests/aa.sw  >/dev/null
        ${PGM}  tests/ab.sw  >/dev/null
EOF
}

