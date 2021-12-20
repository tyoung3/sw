# sw/c/BNFC/MAKEFILE.AM
## Process this file with automake to produce Makefile.in
 
AUTOMAKE_OPTIONS = foreign
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/../build-aux/tap-driver.sh
                  
TESTS = bnfc.test  
EXTRA_DIST = $(TESTS) SW.pdf
bin_PROGRAMS = TestSW
TestSW_SOURCES = Absyn.c  Lexer.c  Parser.c  Printer.c  Skeleton.c  Test.c Absyn.h  Parser.h  Printer.h  Skeleton.h
TestSWdir = ./
