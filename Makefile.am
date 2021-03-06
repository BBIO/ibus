# vim:set noet ts=4:
#
# ibus - The Input Bus
#
# Copyright (c) 2007-2010 Peng Huang <shawn.p.huang@gmail.com>
# Copyright (c) 2007-2010 Red Hat, Inc.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place, Suite 330,
# Boston, MA  02111-1307  USA

SUBDIRS = 		\
	src 		\
	gconf 		\
	ibus 		\
	ui 			\
	util 		\
	client 		\
	setup 		\
	bus 		\
	data 		\
	m4 			\
	po 			\
	docs 		\
	$(NULL)

ACLOCAL_AMFLAGS = -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ibus-1.0.pc

# xinitrc_SCRIPTS = \
# 	ibus.sh \
# 	$(NULL)
# xinitrcdir = $(sysconfdir)/X11/xinit/xinitrc.d

EXTRA_DIST = \
	autogen.sh \
	ibus-1.0.pc.in \
	ibus.spec.in \
	python-config.py \
	ibus.sh \
	$(NULL)

noinst_DIST = \
	$(NULL)

DISTCLEANFILES = \
	po/stamp-it \
	$(NULL)

install-data-hook:
	$(MKDIR_P) $(DESTDIR)${pkgdatadir}/engine

DISTCHECK_CONFIGURE_FLAGS = \
	--enable-gtk-doc \
	--disable-schemas-install \
	$(NULL)

dist-hook:
	if test -d .git ; then \
		git log --name-status --date=iso > $(distdir)/ChangeLog ; \
	fi

rpm: dist @PACKAGE_NAME@.spec
	rpmbuild -bb \
			--define "_sourcedir `pwd`" \
			--define "_builddir `pwd`/rpm" \
			--define "_srcrpmdir `pwd`/rpm" \
			--define "_rpmdir `pwd`"/rpm \
			--define "_specdir `pwd`/rpm" \
			@PACKAGE_NAME@.spec

srpm: dist @PACKAGE_NAME@.spec
	rpmbuild -bs \
			--define "_sourcedir `pwd`" \
			--define "_builddir `pwd`/rpm" \
			--define "_srcrpmdir `pwd`/rpm" \
			--define "_rpmdir `pwd`/rpm" \
			--define "_specdir `pwd`/rpm" \
			@PACKAGE_NAME@.spec

clean-rpm:
	$(RM) -r "`uname -i`"

clean-local: clean-rpm

git-tag:
	git tag @PACKAGE_VERSION@
