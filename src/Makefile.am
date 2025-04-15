
xt_srcdir = ${abs_srcdir}
INSTALL_MOD_DIR = updates
INSTALL_MOD_PATH = $(DESTDIR)

.PHONY: modules modules_install clean_modules

_kcall = -C ${kbuilddir} M=${xt_srcdir}

modules:
	${MAKE} ${_kcall} modules

modules_install:
	${MAKE} ${_kcall} modules_install \
		INSTALL_MOD_PATH=$(INSTALL_MOD_PATH) INSTALL_MOD_DIR=$(INSTALL_MOD_DIR)

clean_modules:
	${MAKE} ${_kcall} clean


_mcall = -C ${xt_srcdir} -f ${xt_srcdir}/Makefile.libxt

libxt-local:
	${MAKE} ${_mcall} all

libxt-install:
	${MAKE} ${_mcall} install

libxt-clean:
	${MAKE} ${_mcall} clean

all-local: modules libxt-local

install-exec-local: modules_install libxt-install

clean-local: clean_modules libxt-clean
