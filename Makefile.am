lib_LTLIBRARIES=libworkspace.la
bin_PROGRAMS=workspace-browser
libexec_PROGRAMS=workspace-browser-applet

serverdir = $(libdir)/bonobo/servers
server_in_file = workspace-browser-applet.server.in
nodist_server_DATA = $(server_in_file:.in=)

EXTRA_DIST=$(server_in_file)
CLEANFILES=$(nodist_server_DATA)

%.server: %.server.in Makefile
	$(AM_V_GEN) sed 's$$@LIBEXECDIR@$$$(libexecdir)$$' $< > $@

workspace_browser_applet_CPPFLAGS=$(WA_CFLAGS) $(WARN_CFLAGS)
workspace_browser_applet_LDADD=libworkspace.la $(libworkspace_la_LIBADD)
workspace_browser_applet_SOURCES=\
	applet.c \
	$(NULL)

workspace_browser_CPPFLAGS=$(libworkspace_la_CPPFLAGS)
workspace_browser_LDADD=libworkspace.la $(libworkspace_la_LIBADD)
workspace_browser_SOURCES=\
	browser.c \
	$(NULL)

libworkspace_la_CPPFLAGS=$(WA_CFLAGS) $(WARN_CFLAGS)
libworkspace_la_LIBADD=$(WA_LIBS)
libworkspace_la_SOURCES=\
	compat-gtk.h \
	wb-label.c \
	wb-label.h \
	window-menu-item.c \
	window-menu-item.h \
	workspace-browser.c \
	workspace-browser.h \
	workspace-button.c \
	workspace-button.h \
	$(NULL)

noinst_PROGRAMS=menu-test
menu_test_CPPFLAGS=$(WA_CFLAGS) $(WARN_CFLAGS)
menu_test_LDADD=$(WA_LIBS)
menu_test_SOURCES=\
	menu-test.c \
	$(NULL)
