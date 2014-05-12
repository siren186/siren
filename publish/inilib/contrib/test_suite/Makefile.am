# -*- makefile -*-
#
# For license see the file LICENSE in the top directory
#
# $Id: Makefile.am,v 1.20 2005/03/14 17:16:55 bwbarrett Exp $
#

include $(top_srcdir)/config/Makefile.options

INCLUDES		= -DINI_BUILDING

noinst_PROGRAMS		= inilib_test
inilib_test_SOURCES	= comment.cc \
			file_functions.cc \
			inilib_test.cc \
			messages.cc \
			operator.cc \
			precision_change.cc \
			registry_functions.cc \
			section_functions.cc

inilib_test_DEPEDENCIES= $(top_builddir)/src/libini.a

include_HEADERS		= attribute_functions.cct \
			inilib_test.h

EXTRA_DIST		= test.ini data.txt comment.ini

inilib_test_LDADD	= -L$(top_builddir)/src -lini
