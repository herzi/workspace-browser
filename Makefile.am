lib_LTLIBRARIES=libworkspace.la
libexec_PROGRAMS=workspace-applet

workspace_applet_CPPFLAGS=$(libworkspace_la_CPPFLAGS)
workspace_applet_LDADD=libworkspace.la $(libworkspace_la_LIBADD)
workspace_applet_SOURCES=\
	main.c \
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
