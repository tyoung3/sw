# sw/model/MAKEFILE.AM

AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = sw
sw_SOURCES =  sw.c swconfig.c swgraph.c swmain.c swsym.c swc.c  swgo.c  swjavafbp.c  swproject.c

sw_HEADERS = model.h  swconfig.h  swgo.h  swgraph.h	sw.h  swmain.h	swsym.h

swdir = ./

CFLAGS =  -DVERSION=${VERSION} $(AM_CFLAGS)

sw_LDADD =  ../bnfc/Absyn.o ../bnfc/Lexer.o ../bnfc/Parser.o ../bnfc/Printer.o
