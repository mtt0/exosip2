ACLOCAL_AMFLAGS = -I scripts
EXTRA_DIST = README autogen.sh LICENSE.OpenSSL

SUBDIRS = scripts platform src include tools help

doxygen:
	doxygen help/doxygen/DoxyFile

upload: dist
	@echo "######## Maintainer only ##########";
	@echo "building files for upload in ftp://savannah.gnu.org/incoming/savannah/exosip";
	@echo "building: $(PACKAGE)-$(VERSION).tar.gz.sig";
	gpg -b $(PACKAGE)-$(VERSION).tar.gz

indent:
	@type astyle --version >/dev/null 2>&1 || astyle --project=.astylerc $(top_srcdir)/include/eXosip2/*.h
	@type astyle --version >/dev/null 2>&1 || astyle --project=.astylerc $(top_srcdir)/src/*.h
	@type astyle --version >/dev/null 2>&1 || astyle --project=.astylerc $(top_srcdir)/src/*.c
	@type astyle --version >/dev/null 2>&1 || astyle --project=.astylerc $(top_srcdir)/tools/*.c
	rm -rf $(top_srcdir)/*/*/*.h~
	rm -rf $(top_srcdir)/*/*.h~
	rm -rf $(top_srcdir)/*/*.c~
