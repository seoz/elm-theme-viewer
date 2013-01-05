dnl Process this file with autoconf to produce a configure script.

# get rid of that stupid cache mechanism
rm -f config.cache

AC_INIT([elm_theme_viewer], [0.1.0], [seojuyung2@gmail.com])
AC_PREREQ([2.60])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_HEADERS([elm_theme_viewer_config.h])

AM_INIT_AUTOMAKE([1.6 dist-bzip2])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_USE_SYSTEM_EXTENSIONS
AC_PROG_CC
AM_PROG_CC_C_O
AC_C___ATTRIBUTE__

requirements="\
   elementary >= 1.7.0 \
   eina >= 1.7.0 \
   evas >= 1.7.0 \
   ecore >= 1.7.0 \
   edje >= 1.7.0 \
   "

PKG_CHECK_MODULES([ELM_THEME_VIEWER], [${requirements}])

AC_CHECK_FUNCS(mkstemps)

EFL_WITH_BIN([edje], [edje-cc], [edje_cc])

with_max_log_level="EINA_LOG_LEVEL_ERR"
AC_ARG_WITH(maximum-log-level,
   [AC_HELP_STRING([--with-maximum-log-level=NUMBER],
                   [limit elm-theme-viewer log level to the given number, any call to EINA_LOG() with values greater than this will be compiled out, ignoring runtime settings, but saving function calls.])],
   [
    if test "x${withval}" != "xno"; then
       if echo "${withval}" | grep -E '^[[0-9]]+$' >/dev/null 2>/dev/null; then
          AC_MSG_NOTICE([ignoring any EINA_LOG() with level greater than ${withval}])
          with_max_log_level="${withval}"
       else
          AC_MSG_ERROR([--with-maximum-log-level takes a decimal number, got "${withval}" instead.])
       fi
    fi
    ], [:])

AC_DEFINE_UNQUOTED(EINA_LOG_LEVEL_MAXIMUM, ${with_max_log_level}, [if set, logging is limited to this amount.])

AC_CONFIG_FILES([
Makefile
src/Makefile
data/Makefile
])

AC_OUTPUT

#####################################################################
## Info

echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE $VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Configuration Options Summary:"
echo "Compilation................: make (or gmake)"
echo "  CPPFLAGS.................: $CPPFLAGS"
echo "  CFLAGS...................: $CFLAGS"
echo "  LDFLAGS..................: $LDFLAGS"
echo
echo "Installation...............: make install (as root if needed, with 'su' or 'sudo')"
echo "  prefix...................: $prefix"
echo
