dnl sw/configure.ac
dnl 	https://www.gnu.org/software/autoconf/manual/autoconf-2.60/html_node/index.html#Top
dnl     https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install
dnl     https://www.gnu.org/software/automake/manual/automake.html#Declaring-Custom-Test-Drivers
dnl   https://fasterthanli.me/articles/cross-compilation-notes
dnl Process this file with autoconf
AC_INIT([sw], [0.28.8], [sw@twyoung.com])  # VERSION for releasing, not in sw
AC_SUBST(SW_MAJOR, ["0"])
AC_SUBST(SW_MINOR, ["28"])
AC_SUBST(SW_LEVEL, ["8"])     # Patch level 
AC_CONFIG_AUX_DIR([build-aux])
AC_REQUIRE_AUX_FILE([tap-driver.sh])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([src/model/sw.c])
AC_CONFIG_HEADERS([src/model/config.h])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_LEX
AC_PROG_CXX
AC_CHECK_FUNCS([strdup strndup memset regcomp])
AC_CHECK_HEADERS([inttypes.h libintl.h regex.h limits.h malloc.h memory.h stddef.h])
AC_CHECK_TYPES([ptrdiff_t])

AC_FUNC_ALLOCA../src/bnfc/TestSWIRL.exe../src/bnfc/TestSWL.exe
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_INT16_T  
AC_TYPE_INT8_T  
AC_TYPE_UINT16_T  
AC_TYPE_UINT32_T  
AC_TYPE_UINT8_T
AC_TYPE_INT32_T
AC_CONFIG_FILES([Makefile src/Makefile src/bnfc/Makefile  src/model/Makefile README.md docsx/Doxyfile SECURITY.md])
AC_OUTPUT

