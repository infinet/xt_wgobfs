# -*- Makefile -*-

ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

.PHONY: tarball dkms-install

tarball_name = ${PACKAGE_NAME}-${PACKAGE_VERSION}.tar.xz

tarball:
	tmpdir=$$(mktemp -dtu); \
	mkdir $$tmpdir; \
	(cd ${top_srcdir} && git archive --prefix=${PACKAGE_NAME}-${PACKAGE_VERSION}/ HEAD | tar -C $$tmpdir -x); \
	(cd $$tmpdir/${PACKAGE_NAME}-${PACKAGE_VERSION} && autoreconf -fi && rm -Rf autom4te*.cache); \
	tar --use=xz -C $$tmpdir -cf ${tarball_name} --owner=root --group=root ${PACKAGE_NAME}-${PACKAGE_VERSION}/; \
	rm -Rf $$tmpdir

# generate tarball as normal user first
dkms-install:
	@[ -f ${tarball_name} ] || { echo "${tarball_name} does not exist. To generate, run make tarball"; exit 1; }
	tar xf ${tarball_name} -C /usr/src
	dkms add -m ${PACKAGE_NAME} -v ${PACKAGE_VERSION}
	@make --no-print-directory dkmsinst

# On Debian 13, need wrap it in @make --no-print-directory. Otherwise the
# "make[1] entering directory ..." message will pollute configure's gcc
# detection.
dkmsinst:
	dkms install -m ${PACKAGE_NAME} -v ${PACKAGE_VERSION}
