## sw/configure.ac
##		https://www.gnu.org/software/autoconf/manual/autoconf-2.60/html_node/index.html#Top
##     https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install
##     https://www.gnu.org/software/automake/manual/automake.html#Declaring-Custom-Test-Drivers

AC_INIT([sw], [0.15.0], [sw@twyoung.com])  #VERSION for releasing, not in sw
AC_SUBST(SW_MAJOR, ["0"])
AC_SUBST(SW_MINOR, ["15"])
AC_SUBST(SW_LEVEL, ["0"])
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
AC_CHECK_FUNCS([strdup strndup memset regcomp])
AC_CHECK_HEADERS([inttypes.h libintl.h limits.h malloc.h memory.h stddef.h])
AC_CHECK_TYPES([ptrdiff_t])

AC_FUNC_ALLOCA
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_INT16_T  
AC_TYPE_INT8_T  
AC_TYPE_UINT16_T  
AC_TYPE_UINT32_T  
AC_TYPE_UINT8_T
AC_TYPE_INT32_T
AC_CONFIG_FILES([Makefile bnfc/Makefile  model/Makefile README.md docs/Makefile docs/Doxyfile])
AC_OUTPUT
