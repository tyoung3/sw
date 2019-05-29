CC = gcc

PGM = ../bin/sw
CCFLAGS = -g -W -Wall

VERSION = \"0.5.2\"

OBJS = ../bnfc/Absyn.o ../bnfc/Lexer.o ../bnfc/Parser.o ../bnfc/Printer.o
SWOBJS = sw.o swmain.o swgo.o swsym.o swgraph.o swjavafbp.o swc.o
HEADERS = ../bnfc/Parser.h ../bnfc/Printer.h ../bnfc/Absyn.h

all:  sw tags 

install: ${PGM}
	sudo cp ${PGM} /usr/local/bin 

tags:   sw.c  swgo.c  swmain.c swsym.c swgo.h model.h sw.h  swmain.h  swsym.h
	ctags *.c *.h

clean:
	rm -f ${SWOBJS}      

poc:	.phony 
	../sw.sh poc 

.phony:  ${PGM} ../sw.sh

check: ${PGM}  ../nds/java.sw ../nds/ac.sw ../nds/aa.sw  ../nds/ab.sw  
	${PGM}  -v 
	! ${PGM} ../nds/e1.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM}  ../nds/e2.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM} ../nds/e3.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM}  ../nds/e4.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	! ${PGM}  ../nds/ac.sw 2>&1 >/dev/null && echo OK_TO_FAIL
	../sw.sh poc     
	${PGM}       ../nds/locusts.sw  >/dev/null
	${PGM}  -m 1 ../nds/collate.sw  >/dev/null
	${PGM}  -m 2 ../nds/collate.sw  >/dev/null
	${PGM}  -m 3 ../nds/collate.sw  >/dev/null
	${PGM}  -m 4 ../nds/java.sw     >/dev/null
	${PGM}  -m 7 ../nds/collate.sw  >/dev/null
	${PGM}  ../nds/aa.sw  >/dev/null
	${PGM}  ../nds/ab.sw  >/dev/null


jpeg:  /tmp/collate.jpg

/tmp/collate.jpg: sw  ../nds/collate.sw
	./sw -m 3 ../nds/collate.sw  > /tmp/collate.dot		\
	&& dot -Tjpg  /tmp/collate.dot > /tmp/collate.jpg 
	
/tmp/sw/locusts.jpg: ../nds/locusts.sw
	./sw -m 3 ../nds/locusts.sw  > /tmp/sw/locusts.dot		\
	&& dot -Tjpg  /tmp/sw/locusts.dot > /tmp/sw/locusts.jpg 
	
${PGM}: ${OBJS}       ${SWOBJS}  
	${CC} ${CCFLAGS} ${OBJS}  ${SWOBJS}  -o sw
	
swsym.o: swsym.c swsym.h 
	${CC} ${CCFLAGS} -c  swsym.c -o swsym.o
		
sw.o: sw.c sw.h swsym.h ${HEADERS}
	${CC} ${CCFLAGS} -c  sw.c -o sw.o 
	
swmain.o: swmain.c sw.h swmain.h ${HEADERS} Makefile
	${CC} ${CCFLAGS} -DVERSION=${VERSION} -c swmain.c -o swmain.o 	
	
swgo.o: swgo.c swgo.h model.h
	${CC} ${CCFLAGS} -c swgo.c -o swgo.o
		
swc.o: swc.c sw.h model.h
	${CC} ${CCFLAGS} -c swc.c -o swc.o	
	
swgraph.o: swgraph.c swgraph.h 
	${CC} ${CCFLAGS} -c swgraph.c -o swgraph.o
	
swjavafbp.o: swjavafbp.c  
	${CC} ${CCFLAGS} -c swjavafbp.c -o swjavafbp.o
	
