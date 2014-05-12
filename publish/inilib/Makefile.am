# -*- makefile -*-
#
# See the LICENSE file in the top level directory for license
# information

include $(top_srcdir)/config/Makefile.options

SUBDIRS			= src
DEPDIRS			= $(SUBDIRS) contrib
DIST_SUBDIRS		= $(SUBDIRS) config contrib doc

EXTRA_DIST		= INSTALL LICENSE NEWS README VERSION

# Targets for making the examples and whatnot
examples:
	@ echo "Making all in contrib/examples"
	@ (cd contrib; $(MAKE) all)

# It seems that distclean will fire off clean-local scripts AFTER
# calling disclean everywhere, which poses a problem for this rule.  A
# quick work-around...
examples-clean:
	@ echo "Making clean in contrib/examples"
	@ (cd contrib; (test -f Makefile && $(MAKE) clean) || test -f Makefile.am)

# Targets for firing off the above clean targets
clean-local: examples-clean

# a hook to run our license install code.
dist-hook:
	csh -f $(top_srcdir)/config/distscript.csh $(DESTDIR)$(distdir)
	@ sleep 5
	@ touch $(DESTDIR)$(distdir)/src/attr_other_arith.h
	@ touch $(DESTDIR)$(distdir)/src/attr_other_arith.h
