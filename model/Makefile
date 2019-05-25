CC = gcc

CCFLAGS = -g -W -Wall
#CCFLAGS = -O6 -W -Wall

VERSION = \"0.4.0\"

OBJS = Absyn.o Lexer.o Parser.o Printer.o

all:  sw tags 

install: sw
	sudo cp ./sw /usr/local/bin 

tags:   sw.c  swgo.c  swmain.c swsym.c swgo.h model.h sw.h  swmain.h  swsym.h

	ctags *.c *.h

clean:
	rm -f sw.o swnom.o    ${OBJS} Parser.h Printer.h Absyn.h

poc:	run 

run:  sw
	./collate.sh poc 

check: sw nds/java.sw nds/ac.sw nds/aa.sw  nds/ab.sw  
	./sw -v 
	./sw -m 1 nds/collate.sw  >/dev/null
	./sw -m 2 nds/collate.sw  >/dev/null
	./sw -m 3 nds/collate.sw  >/dev/null
	./sw -m 4 nds/java.sw     >/dev/null
	./sw -m 7 nds/collate.sw  >/dev/null
	./sw nds/aa.sw  >/dev/null
	./sw nds/ab.sw  >/dev/null
	! ./sw nds/ac.sw 2>&1 >/dev/null && echo OK_TO_FAIL


jpeg:  /tmp/collate.jpg

/tmp/collate.jpg: sw  nds/collate.sw
	./sw -m 3 */collate.sw  > /tmp/collate.dot		\
	&& dot -Tjpg  /tmp/collate.dot > /tmp/collate.jpg 
	
/tmp/sw/locusts.jpg: nds/locusts.sw
	./sw -m 3 nds/locusts.sw  > /tmp/sw/locusts.dot		\
	&& dot -Tjpg  /tmp/sw/locusts.dot > /tmp/sw/locusts.jpg 
	
sw: ${OBJS}                   sw.o swmain.o swgo.o swsym.o swgraph.o swjavafbp.o swc.o 
	${CC} ${CCFLAGS} ${OBJS}  sw.o swmain.o swgo.o swsym.o swgraph.o swjavafbp.o swc.o -o sw
	
swsym.o: swsym.c swsym.h 
	${CC} ${CCFLAGS} -c  swsym.c -o swsym.o
		
sw.o: sw.c sw.h swsym.h Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c  sw.c -o sw.o 
	
swmain.o: swmain.c sw.h swmain.h Parser.h Printer.h Absyn.h Makefile
	${CC} ${CCFLAGS} -DVERSION=${VERSION} -c swmain.c -o swmain.o 	
	
swgo.o: swgo.c swgo.h model.h
	${CC} ${CCFLAGS} -c swgo.c -o swgo.o
		
swc.o: swc.c sw.h model.h
	${CC} ${CCFLAGS} -c swc.c -o swc.o	


swgraph.o: swgraph.c swgraph.h 
	${CC} ${CCFLAGS} -c swgraph.c -o swgraph.o
	
swjavafbp.o: swjavafbp.c  
	${CC} ${CCFLAGS} -c swjavafbp.c -o swjavafbp.o
	
Absyn.h: ../Absyn.h
	cp -s ../Absyn.h ./	
	
Printer.h: ../Printer.h
	cp -s ../Printer.h ./
	
Parser.h: ../Parser.h
	cp -s ../Parser.h ./
	 
Absyn.o: ../Absyn.o		 
	cp -s ../Absyn.o	  ./ 
	 
Lexer.o: ../Lexer.o		 
	cp -s ../Lexer.o  ./
	
Parser.o: ../Parser.o	
	cp -s ../Parser.o ./	 
	
Printer.o: ../Printer.o	
	cp -s ../Printer.o ./	
