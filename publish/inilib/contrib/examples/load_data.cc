// load_data.cc
//
// $COPYRIGHT$
//
// $Id: load_data.cc,v 1.5 2002/05/09 19:07:30 bwbarrett Exp $
//
// Description: example of loading data from a file.
//


#include <string>
#include <inilib.h>

using namespace std;
using namespace INI;

int
main(int argc, char *argv[])
{
  // first things first.  Create a registry:
  registry example_registry;

  // start by setting all the default values.  This step can be
  // skipped, although it has two consequences: A) If a variable isn't
  // defined in the file read, it will not exist in the registry.  B)
  // All variables in the file will be stored as strings, which can
  // mean a slight speed loss and a loss of data for doubles (See the
  // documentation for more information on this).

  example_registry["section 1"]["value 1"] = "NULL";
  example_registry["section 1"]["value 2"] = 0;
  example_registry["section 1"]["value 3"] = 0.0;
  example_registry["section 1"]["value 4"] = false;
  
  example_registry["section 2"]["value 1"] = "NULL";
  example_registry["section 2"]["value 2"] = 2;
  example_registry["section 2"]["value 3"] = 2.2;
  example_registry["section 2"]["value 4"] = true;

  // read in the data from a file.
  example_registry.file_read("input.ini");

  // if this were a usefull application, you would now be doing
  // something with the data you just read in.

  // have the program produce some output...
  cout << "The registry..." << endl;

  cout << example_registry["section 1"]["value 1"] << endl;
  cout << example_registry["section 1"]["value 2"] << endl;
  cout << example_registry["section 1"]["value 3"] << endl;
  cout << example_registry["section 1"]["value 4"] << endl;

  cout << example_registry["section 2"]["value 1"] << endl;
  cout << example_registry["section 2"]["value 2"] << endl;
  cout << example_registry["section 2"]["value 3"] << endl;
  cout << example_registry["section 2"]["value 4"] << endl;

  return 0;
}
