CC = gcc

CCFLAGS = -g -W -Wall
#CCFLAGS = -O6 -W -Wall

OBJS = Absyn.o Lexer.o Parser.o Printer.o

all:  sw tags 

install: sw
	sudo cp ./sw /usr/local/bin 

tags:   sw.c  swgo.c  swmain.c swsym.c swgo.h nemod.h sw.h  swmain.h  swsym.h

	ctags *.c *.h

clean:
	rm -f sw.o swnom.o  swnemod.o  ${OBJS} Parser.h Printer.h Absyn.h

run:  sw
	./collate.sh

check: sw nds/ac.sw
	./sw nds/aa.sw  
	./sw nds/ab.sw
	./sw nds/ac.sw || echo OK

jpeg:  /tmp/collate.jpg

/tmp/collate.jpg: sw  
	./sw */collate.sw 1 > /tmp/collate.dot		\
	&& dot -Tjpg  /tmp/collate.dot > /tmp/collate.jpg \
	&& gimp /tmp/collate.jpg &
	
sw: ${OBJS}                   sw.o swmain.o swgo.o swsym.o swgraph.o
	${CC} ${CCFLAGS} ${OBJS}  sw.o swmain.o swgo.o swsym.o swgraph.o -o sw
	
swsym.o: swsym.c swsym.h 
	${CC} ${CCFLAGS} -c  swsym.c -o swsym.o
		
sw.o: sw.c sw.h swsym.h Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c  sw.c -o sw.o 
	
swmain.o: swmain.c sw.h swmain.h Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c swmain.c -o swmain.o 	
	
swgo.o: swgo.c swgo.h nemod.h
	${CC} ${CCFLAGS} -c swgo.c -o swgo.o	

swgraph.o: swgraph.c swgraph.h 
	${CC} ${CCFLAGS} -c swgraph.c -o swgraph.o
	
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
