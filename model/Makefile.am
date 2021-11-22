# sw/model/MAKEFILE.AM

AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = sw
sw_SOURCES =  sw.c swconfig.c swgraph.c swmain.c swsym.c swc.c  swgo.c  swjavafbp.c  swproject.c

sw_HEADERS = model.h  swconfig.h  swgo.h  swgraph.h	sw.h  swmain.h	swsym.h

swdir = ./

CFLAGS =  -DMAJOR=${SW_MAJOR} -DMINOR=${SW_MINOR} -DLEVEL=${SW_LEVEL} $(AM_CFLAGS)

sw_LDADD =  ../bnfc/Absyn.o ../bnfc/Lexer.o ../bnfc/Parser.o ../bnfc/Printer.o

PGM = ./${bin_PROGRAMS} 
check-local: 
###in_PROGRAMS}  tests/java.sw tests/ac.sw tests/aa.sw  tests/ab.sw  >/dev/null
	${PGM}  -v 
	! ${PGM} tests/ac.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/e4.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/e3.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/fail_include.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	
	${PGM}  tests/aa.sw  >/dev/null
	${PGM}  tests/ab.sw  >/dev/null
	${PGM}  tests/ad.sw  >/dev/null
	${PGM}  tests/ae.sw  >/dev/null
	${PGM}  tests/aef.sw  >/dev/null
	
	${PGM}       ../nds/locusts.sw  >/dev/null
	${PGM}  -m 1 ../nds/collate.sw  >/dev/null  
	${PGM}  -m 2 ../nds/collate.sw  >/dev/null
	${PGM}  -m 3 ../nds/collate.sw  >/dev/null
	${PGM}  -m 4 tests/java.sw     >/dev/null	 
	${PGM}  -m 7 ../nds/collate.sw  >/dev/null
	
	${PGM}  tests/aj.sw   >/dev/null
	${PGM}  tests/asj.sw   >/dev/null
	${PGM}  tests/aj2.sw   >/dev/null
	${PGM}  tests/aaR.sw  >/dev/null
	${PGM}  tests/h1.sw   >/dev/null  

	${PGM}  tests/h2.sw   >/dev/null
	${PGM}  tests/n1.sw   >/dev/null
	${PGM}  tests/n2.sw   >/dev/null
	${PGM}  tests/n3.sw   >/dev/null
	${PGM}  tests/n4.sw   >/dev/null
	${PGM}  tests/n5.sw   >/dev/null
	${PGM}  tests/tag.sw   >/dev/null
	
	${PGM} -m 2 tests/subnet1.sw   >/dev/null
	${PGM} -m 2 tests/sn2.sw   >/dev/null
	
	${PGM}  tests/lr.sw   >/dev/null
	${PGM}  tests/lrR.sw   >/dev/null  
	${PGM}  tests/sisub.sw   >/dev/null
	${PGM}  tests/var.sw   >/dev/null
	${PGM}  tests/module.sw   >/dev/null
	${PGM}  tests/inc.sw   >/dev/null
	${PGM}  tests/combo.sw   >/dev/null
	${PGM}  tests/prefix.sw   >/dev/null
## ?? breaks  github workflow ../bin/sw.sh poc     

