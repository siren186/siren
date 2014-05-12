dnl -*- shell-script -*-
dnl
dnl $Id: cxx_have_broken_getline.m4,v 1.4 2002/05/22 17:27:59 bwbarrett Exp $
dnl

define([LSC_CXX_HAVE_BROKEN_GETLINE],[
#
# Arguments: prefix (optional)
#
# Dependencies: 
#
# Tests whether the getline in std::string is broken
#
# Sets prefix_GETLINE to prefix_getline if broken, getline otherwise
# Must call AC_SUBST manually.
#

# Figure out what prefix to use
lsc_cxx_prefix="$1"
if test "$lsc_cxx_prefix" = ""; then
    lsc_cxx_prefix="LSC"
fi

# First we need to see if we need to check for STL
if test "$LSC_CXX_STL" = ""; then
    LSC_CXX_HAVE_STL($lsc_cxx_prefix)
fi

# Check for the repository
if test "$LSC_CXX_TEMPLATE_REPOSITORY" = ""; then
    LSC_CXX_FIND_TEMPLATE_REPOSITORY
fi

AC_MSG_CHECKING([for broken std::string::getline])

rm -f conftest.cc conftest.o conftest.txt
cat > conftest.txt <<EOF
test1

test2
EOF


cat > conftest.cc <<EOF
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int
main(int agrc, char* argv[])
{
  bool good, bad, fstr, fstr_eof;
  bool result = true;
  fstream input_file;
  string tmp;
  input_file.open("conftest.txt", ios::in);

  for (int i = 0 ; i < 3 ; ++i) {
    getline(input_file, tmp);
    fstr = input_file;
    good = input_file.good();
    bad = input_file.bad();
    fstr_eof = input_file.eof();
    result &= fstr && good && !bad && !fstr_eof;
  }

  getline(input_file, tmp);
  fstr = input_file;
  good = input_file.good();
  bad = input_file.bad();
  fstr_eof = input_file.eof();
  result &= !fstr && !good && !bad && fstr_eof;

  return result ? 1 : 0;
}
EOF

echo configure:__oline__: $CXX $CXXFLAGS conftest.cc -o conftest >&5 
$CXX $CXXFLAGS conftest.cc -o conftest >&5 2>&5
if (test -f conftest); then
    echo configure:__oline__: Running getline test program >&5
    if (conftest) < /dev/null > /dev/null 2>&1; then
	echo configure:__oline__: Failed >&5
	lsc_result="1"
	AC_MSG_RESULT([yes])
    else
        echo configure:__oline__: Success >&5
	lsc_result="0"
	AC_MSG_RESULT([no])
    fi
else
    echo configure:__oline__: here is the program that failed: >&5
    cat conftest.cc >&5
    lsc_result="1"
    AC_MSG_RESULT([yes])
fi
    
# Set the results
lsc_name="${lsc_cxx_prefix}_HAVE_BROKEN_GETLINE"
lsc_str="${lsc_name}=$lsc_result"
eval $lsc_str
AC_DEFINE_UNQUOTED($lsc_name, $lsc_result, [Is std::string::getline broken?])

# Clean up
/bin/rm -rf conftest* $LSC_CXX_TEMPLATE_REPOSITORY
unset lsc_cxx_prefix lsc_name lsc_str lsc_result])dnl
