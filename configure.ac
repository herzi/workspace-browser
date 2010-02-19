AC_INIT(Workspace Applet, 0.0.1, http://no.website.yet/, workspace-applet)
AM_INIT_AUTOMAKE(1.9 dist-bzip2 no-define foreign)

F77=no
CXX=no

AC_PROG_CC
AC_PROG_LIBTOOL

PKG_CHECK_MODULES(WA,[gtk+-2.0 libwnck-1.0 libpanelapplet-2.0])
WA_CFLAGS="$WA_CFLAGS -DWNCK_I_KNOW_THIS_IS_UNSTABLE"
AC_SUBST(WA_CFLAGS)

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
