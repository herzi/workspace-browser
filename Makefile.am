libexec_PROGRAMS=workspace-applet

workspace_applet_CPPFLAGS=$(WA_CFLAGS)
workspace_applet_LDADD=$(WA_LIBS)
workspace_applet_SOURCES=\
	main.c \
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
