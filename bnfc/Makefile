CC = gcc
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -PSW

BISON = bison
BISON_OPTS = -t -pSW

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: Skeleton.c TestSW  SW.tex

clean:
	rm -f *.o TestSW SW.aux SW.log SW.pdf SW.dvi SW.ps SW

distclean: clean
	rm -f Absyn.h Absyn.c Test.c Parser.c Parser.h Lexer.c Skeleton.c Skeleton.h Printer.c Printer.h  SW.l SW.y SW.tex 

SW.tex:  SW.cf
	bnfc --latex SW.cf
	
Skeleton.c: SW.cf
	bnfc --c SW.cf
	
TestSW: ${OBJS} Test.o
	@echo "Linking TestSW..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestSW

Absyn.o: Absyn.c Absyn.h
	${CC} ${CCFLAGS} -c Absyn.c

Lexer.c: SW.l
	${FLEX} ${FLEX_OPTS} -oLexer.c SW.l

Parser.c: SW.y
	${BISON} ${BISON_OPTS} SW.y -o Parser.c

Lexer.o: Lexer.c Parser.h
	${CC} ${CCFLAGS} -c Lexer.c 

Parser.o: Parser.c Absyn.h
	${CC} ${CCFLAGS} -c Parser.c

Printer.o: Printer.c Printer.h Absyn.h
	${CC} ${CCFLAGS} -c Printer.c

Test.o: Test.c Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c Test.c

