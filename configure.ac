AC_INIT(Workspace Applet, 0.0.2, http://github.com/herzi/workspace-browser/issues, workspace-applet)
AM_INIT_AUTOMAKE(1.9 dist-bzip2 no-define foreign)

F77=no
CXX=no

AC_PROG_CC
AC_PROG_LIBTOOL
ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])],[])

GNOME_COMPILE_WARNINGS(maximum)

PKG_CHECK_MODULES(WA,[gtk+-2.0 libwnck-1.0 libpanelapplet-2.0])
WA_CFLAGS="$WA_CFLAGS -DWNCK_I_KNOW_THIS_IS_UNSTABLE"
AC_SUBST(WA_CFLAGS)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
