CC = gcc
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -PFBP

BISON = bison
BISON_OPTS = -t -pFBP

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: TestFBP

clean:
	rm -f *.o TestFBP FBP.aux FBP.log FBP.pdf FBP.dvi FBP.ps FBP

distclean: clean
	rm -f Absyn.h Absyn.c Test.c Parser.c Parser.h Lexer.c Skeleton.c Skeleton.h Printer.c Printer.h Makefile FBP.l FBP.y FBP.tex 

TestFBP: ${OBJS} Test.o
	@echo "Linking TestFBP..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestFBP

Absyn.o: Absyn.c Absyn.h
	${CC} ${CCFLAGS} -c Absyn.c

Lexer.c: FBP.l
	${FLEX} ${FLEX_OPTS} -oLexer.c FBP.l

Parser.c: FBP.y
	${BISON} ${BISON_OPTS} FBP.y -o Parser.c

Lexer.o: Lexer.c Parser.h
	${CC} ${CCFLAGS} -c Lexer.c 

Parser.o: Parser.c Absyn.h
	${CC} ${CCFLAGS} -c Parser.c

Printer.o: Printer.c Printer.h Absyn.h
	${CC} ${CCFLAGS} -c Printer.c

Test.o: Test.c Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c Test.c

