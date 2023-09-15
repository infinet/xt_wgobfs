AC_INIT([xt_wgobfs], [0.5.0])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_PROG_INSTALL
AM_INIT_AUTOMAKE([1.10b -Wall foreign subdir-objects])
AC_PROG_CC
AM_PROG_CC_C_O
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AC_DISABLE_STATIC
AC_PROG_LIBTOOL

AC_ARG_WITH([kbuild],
	AS_HELP_STRING([--with-kbuild=PATH],
	[Path to kernel build directory [[/lib/modules/CURRENT/build]]])
AS_HELP_STRING([--without-kbuild],
	[Build only userspace tools]),
	[kbuilddir="$withval"],
	[kbuilddir="/lib/modules/$(uname -r)/build"])
#
# check for --without-kbuild
#
AS_IF([test "$kbuilddir" = no], [kbuilddir=""])

AC_CHECK_HEADERS([linux/netfilter/x_tables.h], [],
	[AC_MSG_ERROR([You need to have linux/netfilter/x_tables.h, see INSTALL file for details])])
PKG_CHECK_MODULES([libxtables], [xtables >= 1.4.21])
xtlibdir="$($PKG_CONFIG --variable=xtlibdir xtables)"

AC_ARG_WITH([xtlibdir],
	AS_HELP_STRING([--with-xtlibdir=PATH],
	[Path where to install Xtables extensions [[autodetect]]]),
	[xtlibdir="$withval"])
AC_MSG_CHECKING([Xtables module directory])
AC_MSG_RESULT([$xtlibdir])

regular_CPPFLAGS="-D_LARGEFILE_SOURCE=1 -D_LARGE_FILES -D_FILE_OFFSET_BITS=64 \
	-D_REENTRANT -I\${XA_TOPSRCDIR}/include"
regular_CFLAGS="-Wall -Waggregate-return -Wmissing-declarations \
	-Wmissing-prototypes -Wredundant-decls -Wshadow -Wstrict-prototypes \
	-Winline -pipe";


AC_SUBST([regular_CPPFLAGS])
AC_SUBST([regular_CFLAGS])
AC_SUBST([kbuilddir])
AC_SUBST([xtlibdir])
AC_CONFIG_FILES([Makefile Makefile.libxt])
AC_OUTPUT
