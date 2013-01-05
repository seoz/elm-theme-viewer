MAINTAINERCLEANFILES = Makefile.in

EDJE_CC = @edje_cc@
EDJE_FLAGS_VERBOSE_ =
EDJE_FLAGS_VERBOSE_0 =
EDJE_FLAGS_VERBOSE_1 = -v
EDJE_FLAGS = $(EDJE_FLAGS_$(V))

filesdir = $(pkgdatadir)/themes
files_DATA = \
layout.edj

EXTRA_DIST = layout.edc

layout.edj: Makefile layout.edc
	$(EDJE_CC) $(EDJE_FLAGS) \
	$(top_srcdir)/data/themes/layout.edc \
	$(top_builddir)/data/themes/layout.edj

clean-local:
	rm -f *.edj
