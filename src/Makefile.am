MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = elm_theme_viewer

elm_theme_viewer_CPPFLAGS = -I. \
-DPACKAGE_BIN_DIR=\"$(bindir)\" -DPACKAGE_LIB_DIR=\"$(libdir)\" \
-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\" @ELM_THEME_VIEWER_CFLAGS@

elm_theme_viewer_LDADD = @ELM_THEME_VIEWER_LIBS@

elm_theme_viewer_SOURCES = \
gui.c gui.h \
log.c log.h \
theme.c theme.h \
widget.c widget.h \
main.c common.h \
gui_mobile.c gui_mobile.h
