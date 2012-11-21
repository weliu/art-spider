#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(art_spider, 1.0, 266lwf@163.com)
AM_INIT_AUTOMAKE(art_spider, 1.0, 266lwf@163.com)
AC_CONFIG_SRCDIR([src/main/main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
LT_INIT
AC_PROG_LIBTOOL

# Checks for libraries.
# FIXME: Replace `main' with a function in `-llog4cplus':
AC_CHECK_LIB([log4cplus], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/lib/Makefile
                 src/main/Makefile])
AC_OUTPUT
