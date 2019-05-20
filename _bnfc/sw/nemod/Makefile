CC = gcc
CCFLAGS = -g -W -Wall

OBJS = Absyn.o Lexer.o Parser.o Printer.o

all:  sw

clean:
	rm -f sw.o swnom.o  swnemod.o  ${OBJS} Parser.h Printer.h Absyn.h

check: sw nds/ac.sw
	./sw nds/aa.sw  
	./sw nds/ab.sw
	./sw nds/ac.sw
	./sw nds/ae1.sw || echo OK
	
sw: sw.o swnemod.o  ${OBJS}
	${CC} ${CCFLAGS} ${OBJS}  sw.o swnemod.o   -o sw
	
sw.o: sw.c sw.h  Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c  sw.c -o sw.o 
	
swnemod.o: swnemod.c sw.h swnemod.h Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c swnemod.c -o swnemod.o 	

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
