# sw/c/model/MAKEFILE.AM   
## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh

#TESTS  bnfc.test   
#// EXTRA_DIST = $(TESTS)   
bin_PROGRAMS = TestSWL
scriptsdir = "$(DESTDIR)/bin"

PGM = ./${bin_PROGRAMS} Absyn.o  Lexer.o  Parser.o  Printer.o  Test.o 

swdir = ./

TestSWL_SOURCES =  Absyn.c  Lexer.c  Parser.c  Printer.c  Skeleton.c  Test.c

CFLAGS = -g  $(AM_CFLAGS) -DMAJOR="${SW_MAJOR}" -DMINOR="${SW_MINOR}" -DSLEVEL="${SW_LEVEL}"



