## sw/configure.ac
##     https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install
##     https://www.gnu.org/software/automake/manual/automake.html#Declaring-Custom-Test-Drivers

AC_INIT([sw], [0.14], [sw@twyoung.com])  #VERSION for releasing, not in sw
AC_SUBST(SW_MAJOR, ["0"])
AC_SUBST(SW_MINOR, ["15"])
AC_SUBST(SW_LEVEL, ["00"])
AC_CONFIG_AUX_DIR([build-aux])
AC_REQUIRE_AUX_FILE([tap-driver.sh])
## AC_CONFIG_TESTDIR (directory, [test-path = ‘./tests’])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([model/sw.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

## dist_bin_SCRIPTS = bin/swgraph
AC_CONFIG_FILES([Makefile bnfc/Makefile model/Makefile README.md])
AC_OUTPUT
