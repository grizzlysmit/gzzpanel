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
	common.h \
	wnck-application.cc \
	wnck-application.h \
	wnck-class-group.cc \
	wnck-class-group.h \
	private/wnck-tasklist_p.h \
	private.h \
	applet.cc \
	applet.h \
	prefs.cc \
	prefs.h \
	private/wnck-screen_p.h \
	private/wnck-window_p.h \
	private/wnck-workspace_p.h \
	private/wnck-application_p.h \
	private/wnck-class-group_p.h \
	wrap_init.h \
	wrap_init.cc \
	wnck-action-menu.cc \
	wnck-action-menu.h \
	lvt.cc \
	lvt.h \
	runapp.cc \
	runapp.h

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

