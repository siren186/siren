// convert_types.cc
//
// $COPYRIGHT$
//
// $Id: convert_types.cc,v 1.6 2002/05/09 18:52:54 bwbarrett Exp $
//
// Description: example of some of the type casting abilities of the
//              library
//


#include <string>
#include <iostream>
#include <inilib.h>

using namespace std;
using namespace INI;

int
main(int argc, char *argv[])
{
  // first things first.  Create a registry:
  registry example_registry;

  // inilib overloads operators such that any supported data type
  // (int, double, bool, string) can be cast to or assigned from any
  // of the four types.  Here is a short example.  As always, we start
  // by building up a small registry.
  example_registry["section"]["value 1"] = 1;
  example_registry["section"]["value 2"] = 1.12345;

  // casting from a string to an int or double only makes since if the
  // string represents a base 10 number, so we'll use one for the
  // examples.
  example_registry["section"]["value 3"] = "1.2";
  example_registry["section"]["value 4"] = true;

  // we can cast an integer to double...
  cout << "An int cast to a double: " 
       << (double) example_registry["section"]["value 1"] << endl;

  // and the other way around.  Of course, we lose something in the
  // translation.
  cout << "A double cast to an int: "
       << (int) example_registry["section"]["value 2"] << endl;

  // Casting a double to a string is doable, but notice that inilib
  // causes some data to be lost when it truncates the decimal part of
  // the number.
  //
  // Ostream is overloaded for attribute to implicitly do the
  // (std::string) cast, so that doesn't need to be stated here.
  cout << "A double cast to a string: "
       << example_registry["section"]["value 2"] << endl;

  // Also in the loss of information category is anything cast to a
  // bool.  The rule for this one is non-zero double/int or string
  // "true" is true and all else is false.
  cout << "A string cast to a bool: "
       << (bool) example_registry["section"]["value 3"] << endl;
  
  // A bool cast to a string will be the string's "true" or an empty
  // string (because Perl does it more or less this way).
  cout << "A bool cast to a string: "
       << example_registry["section"]["value 4"] << endl;

  // a bool cast to a double or int will handled however your compiler
  // deals with a bool cast to a double or int.
  cout << "A bool cast to a double: "
       << (double) example_registry["section"]["value 4"] << endl;

  // of course, you can have implicit casting when you are doing
  // assignment.  So if you wanted to do;
  int im_an_int = example_registry["section"]["value 2"];
  example_registry["section"]["value 3"] = im_an_int;

  // example_registry["section"]["value 2"] will be cast to an int,
  // then the integer assignment operator will set im_an_int to the
  // value returned by the cast (1 in this case).

  // the assignment operator is also overloaded for the attribute
  // class, so you can assign any int, double, bool, or string to any
  // attribute, regardless of it's type.  

  // So we can assign a double to an int attribute:
  example_registry["section"]["value 1"] = 2.3456;

  // of course, as noted above, we've lost some (ok, a lot) of
  // precision in doing this.  Instead of 2.3456,
  // example_registry["section"]["value 1"] contains 2.
  cout << "Result of assigning 2.3456 to an integer attribute: "
       << (int) example_registry["section"]["value 1"] << endl;

  // again, all possible combinations are not covered in this example.
  // Otherwise, it would get a little long.

  return 0;
}
