// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: operator.cc,v 1.5 2005/03/10 18:13:11 bwbarrett Exp $
//
// Tests all the operators overloaded in the inilib program...
//
// To make this easier, there is a file that contains all the test
// cases we want to use.  This will run all of those test cases,
// building up a really big registry while we are at it....
//


#include <iostream>
#include <fstream>
#include <string>

#include "inilib.h"
#include "inilib_test.h"

using namespace std;
using namespace INI;

// private functions....
static bool get_operand(fstream&, registry&, const int, const std::string&);

bool
operator_test(std::string input)
{
  // just in case...
  attribute::set_precision(4);

  bool result = true;
  int testcase = 1;
  string op;
  string op1_type, op1_value;
  string op2_type, op2_value;
  string ans_type, ans_value;

  registry test("optest.ini", false, false);

  fstream input_file;
  input_file.open(input.c_str(), ios::in);
  if (!input_file) {
    cerr << "Could not open the data file" << endl;
    return false;
  }

  while (input_file && result) {
    input_file >> op;
    if (!input_file)
      continue;

    Testing("Automatic test " + int2str(testcase));
      
    // for the binary comparison functions, we are going to perform
    // that operation with the two given values.  Since that doesn't
    // really test all the cases, the n<boolean function> tests the
    // case, and uses a ! of the result...
    if (op == "==") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (test[int2str(testcase)]["op1"] == test[int2str(testcase)]["op2"])
	Pass();
      else {
	result = false;
	Fail();
      }
    } else if (op == "n==") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (!(test[int2str(testcase)]["op1"] == 
	    test[int2str(testcase)]["op2"]))
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "!=") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (test[int2str(testcase)]["op1"] != test[int2str(testcase)]["op2"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "n!=") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (!(test[int2str(testcase)]["op1"] != 
	    test[int2str(testcase)]["op2"]))
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "<") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (test[int2str(testcase)]["op1"] <
	    test[int2str(testcase)]["op2"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "n<") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (!(test[int2str(testcase)]["op1"] <
	    test[int2str(testcase)]["op2"]))
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "<=") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (test[int2str(testcase)]["op1"] <=
	    test[int2str(testcase)]["op2"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "n<=") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (!(test[int2str(testcase)]["op1"] <=
	    test[int2str(testcase)]["op2"]))
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == ">") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (test[int2str(testcase)]["op1"] >
	    test[int2str(testcase)]["op2"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "n>") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (!(test[int2str(testcase)]["op1"] >
	    test[int2str(testcase)]["op2"]))
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == ">=") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (test[int2str(testcase)]["op1"] >=
	    test[int2str(testcase)]["op2"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "n>=") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      if (!(test[int2str(testcase)]["op1"] >=
	    test[int2str(testcase)]["op2"]))
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "!") {       
      result &= get_operand(input_file, test, testcase, "op1");
      if (!test[int2str(testcase)]["op1"]) 
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "n!") {
      result &= get_operand(input_file, test, testcase, "op1");
      if (!(!test[int2str(testcase)]["op1"]))
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "++") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "ans");
      ++test[int2str(testcase)]["op1"];
      if (test[int2str(testcase)]["op1"] == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "--") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "ans");
      --test[int2str(testcase)]["op1"];
      if (test[int2str(testcase)]["op1"] == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "u-") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "ans");
      if ((-test[int2str(testcase)]["op1"]) == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "*") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      result &= get_operand(input_file, test, testcase, "ans");

      test[int2str(testcase)]["tmp"] = 
	test[int2str(testcase)]["op1"] * test[int2str(testcase)]["op2"];

      if (test[int2str(testcase)]["tmp"] == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "/") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      result &= get_operand(input_file, test, testcase, "ans");

      test[int2str(testcase)]["tmp"] = 
	test[int2str(testcase)]["op1"] / test[int2str(testcase)]["op2"];

      if (test[int2str(testcase)]["tmp"] == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "%") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      result &= get_operand(input_file, test, testcase, "ans");

      test[int2str(testcase)]["tmp"] = 
	test[int2str(testcase)]["op1"] % test[int2str(testcase)]["op2"];

      if (test[int2str(testcase)]["tmp"] == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "+") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      result &= get_operand(input_file, test, testcase, "ans");

      test[int2str(testcase)]["tmp"] = 
	test[int2str(testcase)]["op1"] + test[int2str(testcase)]["op2"];

      if (test[int2str(testcase)]["tmp"] == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else if (op == "-") {
      result &= get_operand(input_file, test, testcase, "op1");
      result &= get_operand(input_file, test, testcase, "op2");
      result &= get_operand(input_file, test, testcase, "ans");

      test[int2str(testcase)]["tmp"] = 
	(test[int2str(testcase)]["op1"] - test[int2str(testcase)]["op2"]);

      if (test[int2str(testcase)]["tmp"] == test[int2str(testcase)]["ans"])
	Pass();
      else {
	result = false;
	Fail();
      }

    } else {
      result = false;
      Fail("Unknown Operator");
    }

    ++testcase;
  } // while loop

  return result;
}


static bool
get_operand(fstream& input_file, registry& test_reg, 
	    const int testcase, const std::string& key)
{
  string op_type;
  bool bool_val;
  double double_val;
  int int_val;
  string string_val;
  
  input_file >> op_type;
  if (!input_file)
    return false;

  if (op_type == "bool") {
    input_file >> string_val;
    if (!input_file)
      return false;
    if (string_val == "true")
      bool_val = true;
    else 
      bool_val = false;
    test_reg[int2str(testcase)][key] = bool_val;
  } else if (op_type == "double") {
    input_file >> double_val;
    if (!input_file)
      return false;
    test_reg[int2str(testcase)][key] = double_val;
  } else   if (op_type == "int") {
    input_file >> int_val;
    if (!input_file)
      return false;
    test_reg[int2str(testcase)][key] = int_val;
  } else   if (op_type == "string") {
    input_file >> string_val;
    if (string_val == "null")
      string_val = "";
    if (!input_file)
      return false;
    test_reg[int2str(testcase)][key] = string_val;
  } else
    return false;

  return true;
}
