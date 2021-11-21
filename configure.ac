## sw/configure.ac
##1 https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install
AC_INIT([sw], [0.15.0], [sw@twyoung.com])
AC_CONFIG_TESTDIR (directory, [test-path = ‘./tests’])
# ??? Still within configure.ac, as appropriate, ensure that some AC_CONFIG_FILES command includes substitution for tests/atlocal.


AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([model/sw.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
#AC_PROG_CXX
AC_PROG_CC
#AC_PROG_BNFC
#AC_PROG_CPP

AC_CONFIG_FILES([Makefile bnfc/Makefile model/Makefile tests/Makefile])

AC_OUTPUT
