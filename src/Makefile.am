## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = gzzpanel.ui \
	grizzlybear.24x24.png \
	grizzlybear.32x32.png \
	grizzlybear.48x48.png \
	grizzlybear.64x64.png \
	grizzlybear.96x96.png \
	grizzlybear.101x101.png


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(GZZPANEL_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = gzzpanel

gzzpanel_SOURCES = \
	main.cc \
	mainwindow.cc \
	mainwindow.h \
	wnck-pager.cc \
	wnck-pager.h \
	wnck-tasklist.cc \
	wnck-tasklist.h \
	taskbar.cc \
	taskbar.h \
	task.cc \
	task.h \
	wnck-screen.cc \
	wnck-screen.h \
	wnck-window.cc \
	wnck-window.h \
	wnck-workspace.cc \
	wnck-workspace.h \
	common.h

gzzpanel_CXXFLAGS = -std=c++11 

gzzpanel_LDFLAGS =  \
	-lboost_filesystem \
	-lboost_system

gzzpanel_LDADD = $(GZZPANEL_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

