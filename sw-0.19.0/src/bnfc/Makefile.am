# sw/c/BNFC/MAKEFILE.AM
## Process this file with automake to produce Makefile.in
 
AUTOMAKE_OPTIONS = foreign
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/../build-aux/tap-driver.sh
                  
TESTS = bnfc.test  
EXTRA_DIST = $(TESTS) SWIRL.pdf
bin_PROGRAMS = TestSWIRL
TestSWIRL_SOURCES = Absyn.c  Lexer.c  Parser.c  Printer.c  Skeleton.c  Test.c Absyn.h  Parser.h  Printer.h  Skeleton.h
TestSWIRLdir = ./
