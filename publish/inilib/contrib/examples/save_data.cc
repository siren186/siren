// save_data.cc
//
// $COPYRIGHT$
//
// $Id: save_data.cc,v 1.4 2000/09/03 19:38:43 bwbarrett Exp $
//
// Description: example of saving data to a file.
//


#include <string>
#include <inilib.h>

using namespace std;
using namespace INI;

int
main(int argc, char *argv[])
{
  // as expected, create a registry
  registry example_registry;

  // Since we need something here, populate the registry.  This really
  // has nothing to do with saving data to disk, but the example is
  // pretty useless without it.
  example_registry["section 1"]["value 1"] = "I'm a string";
  example_registry["section 1"]["value 2"] = 1;
  example_registry["section 1"]["value 3"] = 1.234567890;
  example_registry["section 1"]["value 4"] = true;

  example_registry["section 2"]["value 2"] = "Another string";
  example_registry["section 2"]["value 3"] = 2;
  example_registry["section 2"]["value 4"] = 3.1415;
  example_registry["section 2"]["value 5"] = false;

  // now write the file to disk.
  example_registry.file_write("output.ini");

  // have the program produce some output...
  cout << "This program really doesn't produce any output." << endl;

  return 0;
}
