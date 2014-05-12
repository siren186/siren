// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: section_functions.cc,v 1.6 2000/09/03 19:42:05 bwbarrett Exp $
//
// Test most of the commands in the section class.  The file commands
// are tested elsewhere.
//


#include <string>

#include "inilib.h"
#include "inilib_test.h"

using namespace std;
using namespace INI;

bool
section_find()
{
  bool result = true;
  section section1;
  int test_int = 1;
  
  Testing("Section::find()");

  section1.insert("test", test_int);
  // make sure something is found...
  if (section1.find("test") == section1.end()) {
    result = false;
    Fail();
  // check to make sure it returned an acceptable iterator
 } else if (!( (*section1.find("test")).first == "test")) {
    result = false;
    Fail();
  // does something that shouldn't be found return the end() iterator?
 } else if (section1.find("nofind") != section1.end()) {
    result = false;
    Fail();
 } else
    Pass();

  return result;
}


bool
section_add_insert()
{
  bool result = true;
  section section1;
  int test_int = 1;
  
  Testing("Section::Adding Section - insert()");
  
  section1.insert("test", test_int);
  if (section1.find("test") == section1.end()) {
    result = false;
    Fail();
  } else
    Pass();

  return result;
}


bool
section_add_bracket()
{
  bool result = true;
  section section2;
  int_attribute attribute2(1);

  Testing("Section::Adding Section - []");

  section2["test"] = attribute2;
  if (section2.find("test") == section2.end()) {
    result = false;
    Fail();
  } else
    Pass();

  return result;
}


bool
section_copy_constructor()
{
  bool result = true;
  section section1;
  int_attribute attribute1(1);

  Testing("Section::Copy constructor");

  // have to create a section....
  section1["test"] = attribute1;
  
  section section2(section1);
  if ( section2.end() == section2.find("test")) {
    result = false;
    Fail();
  } else
    Pass();

  return result;
}


bool
section_equal_operator()
{
  bool result = true;
  section section1, section2;
  int_attribute attribute1(1);
  
  Testing("Section::= operator");

  section1["test"] = attribute1;

  section2 = section1;
  if (section2.find("test") == section2.end() ) {
    result = false;
    Fail();
  } else
    Pass();

  return result;
}


bool
section_plus_equals_operator()
{
  bool result = true;
  section section1, section2;
  int_attribute attribute1(1);
  
  Testing("Section::+= operator");
  
  section1["test1"] = attribute1;
  section2["test2"] = attribute1;

  section2 += section1;
  if (section2.find("test2") == section2.end()) {
    result = false;
    Fail();
  } else if (section2.find("test1") == section2.end()) {
    result = false;
    Fail();
  } else 
    Pass();

  return result;
}

bool
section_clear()
{  
  bool result = true;

  section section1;
  int_attribute attribute1(1);

  Testing("Section::clear()");
  section1["test1"] = attribute1;

  section1.clear();
  if (!(section1.find("test1") == section1.end() )) {
    result = false;
    Fail();
  } else
    Pass();

  return result;
}


bool
section_overwrite_insert()
{
  // This test is more for memory checking than anything.
  bool result = true;

  section section1;

  Testing("Overwriting attributes with insert()");
  section1.insert("test", 2);
  section1.insert("test", 1);
  section1.insert("test", 3.4);
  section1.insert("test", (string) "foo");
  section1.insert("test", true);

  // JMS Put in a real test here...

  Pass();
  return result;
}
