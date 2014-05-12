# -*- perl -*-
#
# See the LICENSE file in the top level directory for license
# information
#
# $Id: op_overload_gen.pl,v 1.6 2000/09/03 19:45:47 bwbarrett Exp $
#
# PURPOSE: Produce the operator overloading files for inilib
#

sub open_file;
sub close_file;
sub file_stuff;

# The operators to play with...

$header = "";

@binary = ("+");
@binary_no_string = ("*", "/", "%", "-");
@bool_binary = ("<", "==", "!=");
@bool_binary_no_string = ("<=", ">", ">=");

open_file("attr_other_arith.h", "ATTR_OTHER_ARITH_H_");

########################################################################
#
# Arithmatic Attr-other 
#
########################################################################

foreach $type ("bool", "double", "int", "std::string") {
    foreach $operator (@binary) {
	file_stuff($operator, $type, $type);
    }
}


########################################################################
#
# Arithmatic Attr-other - no std::string
#
########################################################################

foreach $type ("bool", "double", "int") {
    foreach $operator (@binary_no_string) {
	file_stuff($operator, $type, $type);
    }
}

close_file;
open_file("attr_other_comp.h", "ATTR_OTHER_COMP_H_");


########################################################################
#
# Comparisons Attr-other Binary Operators
#
########################################################################

foreach $type ("bool", "double", "int", "std::string") {
    foreach $operator (@bool_binary) {
	file_stuff($operator, "bool", $type);
    }
}


########################################################################
#
# Comparisons Attr-other Binary Operators - no std::string
#
########################################################################

foreach $type ("bool", "double", "int") {
    foreach $operator (@bool_binary_no_string) {
	file_stuff($operator, "bool", $type);
    }
}

close_file();

########################################################################
#
# Function to do the repeated regex / file stuff
#
########################################################################

sub file_stuff
{
    my $operator = shift;
    my $rtype = shift;
    my $type = shift;
    
    open(TEMPLATE, "op_overload_gen.txt") || 
	die "Could not open $filename $!\n";

    # This is a special case that we couldn't put in the template.
    # operator% is not defined for double, but we need something here.
    # RTFM (it's in the docs).
    while (<TEMPLATE>) {
	if (($type eq "double") && ($operator eq "%") && 
	    ($_ eq "  return ((%%type%%) a %%operator%% b);\n")) {
	    $_ = "   return (double) ((int) a % (int) b);\n";
	} elsif (($type eq "double") && ($operator eq "%") && 
		 ($_ eq "  return (a %%operator%% (%%type%%) b);\n")) {
	    $_ = "   return (double) ((int) a % (int) b);\n";
	} else {
	    $_ =~ s/\%\%operator\%\%/$operator/g;
	    $_ =~ s/\%\%type\%\%/$type/g;
	    $_ =~ s/\%\%rtype\%\%/$rtype/g;
	}	
	print OUTPUT $_;
    }
    
    print OUTPUT "\n";
    
    close(TEMPLATE);
}


sub open_file
{
    my $filename = shift;
    $header = shift;

    open(OUTPUT, ">$filename") || die "Couldn't open $filename $!\n";
    
    
    print OUTPUT "//
// \$COPYRIGHT\$
//
// AUTOMATICALLY GENERATED BY op_overload_gen.pl
// Edit this file at your own risk.  People have been killed for less.
//
    
#ifndef " . $header . "
#define " . $header . "

#include <string>

#include \"Debug.h\"
#include \"attribute.h\"
#include \"bool_attribute.h\"
#include \"double_attribute.h\"
#include \"int_attribute.h\"
#include \"string_attribute.h\"

namespace INI {
";
}

sub close_file
{
    print OUTPUT "}
#endif // " . $header . "
";

    close(OUTPUT);
}
