// attributes.cc
//
// $COPYRIGHT$
//
// $Id: attributes.cc,v 1.6 2000/09/03 19:38:43 bwbarrett Exp $
//
// Description: An example of some of the ways to add attributes
//              to the registry
//


#include <string>
#include <iostream>
#include <inilib.h>

using namespace std;
using namespace INI;

int
main(int argc, char *argv[])
{
  // As you know (you have read the docs, right), there is more than
  // one way to add an attribute.  Not only that, but there is a
  // difference in how the attributes are created depending on how you
  // first created the attribute.

  // To make the syntax a little easier, explicitly create a section
  // and deal with that directly:
  section example_section;
  
  // Method 1 for adding an attribute: using the insert method.  This
  // creates an attribute who's type is either an int, double, string,
  // or bool depending on what type the value you passed tothe insert
  // method.

  // For example, to create an attribute called value 1 with an
  // integer value, we would call:
  example_section.insert("value 1", 1);

  // or to do the same, but with a double, we could call:
  example_section.insert("value 2", 2.2);

  // of course, that is really no different than this:
  double im_a_double = 2.2;
  example_section.insert("value 3", im_a_double);


  // Method 2 for adding an attribute: implicitly creating an
  // attribute usingthe [] operator.  This occurs in one of two
  // situations: 1) you call <variable> = <some section>["foo"], where
  // foo is not in <some section> or 2) you call <some section>["foo"]
  // = variable, where foo is not in <some section>.  
  //
  // In both of these cases, an attribute must be created before we
  // know the type of the attribute.  So we use a wrapper attribute to
  // cover this case.  Once the type is known, the wrapper attribute
  // creates an attribute of that type and redirects all methods to
  // that attribute type.  
  //
  // What does all this mean for you?  There is an extra function call
  // every time you access an attribute created this way.  That's it.
  // So if you don't mind an extra function call here and there, just
  // use this method.  It's much easier.  This how attributes are
  // created in all the other examples.

  // This will create an int attribute with value 1:
  example_section["value 4"] = 1;

  // This will create a double attribute with value 5:
  example_section["value 5"] = 5;

  // This will create an int attribute, with unspecified value.  A
  // value of 0 will be assigned to im_an_int:
  int im_an_int = example_section["value 6"];
  example_section["value 7"] = im_an_int;
  
  // Regardless of whether the value assigned to/from is an int,
  // double, string, or bool, the code operates in a similar fasion.
  // All possiblities are not shown so that this example didn't go on
  // forever.

  // have the program produce some output...
  cout << "This program really doesn't produce any output." << endl;


  return 0;
}
