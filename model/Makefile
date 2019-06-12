CC = gcc

PGM = ../bin/sw
CCFLAGS = -g -W -Wall

VERSION = \"0.7.6\"

LATEX = latex
DVIPS = dvips

OBJS = ../bnfc/Absyn.o ../bnfc/Lexer.o ../bnfc/Parser.o ../bnfc/Printer.o
SWOBJS = sw.o swmain.o swgo.o swsym.o swgraph.o swjavafbp.o swc.o
HEADERS = ../bnfc/Parser.h ../bnfc/Printer.h ../bnfc/Absyn.h

all:  ../bin/sw tags SW.pdf

install: ${PGM}
	sudo cp ${PGM} /usr/local/bin 

tags:   sw.c  swgo.c  swmain.c swsym.c swgo.h model.h sw.h  swmain.h  swsym.h
	ctags *.c *.h

clean:
	rm -f ${SWOBJS}      

poc:	.phony 
	../sw.sh poc 

.phony:  ${PGM} ../sw.sh

SW.ps: SW.dvi
	${DVIPS} SW.dvi -o SW.ps
	
SW.dvi: ../bnfc/SW.tex
	${LATEX} ../bnfc/SW.tex
        
SW.pdf:  SW.ps
	ps2pdf SW.ps
            

check: ${PGM}  tests/java.sw tests/ac.sw tests/aa.sw  tests/ab.sw  
	${PGM}  -v 
	! ${PGM} tests/e1.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/nds/e2.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/e3.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/e4.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} tests/ac.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	${PGM}       ../nds/locusts.sw  >/dev/null
	${PGM}  -m 1 ../nds/collate.sw  >/dev/null
	${PGM}  -m 2 ../nds/collate.sw  >/dev/null
	${PGM}  -m 3 ../nds/collate.sw  >/dev/null
	${PGM}  -m 4 tests/java.sw     >/dev/null
	${PGM}  -m 7 ../nds/collate.sw  >/dev/null
	${PGM}  tests/aa.sw  >/dev/null
	${PGM}  tests/ab.sw  >/dev/null
	${PGM}  tests/ad.sw  >/dev/null
	${PGM}  tests/ae.sw  >/dev/null
	${PGM}  tests/aef.sw  >/dev/null
	${PGM}  tests/sisub.sw   >/dev/null
	../sw.sh poc     
	${PGM} -m 2 tests/subnet1.sw   >/dev/null


svg:  .phsvg 
	dot -Tsvg  /tmp/collate.dot > /tmp/collate.svg

.phsvg: /tmp/collate.dot
		
/tmp/collate.dot: ../bin/sw  ../nds/collate.sw
	../bin/sw -m 3 ../nds/collate.sw > /tmp/collate.dot
	
jpeg:  /tmp/collate.jpg

/tmp/collate.jpg: sw  ../nds/collate.sw
	./sw -m 3 ../nds/collate.sw  > /tmp/collate.dot		\
	&& dot -Tjpg  /tmp/collate.dot > /tmp/collate.jpg 
	
/tmp/sw/locusts.jpg: ../nds/locusts.sw
	./sw -m 3 ../nds/locusts.sw  > /tmp/sw/locusts.dot		\
	&& dot -Tjpg  /tmp/sw/locusts.dot > /tmp/sw/locusts.jpg 
	
${PGM}: ${OBJS} ${SWOBJS}  
	${CC} ${CCFLAGS} ${OBJS}  ${SWOBJS}  -o ../bin/sw
	
swsym.o: swsym.c swsym.h 
	${CC} ${CCFLAGS} -c  swsym.c -o swsym.o
		
sw.o: sw.c sw.h swsym.h ${HEADERS} model.h
	${CC} ${CCFLAGS} -c  sw.c -o sw.o 
	
swmain.o: swmain.c sw.h swgo.h swgraph.h swsym.h swmain.h ${HEADERS} Makefile  model.h
	${CC} ${CCFLAGS} -DVERSION=${VERSION} -c swmain.c -o swmain.o 	
	
swgo.o: swgo.c swgo.h swsym.h sw.h model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swgo.c -o swgo.o
		
swc.o: swc.c sw.h model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swc.c -o swc.o	
	
swgraph.o: swgraph.c swgraph.h model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swgraph.c -o swgraph.o
	
swjavafbp.o: swjavafbp.c  model.h ${HEADERS}
	${CC} ${CCFLAGS} -c swjavafbp.c -o swjavafbp.o
	
