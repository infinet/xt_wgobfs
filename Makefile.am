# -*- Makefile -*-

ACLOCAL_AMFLAGS  = -I m4

xt_srcdir = ${abs_srcdir}/src
_kcall = -C ${kbuilddir} M=${xt_srcdir}

.PHONY: modules modules_install clean_modules \
        libxt-local libxt-install libxt-clean install clean all

all: modules libxt-local

install: modules_install libxt-install

clean: clean_modules libxt-clean

modules:
	${MAKE} ${_kcall} modules

modules_install:
	${MAKE} ${_kcall} INSTALL_MOD_PATH=${DESTDIR} ext-mod-dir='$${INSTALL_MOD_DIR}' modules_install

clean_modules:
	${MAKE} ${_kcall} clean

_mcall = -C ${xt_srcdir} -f ${top_builddir}/../Makefile.libxt

libxt-local:
	${MAKE} ${_mcall} all

libxt-install:
	${MAKE} ${_mcall} install

libxt-clean:
	${MAKE} ${_mcall} clean

tmpdir := $(shell mktemp -dtu)
packer  = xz
packext = .tar.xz

.PHONY: tarball
tarball:
	mkdir ${tmpdir}
	pushd ${top_srcdir} && git archive --prefix=${PACKAGE_NAME}-${PACKAGE_VERSION}/ HEAD | tar -C ${tmpdir} -x && popd;
	pushd ${tmpdir}/${PACKAGE_NAME}-${PACKAGE_VERSION} && autoreconf -fi && rm -Rf autom4te*.cache && popd;
	tar --use=${packer} -C ${tmpdir} -cf ${PACKAGE_NAME}-${PACKAGE_VERSION}${packext} --owner=root --group=root ${PACKAGE_NAME}-${PACKAGE_VERSION}/;
	rm -Rf ${tmpdir};
