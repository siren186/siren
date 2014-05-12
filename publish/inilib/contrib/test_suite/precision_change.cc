// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: precision_change.cc,v 1.3 2005/03/10 18:13:11 bwbarrett Exp $
//
// Tests the attribute precision change functions.
//


#include <string>

#include "inilib.h"
#include "inilib_test.h"

using namespace std;
using namespace INI;

const double value = 1.2345678;

bool
one_decimal()
{
  Testing("Printing 1 decimal digit");

  section section1;
  section1.insert("foo", value);

  attribute::set_precision(1);

  Pass((string) section1["foo"]);

  return true;
}

bool
two_decimal()
{
  Testing("Printing 2 decimal digits");

  section section1;
  section1.insert("foo", value);

  attribute::set_precision(2);

  Pass((string) section1["foo"]);

  return true;
}


bool
three_decimal()
{
  Testing("Printing 3 decimal digits");

  section section1;
  section1.insert("foo", value);

  attribute::set_precision(3);

  Pass((string) section1["foo"]);

  return true;
}


bool
four_decimal()
{
  Testing("Printing 4 decimal digits");

  section section1;
  section1.insert("foo", value);

  attribute::set_precision(4);

  Pass((string) section1["foo"]);

  return true;
}


bool
too_many_decimal()
{
  Testing("Precision set too high");

  section section1;
  section1.insert("foo", value);

  attribute::set_precision(100000);

  if (attribute::get_precision() != 100) {
    Fail();
    return false;
  } else {
    Pass();
  }

  return true;
}




