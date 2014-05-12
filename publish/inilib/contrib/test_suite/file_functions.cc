// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: file_functions.cc,v 1.5 2000/12/19 18:21:57 bwbarrett Exp $
//
// Tests the file functions for the registry
//


#include <string>
#include <iostream>

#include "inilib.h"
#include "inilib_test.h"

using namespace std;
using namespace INI;


bool
read_on_construct()
{
  Testing("Read file on construction");

  bool value = true;
  registry reg("test.ini", true, false);

  if ((double) reg["test1"]["foo"] != 1.23) {
    value = false;
    Fail((std::string) reg["test1"]["foo"]);
  } else if ((std::string) reg["test1"]["bar"] != "") {
    value = false;
    Fail("blank");
  } else if ((int) reg["test2"]["bar"] != 3) {
    value = false;
    Fail("2");
  } else {
    Pass();
  }

  return value;
}


bool write_on_destruct_part_one()
{
  bool value = true;
  registry reg("foo.ini", false, true);
  
  reg["write_on_destruct"]["wrote"] = true;

  return value;
}


bool
write_on_destruct()
{
  // depends on read_on_construct already running and being passed.
  bool value = true;
  
  value = write_on_destruct_part_one();

  registry reg("foo.ini", true, false);
  
  Testing("Write file on destruction");

  if ((bool) reg["write_on_destruct"]["wrote"] != true) {
    value = false;
    Fail();
  } else {
    Pass();
  }

  return value;
}


bool
name_information()
{
  bool value = true;
  bool ret = true;
  registry reg1;
  registry reg2("test.ini", false, false);
  registry reg3("test.ini");

  Testing("Filename interactions");

  // First set

  Testing("Constructor values");
  if (reg1.get_filename() != (string) "") {
    value = false;
  } else if (reg1.get_write_on_destruct() == true) {
    value = false;
  } else if (reg2.get_filename() != "test.ini") {
    value = false;
  } else if (reg2.get_write_on_destruct() != false) {
    value = false;
  } else if (reg3.get_write_on_destruct() != true) {
    value = false;
  }
  Test(value);
  ret = value;

  // Second set

  Testing("Explicit values");
  value = true;
  reg2.set_filename("foo.bar");
  reg2.set_write_on_destruct(false);
  reg3.set_write_on_destruct(false);
  
  if (reg2.get_filename() != "foo.bar") {
    value = false;
  } else if (reg2.get_write_on_destruct() != false) {
    value = false;
  }
  Test(value);
  ret &= value;

  // Print out the overall for this subsection

  Test(ret);
  return ret;
}
