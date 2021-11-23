## sw/configure.ac
##		https://www.gnu.org/software/autoconf/manual/autoconf-2.60/html_node/index.html#Top
##     https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install
##     https://www.gnu.org/software/automake/manual/automake.html#Declaring-Custom-Test-Drivers

AC_INIT([sw], [0.14.9999], [sw@twyoung.com])  #VERSION for releasing, not in sw
AC_SUBST(SW_MAJOR, ["0"])
AC_SUBST(SW_MINOR, ["14"])
AC_SUBST(SW_LEVEL, ["9999"])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SUBDIRS([docs build-aux])
AC_REQUIRE_AUX_FILE([tap-driver.sh])
## AC_CONFIG_TESTDIR (directory, [test-path = ‘./tests’])
## AC_CONFIG_TESTDIR (directory, [test-path = ‘./model/tests’])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([model/sw.c])
AC_CONFIG_HEADERS([model/config.h])

# Checks for programs.
AC_PROG_CC

## dist_bin_SCRIPTS = bin/swgraph
AC_CONFIG_FILES([Makefile bnfc/Makefile  model/Makefile README.md])
AC_OUTPUT
