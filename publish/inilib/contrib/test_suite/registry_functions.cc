// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: registry_functions.cc,v 1.8 2000/09/03 19:42:05 bwbarrett Exp $
//
// Test most of the commands in the registry class.  The file commands
// are tested elsewhere.
//


#include <string>

#include "inilib.h"
#include "inilib_test.h"

using namespace std;
using namespace INI;


bool
registry_find()
{
  bool value = false;

  registry registry1;
  section section1;
  
  Testing("Registry::find()");

  registry1.insert("test", section1);
  // make sure something is found...
  if (registry1.find("test") == registry1.end()) {
    Fail();
  // check to make sure it returned an acceptable iterator
  } else if (!( (*registry1.find("test")).first == "test")) {
    Fail();
  // does something that shouldn't be found return the end() iterator?
  } else if (registry1.find("nofind") != registry1.end()) {
    Fail();
  } else {
    Pass();
    value = true;
  }

  return value;
}


bool
registry_section_add_insert()
{
  bool value = true;

  registry registry1;
  section section1;

  Testing("Registry::Adding Section - insert()");
  
  registry1.insert("test", section1);
  if (registry1.find("test") == registry1.end()) {
    Fail();
    value = false;
  } else {
    Pass();
  }
  
  return value;
}


bool
registry_section_add_bracket()
{
  bool value = true;

  registry registry1;
  section section1;

  Testing("Registry::Adding Section - []");

  registry1["test"] = section1;
  if (registry1.find("test") == registry1.end() ) {
    Fail();
    value = false;
  } else {
    Pass();
  } 
  
  return value;
}


bool
registry_copy_constructor()
{
  bool value = true;

  registry registry1;
  section section1;

  Testing("Registry::Copy constructor");

  // have to create a registry....
  registry1["test"] = section1;
  
  registry registry2(registry1);
  if (registry2.find("test") == registry2.end() ) {
    value = false;
    Fail();
  } else {
    Pass();
  }

  return value;
}


bool
registry_equal_operator()
{
  bool value = true;

  registry registry1, registry2;
  section section1;
  
  Testing("Registry::= operator");

  registry1["test"] = section1;

  registry2 = registry1;
  if (registry2.find("test") == registry2.end() ) {
    value = false;
    Fail();
  } else {
    Pass();
  }
  
  return value;
}


bool
registry_plus_equals_operator()
{
  bool value = true;

  registry registry1, registry2;
  section section1;
  
  Testing("Registry::+= operator");
  
  registry1["test1"] = section1;
  registry2["test2"] = section1;

  registry2 += registry1;
  if (registry2.find("test2") == registry2.end()) {
    value = false;
    Fail();
  } else if (registry2.find("test1") == registry2.end()) {
    value = false;
    Fail();
  } else 
    Pass();

  return value;
}

bool
registry_clear()
{  
  bool value = true;
  
  registry registry1;
  section section1;

  Testing("Registry::clear()");
  registry1["test1"] = section1;

  registry1.clear();
  if (!(registry1.find("test1") == registry1.end() )) {
    value = false;
    Fail();
  } else
    Pass();

  return value;
}
