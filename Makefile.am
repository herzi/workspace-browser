lib_LTLIBRARIES=libworkspace.la
bin_PROGRAMS=workspace-browser
libexec_PROGRAMS=workspace-browser-applet

serverdir = $(libdir)/bonobo/servers
server_in_file = workspace-browser-applet.server.in
nodist_server_DATA = $(server_in_file:.in=)

%.server: %.server.in Makefile
	sed 's$$@LIBEXECDIR@$$$(libexecdir)$$' $< > $@

applet.h: .git/
	echo "#define REVISION \"`git describe --tags`\"" > $@.new
	cmp -s $@ $@.new && rm -f $@.new || mv $@.new $@

workspace_browser_applet_CPPFLAGS=$(WA_CFLAGS)
workspace_browser_applet_LDADD=$(WA_LIBS)
workspace_browser_applet_SOURCES=\
	applet.c \
	$(NULL)
nodist_workspace_browser_applet_SOURCES=\
	applet.h \
	$(NULL)

BUILT_SOURCES=\
	$(nodist_workspace_browser_applet_SOURCES) \
	$(NULL)
CLEANFILES=$(BUILT_SOURCES) $(nodist_server_DATA)

workspace_browser_CPPFLAGS=$(libworkspace_la_CPPFLAGS)
workspace_browser_LDADD=libworkspace.la $(libworkspace_la_LIBADD)
workspace_browser_SOURCES=\
	browser.c \
	$(NULL)

libworkspace_la_CPPFLAGS=$(WA_CFLAGS)
libworkspace_la_LIBADD=$(WA_LIBS)
libworkspace_la_SOURCES=\
	window-menu-item.c \
	window-menu-item.h \
	workspace-browser.c \
	workspace-browser.h \
	workspace-button.c \
	workspace-button.h \
	$(NULL)

noinst_PROGRAMS=menu-test
menu_test_CPPFLAGS=$(WA_CFLAGS)
menu_test_LDADD=$(WA_LIBS)
menu_test_SOURCES=\
	menu-test.c \
	$(NULL)
