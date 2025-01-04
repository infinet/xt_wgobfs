# -*- Makefile -*-

ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

.PHONY: tarball
tarball:
	tmpdir=$$(mktemp -dtu); \
	mkdir $$tmpdir; \
	(cd ${top_srcdir} && git archive --prefix=${PACKAGE_NAME}-${PACKAGE_VERSION}/ HEAD | tar -C $$tmpdir -x); \
	(cd $$tmpdir/${PACKAGE_NAME}-${PACKAGE_VERSION} && autoreconf -fi && rm -Rf autom4te*.cache); \
	tar --use=xz -C $$tmpdir -cf ${PACKAGE_NAME}-${PACKAGE_VERSION}.tar.xz --owner=root --group=root ${PACKAGE_NAME}-${PACKAGE_VERSION}/; \
	rm -Rf $$tmpdir
