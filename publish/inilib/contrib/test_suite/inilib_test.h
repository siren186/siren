// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: inilib_test.h,v 1.15 2004/11/28 05:32:55 bwbarrett Exp $

#ifndef INILIB_TEST_H_
#define INILIB_TEST_H_

#include <string>

// registry_functions.cc
bool registry_find();
bool registry_section_add_insert();
bool registry_section_add_bracket();
bool registry_copy_constructor();
bool registry_equal_operator();
bool registry_plus_equals_operator();
bool registry_clear();

// section_functions.cc
bool section_find();
bool section_add_insert();
bool section_add_bracket();
bool section_copy_constructor();
bool section_equal_operator();
bool section_plus_equals_operator();
bool section_clear();
bool section_overwrite_insert();

// file_functions.cc
bool read_on_construct();
bool write_on_destruct();
bool name_information();

// precision_change.cc
bool one_decimal();
bool two_decimal();
bool three_decimal();
bool four_decimal();
bool too_many_decimal();

// operator.cc
bool operator_test(std::string input = "data.txt");

// messages.cc
void Testing(const std::string& msg);
void Pass(const std::string& msg = "PASS");
void Postpone(const std::string& class_name);
void Done(const std::string& msg = "DONE");
void Fail(const std::string& msg = "FAIL");
void Abort(const std::string& msg = "ABORT");

// comment.cc
bool comment_check();

// General helper functions
inline void 
Test(bool c, const std::string& msg) 
{ 
  (c) ? Pass() : Fail(msg); 
}


inline void 
Test(bool c) 
{ 
  (c) ? Pass() : Fail(); 
}

#endif // INILIB_TEST_H_

