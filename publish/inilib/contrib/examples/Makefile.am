# -*- makefile -*-
#
# For license see the file LICENSE in the top directory
#
# $Id: Makefile.am,v 1.16 2002/05/22 17:33:39 bwbarrett Exp $
#

include $(top_srcdir)/config/Makefile.options

INCLUDES		= -DINI_BUILDING

noinst_PROGRAMS		= attributes convert_types load_data save_data 

attributes_SOURCES	= attributes.cc
attributes_LDADD	= -L$(top_builddir)/src -lini
attributes_DEPEDENCIES	= $(top_builddir)/src/libini.a

convert_types_SOURCES	= convert_types.cc
convert_types_LDADD	= -L$(top_builddir)/src -lini
convert_DEPEDENCIES	= $(top_builddir)/src/libini.a

load_data_SOURCES	= load_data.cc
load_data_LDADD		= -L$(top_builddir)/src -lini
load_data_DEPEDENCIES	= $(top_builddir)/src/libini.a

save_data_SOURCES	= save_data.cc
save_data_LDADD		= -L$(top_builddir)/src -lini
save_data_DEPEDENCIES	= $(top_builddir)/src/libini.a

EXTRA_DIST		= input.ini 
