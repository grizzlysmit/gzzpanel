## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

gzzpaneldocdir = ${prefix}/doc/gzzpanel
gzzpaneldoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(gzzpaneldoc_DATA) \
			 gzzpanel.desktop \
			 gzzpanel.png \
	$(INTLTOOL_FILES)

pixmapdir = $(datadir)/pixmaps

pixmap_DATA = gzzpanel.png


Applicationsdir = $(datadir)/applications
Applications_DATA = gzzpanel.desktop

AM_CXXFLAGS = -std=c++17 

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(gzzpaneldocdir)
