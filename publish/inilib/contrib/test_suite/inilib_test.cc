// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: inilib_test.cc,v 1.16 2005/03/10 18:13:11 bwbarrett Exp $
//

#include <iostream>
#include "inilib.h"

#include "inilib_test.h"
#include "attribute_functions.cct"

using namespace INI;
using namespace std;

//
// Global variables
//
const int version[3] = { 1, 0, 2 };


//
// main
//
int
main(int argc, char *argv[])
{
  bool group = true;
  bool result = true;

  // Announce
  cout << endl
       << "INILIB Test suite" << endl
       << "-----------------" << endl 
       << "Version " << version[0] << "." << version[1] << "."
       << version[2] << endl << endl;

  // Test all the objects
  Testing("int_attribute");
  group = true;
  int_attribute attribute1(1);
  group &= attribute_cast_int(attribute1, 1);
  group &= attribute_cast_double(attribute1, 1);
  group &= attribute_cast_string(attribute1, "1");
  group &= attribute_cast_bool(attribute1, 1);
  group &= attribute_assignment_int(attribute1, 1, 1);
  group &= attribute_assignment_double(attribute1, 1.23, 1.00);
  group &= attribute_assignment_string(attribute1, "1.23", "1");
  group &= attribute_assignment_bool(attribute1, true, true);
  result &= group;
  Test(group);

  Testing("double_attribute");
  group = true;
  double_attribute attribute2(1.1);
  group &= attribute_cast_int(attribute2, 1.1);
  group &= attribute_cast_double(attribute2, 1.1);
  group &= attribute_cast_string(attribute2, "1.1");
  group &= attribute_cast_bool(attribute2, 1.1);
  group &= attribute_assignment_int(attribute2, 1, 1);
  group &= attribute_assignment_double(attribute2, 1.234, 1.234);
  group &= attribute_assignment_string(attribute2, "1.233", "1.233");
  group &= attribute_assignment_bool(attribute2, (bool) 1.23,  true);
  result &= group;
  Test(group);

  Testing("string_attribute");
  group = true;
  string_attribute attribute3("1.1");
  group &= attribute_cast_int(attribute3, 1);
  group &= attribute_cast_double(attribute3, 1.1);
  group &= attribute_cast_string(attribute3, "1.1");
  group &= attribute_cast_bool(attribute3, false);
  group &= attribute_assignment_int(attribute3, 1, 1);
  group &= attribute_assignment_double(attribute3, 1.234, 1.234);
  group &= attribute_assignment_string(attribute3, "foo", "foo");
  group &= attribute_assignment_bool(attribute3, true, true);
  result &= group;
  Test(group);

  Testing("bool_attribute");
  group = true;
  bool_attribute attribute4(true);
  group &= attribute_cast_int(attribute4, true);
  group &= attribute_cast_double(attribute4, true);
  group &= attribute_cast_string(attribute4, "true");
  group &= attribute_cast_bool(attribute4, true);
  group &= attribute_assignment_int(attribute4, 5, 1);
  group &= attribute_assignment_double(attribute4, 1.5, 1.0);
  group &= attribute_assignment_string(attribute4, "true", "true");
  group &= attribute_assignment_bool(attribute4, true, true);
  result &= group;
  Test(group);

  Testing("attribute");
  group = true;
  attribute attribute5, attribute6, attribute7, attribute8;
  attribute5 = 1;
  group &= attribute_cast_int(attribute5, 1);
  group &= attribute_cast_double(attribute5, 1);
  group &= attribute_cast_string(attribute5, "1");
  group &= attribute_cast_bool(attribute5, 1);
  group &= attribute_assignment_int(attribute5, 1, 1);
  group &= attribute_assignment_double(attribute5, 1.23, 1.00);
  group &= attribute_assignment_string(attribute5, "1.23", "1");
  group &= attribute_assignment_bool(attribute5, true, true);

  attribute6 = 1.1;
  group &= attribute_cast_int(attribute6, 1.1);
  group &= attribute_cast_double(attribute6, 1.1);
  group &= attribute_cast_string(attribute6, "1.1");
  group &= attribute_cast_bool(attribute6, 1.1);
  group &= attribute_assignment_int(attribute6, 1, 1);
  group &= attribute_assignment_double(attribute6, 1.234, 1.234);
  group &= attribute_assignment_string(attribute6, "1.233", "1.233");
  group &= attribute_assignment_bool(attribute6, (bool) 1.23,  true);

  attribute7 = (std::string) "1.1";
  group &= attribute_cast_int(attribute7, 1);
  group &= attribute_cast_double(attribute7, 1.1);
  group &= attribute_cast_string(attribute7, "1.1");
  group &= attribute_cast_bool(attribute7, (bool) false);
  group &= attribute_assignment_int(attribute7, 1, 1);
  group &= attribute_assignment_double(attribute7, 1.234, 1.234);
  group &= attribute_assignment_string(attribute7, "foo", "foo");
  group &= attribute_assignment_bool(attribute7, true, true);

  attribute8 = true;
  group &= attribute_cast_int(attribute8, true);
  group &= attribute_cast_double(attribute8, true);
  group &= attribute_cast_string(attribute8, "true");
  group &= attribute_cast_bool(attribute8, true);
  group &= attribute_assignment_int(attribute8, 5, 1);
  group &= attribute_assignment_double(attribute8, 1.5, 1.0);
  group &= attribute_assignment_string(attribute8, "true", "true");
  group &= attribute_assignment_bool(attribute8, (bool) true, (bool) true);
  result &= group;
  Test(group);

  Testing("Section");
  group = true;
  group &= section_find();
  group &= section_add_insert();
  group &= section_add_bracket();
  group &= section_copy_constructor();
  group &= section_equal_operator();
  group &= section_plus_equals_operator();
  group &= section_clear();
  group &= section_overwrite_insert();
  result &= group;
  Test(group);

  Testing("Registry");
  group = true;
  group &= registry_find();
  group &= registry_section_add_insert();
  group &= registry_section_add_bracket();
  group &= registry_copy_constructor();
  group &= registry_equal_operator();
  group &= registry_plus_equals_operator();
  group &= registry_clear();
  result &= group; 
  Test(group);

  Testing("Registry File Functions");
  group = true;
  group &= read_on_construct();
  group &= write_on_destruct();
  group &= name_information();
  result &= group; 
  Test(group);

  Testing("Comments");
  group = true;
  group &= comment_check();
  result &= group;
  Test(group);

  Testing("Precision Change -- Visual only");
  group = true;
  group &= one_decimal();
  group &= two_decimal();
  group &= three_decimal();
  group &= four_decimal();
  group &= too_many_decimal();
  result &= group;
  Test(group);

  Testing("Operator Overloading (automatic generation)");
  group = true;
  group &= operator_test();
  result &= group;
  Test(group);

  // All done.
  cout << endl << "INILIB test suite: ";

  if (result)
    cout << "All done.  All tests passed." << endl;
  else 
    cout << "All done.  Failures found." << endl;

  return 0;
}


