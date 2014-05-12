// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: comment.cc,v 1.1 2004/11/28 05:32:55 bwbarrett Exp $
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
comment_check()
{
  bool value = true;
  registry reg("comment.ini", true, false);

  Testing("Complete line comment");
  if ((std::string) reg["comment"]["key1"] != "value1") {
    value = false;
    Fail((std::string) reg["comment"]["key1"]);
  } else {
    Pass();
  }

  Testing("End of line comment (comment line)");
  if ((std::string) reg["comment"]["key2"] != "value2") {
    value = false;
    Fail((std::string) reg["comment"]["key2"]);
  } else {
    Pass();
  }

  Testing("End of line comment (next line)");
  if ((std::string) reg["comment"]["key3"] != "value3") {
    value = false;
    Fail((std::string) reg["comment"]["key3"]);
  } else {
    Pass();
  }

  return value;
}
