CC = gcc

PGM = ../bin/sw
CCFLAGS = --static -g -pg -W -Wall

VERSION = \"0.12.2\"

LATEX = latex
DVIPS = dvips

OBJS = ../bnfc/Absyn.o ../bnfc/Lexer.o ../bnfc/Parser.o ../bnfc/Printer.o
SWOBJS = sw.o swmain.o swgo.o swsym.o swgraph.o swjavafbp.o swc.o swconfig.o swproject.o
HEADERS = ../bnfc/Parser.h ../bnfc/Printer.h ../bnfc/Absyn.h

all:  ../bin/sw tags  

install: ${PGM}
	sudo cp ${PGM} ../bin/swgraph ../bin/swgo ${GOPATH}/bin

tags:   sw.c  swgo.c  swmain.c swsym.c swproject.c swgo.h model.h sw.h swconfig.c swmain.h  swsym.h
	ctags *.c *.h

clean:
	rm -f ${SWOBJS}      

poc:	.phony 
	../bin/sw.sh poc 

.phony:  ${PGM} ../bin/sw.sh

SW.ps: SW.dvi
	${DVIPS} SW.dvi -o SW.ps
	
SW.dvi: ../bnfc/SW.tex
	${LATEX} -output-format=dvi ../bnfc/SW.tex
        
SW.pdf:  ../bnfc/SW.tex
	( pdftex ../bnfc/SW.tex; echo OK ) 
            
../bnfc/Absyn.o: ../bnfc/Absyn.c 
	make -C ../bnfc

check:
	${PGM}  tests/java.sw tests/ac.sw tests/aa.sw  tests/ab.sw  >/dev/null
	${PGM}  -v 
	! ${PGM} tests/ac.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/e4.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/e3.sw 2>&1 >/dev/null && echo OK_TO_FAIL
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
	#  ../bin/sw.sh poc     


svg:  .phsvg 
	dot -Tsvg  /tmp/collate.dot > /tmp/collate.svg

.phsvg: /tmp/collate.dot
		
/tmp/collate.dot: ../bin/sw  ../nds/collate.sw
	../bin/sw -m 3 ../nds/collate.sw > /tmp/collate.dot
	
jpeg:  /tmp/collate.jpg

/tmp/collate.jpg: sw  ../nds/collate.sw
	./sw -m 3 ../nds/collate.sw  > /tmp/collate.dot		\
	&& dot -Tjpg  /tmp/collate.dot > /tmp/collate.jpg 
	
/tmp/sw/locusts.png: ../nds/locusts.sw
	./sw -m 3 ../nds/locusts.sw  > /tmp/sw/locusts.dot		\
	&& dot -Tpng /tmp/sw/locusts.dot > /tmp/sw/locusts.png
	
${PGM}: ${OBJS} ${SWOBJS}  
	${CC} ${CCFLAGS} ${OBJS}  ${SWOBJS} -lyaml -o ../bin/sw
	
swsym.o: swsym.c swsym.h 
	${CC} ${CCFLAGS} -c  swsym.c -o swsym.o

swconfig.o: swconfig.c sw.h swconfig.h
	${CC} ${CCFLAGS} -c  swconfig.c -o swconfig.o
		
sw.o: sw.c sw.h swsym.h ${HEADERS} model.h
	${CC} ${CCFLAGS} -c  sw.c -o sw.o 
	
swmain.o: swmain.c sw.h swgo.h swgraph.h swsym.h swmain.h swconfig.h ${HEADERS} Makefile  model.h
	${CC} ${CCFLAGS} -DVERSION=${VERSION} -c swmain.c -o swmain.o 	
	
swgo.o: swgo.c swgo.h swsym.h sw.h model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swgo.c -o swgo.o
	
swproject.o: swproject.c swsym.h sw.h model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swproject.c -o swproject.o
		
swc.o: swc.c sw.h model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swc.c -o swc.o	
	
swgraph.o: swgraph.c swgraph.h model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swgraph.c -o swgraph.o
	
swjavafbp.o: swjavafbp.c  model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swjavafbp.c -o swjavafbp.o
	
