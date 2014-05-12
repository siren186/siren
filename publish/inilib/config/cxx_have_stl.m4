dnl -*- shell-script -*-
dnl
dnl $Id: cxx_have_stl.m4,v 1.2 2002/05/22 17:27:59 bwbarrett Exp $
dnl

define(LSC_CXX_HAVE_STL,[
#
# Arguments: prefix (optional)
#
# Dependencies: None
#
# See if the C++ compiler has STL
#
# Set prefix_CXX_STL and LSC_CXX_STL to 1 if so, 0 if not
# AC_DEFINE prefix_CXX_STL to 1 if so, 0 if not
#

# Figure out what prefix to use
lsc_prefix="$1"
if test "$lsc_prefix" = ""; then
    lsc_prefix="LSC"
fi

# Do the test
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_CHECK_HEADER(map, LSC_CXX_STL=1, LSC_CXX_STL=0)

# Set the result
lsc_name="${lsc_prefix}_CXX_STL"
lsc_str="${lsc_name}=$LSC_CXX_STL"
eval $lsc_str
AC_DEFINE_UNQUOTED($lsc_name, $LSC_CXX_STL, [Do we have STL support?])

# Clean up
AC_LANG_RESTORE
unset lsc_prefix lsc_str lsc_name])dnl

