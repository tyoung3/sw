CC = gcc
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -PSWL

BISON = bison
BISON_OPTS = -t -pSWL

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY : clean distclean

all : TestSWL 

doc: ../../docs/SWL.pdf

../../docs/SWL.pdf: SWL.tex
	pdflatex -output-directory=../../docs SWL.tex
    
SWL.tex: SWL.cf
	bnfc --latex SWL.cf    

clean :
	rm -f *.o TestSWL SWL.aux SWL.log SWL.pdf SWL.dvi SWL.ps SWL

distclean : clean
	rm -f Absyn.h Absyn.c Test.c Parser.c Parser.h Lexer.c Skeleton.c Skeleton.h Printer.c Printer.h Makefile SWL.l SWL.y SWL.tex

TestSWL : ${OBJS} Test.o
	@echo "Linking TestSWL..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestSWL

Absyn.o : Absyn.c Absyn.h
	${CC} ${CCFLAGS} -c Absyn.c

Lexer.c : SWL.l
	${FLEX} ${FLEX_OPTS} -oLexer.c SWL.l

Parser.c : SWL.y
	${BISON} ${BISON_OPTS} SWL.y -o Parser.c

Lexer.o : Lexer.c Parser.h
	${CC} ${CCFLAGS} -c Lexer.c

Parser.o : Parser.c Absyn.h
	${CC} ${CCFLAGS} -c Parser.c

Printer.o : Printer.c Printer.h Absyn.h
	${CC} ${CCFLAGS} -c Printer.c

Test.o : Test.c Parser.h Printer.h Absyn.h
	${CC} ${CCFLAGS} -c Test.c
