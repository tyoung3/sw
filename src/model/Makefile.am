# sw/c/model/MAKEFILE.AM   
## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign
TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh

##??? ErrorAM_WITH_REGEX
TESTS = sw.test   
EXTRA_DIST = $(TESTS)   
bin_PROGRAMS = sw
bin_scripts = sw.test mktest.sh
scriptsdir = "$(DESTDIR)/bin"

PGM = ./${bin_PROGRAMS} 

swdir = ./

sw_SOURCES =  sw.c swexpand.c swconfig.c swgraph.c swmain.c swsym.c swc.c  swgo.c  swjavafbp.c  swproject.c model.h  swconfig.h  swgo.h  swgraph.h	sw.h  swmain.h	swsym.h swgofbp.c swgofbp.h re.c re.h strndup.c 

CFLAGS = -g  $(AM_CFLAGS) -Wall -Wextra -DMAJOR="${SW_MAJOR}" -DMINOR="${SW_MINOR}" -DSLEVEL="${SW_LEVEL}" 

sw_LDADD = ../bnfc/Absyn.o ../bnfc/Lexer.o ../bnfc/Parser.o ../bnfc/Printer.o

