# -*- shell-script -*-
dnl
dnl $Id: acinclude.m4,v 1.4 2002/05/22 17:27:57 bwbarrett Exp $
dnl

#############################################################################

# Get all the respective tests; these are from the LSC standard m4
# repository

# C++ tests

sinclude(config/cxx_find_template_repository.m4)
sinclude(config/cxx_have_stl.m4)
sinclude(config/cxx_have_broken_getline.m4)

