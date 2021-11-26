# sw/model/MAKEFILE.AM   
## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh
                  
TESTS = sw.test   
EXTRA_DIST = $(TESTS)   
bin_PROGRAMS = sw
bin_scripts = sw.test.sh
##scripts_DATA = tests/ab.sw tests/aa.sw
##scriptsdir = prefix=@prefix@
##exec_prefix=@exec_prefix@
##bindir=@bindir@
scriptsdir = "$(DESTDIR)/bin"

PGM = ./${bin_PROGRAMS} 

swdir = ./

sw_SOURCES =  sw.c swconfig.c swgraph.c swmain.c swsym.c swc.c  swgo.c  swjavafbp.c  swproject.c model.h  swconfig.h  swgo.h  swgraph.h	sw.h  swmain.h	swsym.h 

CFLAGS = -g  $(AM_CFLAGS) -DMAJOR=${SW_MAJOR} -DMINOR=${SW_MINOR}               -DLEVEL=${SW_LEVEL}

sw_LDADD = ../bnfc/Absyn.o ../bnfc/Lexer.o ../bnfc/Parser.o ../bnfc/Printer.o

