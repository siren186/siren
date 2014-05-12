# -*- makefile -*-
#
# $Id: Makefile.am,v 1.16 2002/05/23 17:47:55 bwbarrett Exp $
#
# See the LICENSE file in the top level directory for license
# information

include $(top_srcdir)/config/Makefile.options

INCLUDES		= -DINI_BUILDING

# Base files - included in both library and binary (binary being used
# to force build of object files for some obscure, but related
# project)
ini_files		= \
			attribute.cc \
			bool_attribute.cc \
			double_attribute.cc \
			int_attribute.cc \
			registry.cc \
			string_attribute.cc

# The library - add in extra because lib_LIBRARIES is in a conditional
EXTRA_LIBRARIES		= libini.a
libini_a_SOURCES	= $(ini_files)
libini_a_AR		= $(INI_AR)

# The binary - add in extra because noinst_PROGRAMS is in a conditional
EXTRA_PROGRAMS		= inilib
inilib_SOURCES		= $(ini_files) \
			  inilib.cc

# Which do we build - library or binary?
if WANT_INI_LIBRARY
lib_LIBRARIES		= libini.a
else
noinst_PROGRAMS		= inilib
endif

# All the header files - only inilib.h gets sent to include everyone
# else will end up in include/inilib/<filename>
include_HEADERS		= inilib.h

pkginclude_HEADERS	= Debug.h \
			attr_attr_arith.h \
			attr_attr_comp.h \
			attr_other_arith.h \
			attr_other_comp.h \
			attribute.h \
			bool_attribute.h \
			double_attribute.h \
			ini_config.h \
			ini_functions.h \
			ini_getline.h \
			int_attribute.h \
			registry.h \
			section.h \
			string_attribute.h

# make it get rebuilt at the right times....
attr_other_arith.h:  op_overload_gen.pl op_overload_gen.txt
	perl $(top_srcdir)/src/op_overload_gen.pl

attr_other_comp.h:  op_overload_gen.pl op_overload_gen.txt
	perl $(top_srcdir)/src/op_overload_gen.pl

EXTRA_DIST		= op_overload_gen.pl op_overload_gen.txt

