// -*- c++ -*-
//
// $COPYRIGHT$
//
// $Id: messages.cc,v 1.7 2000/09/03 19:42:05 bwbarrett Exp $
//

#include <iostream>
#include <string>
#include <stack>

#include "inilib_test.h"

using namespace std;

//
// Global vars for below
//

static int indent_level = 0;
static int column = 0;
static int num_bullets = -1;
static int waiting = 0;

static const char bullets[] = { '*', '-', 'o', '.', 0 };
static const int dest_column = 50;

static stack<string> msg_stack;

//
// Local functions
//

static void Endline(const string& msg);
static inline void 
decrement(void) 
{ 
  indent_level = (indent_level <= 0) ? 0 : indent_level - 1; 
}

static inline void 
increment(void)
{
  indent_level++; 
};


//
// Testing
//
void
Testing(const string& message)
{
  int i;

  if (num_bullets == -1)
    for (num_bullets= 0; bullets[num_bullets] != 0; num_bullets++)
      continue;

  // Check to see if we are waiting at the end of a line already

  if (waiting)
    cout << endl;

  // Output the indenting and bullet

  column= 0;
  for (i= 0; i < indent_level; i++) {
    cout <<"  ";
    column += 2;
  }

  // Output the message 

  msg_stack.push(message);
  if (indent_level == 0)
    cout << endl;
  cout << bullets[indent_level % num_bullets] << " " << message << "... ";

  column += 6 + message.size();
  for (i= column ; i < dest_column; i++)
    cout << " ";
  cout.flush();

  waiting= 1;
  increment();
}


//
// Pass
//
void
Pass(const string& msg)
{
  decrement();
  Endline(msg);
}

//
// Postpone
//
void
Postpone(const string& class_name)
{
  string tmp;

  tmp = "POSTPONED -- " + class_name;
  Endline(tmp);

  cout.flush();
}


//
// Done
//
void
Done(const string& msg)
{
  decrement();
  Endline(msg);
}


//
// Fail
//
void
Fail(const string& msg)
{
  decrement();
  Endline(msg);
}


//
// Abort
//
void
Abort(const string& msg)
{
  Endline("FAIL");

  cerr << endl;
  if (msg.size() != 0)
    cerr << "inilib test suite: " << msg << endl;

  cerr << "inilib test suite: major error!" << endl;
  cerr << "inilib test suite: terminated" << endl << endl;

  exit(1);
}


//
// Endline
//
static void
Endline(const string& msg)
{
  cout.flush();
  if (waiting) {
    cout << msg << endl;
    msg_stack.pop();
  }
  else {
    // Output the indenting and bullet
    
    int i;
    column = 0;
    for (i = 0; i < indent_level; i++) {
      cout <<"  ";
      column += 2;
    }
    
    string line = msg_stack.top();
    msg_stack.pop();
    cout << bullets[indent_level % num_bullets] << " " << line << "... ";
    for (i = column + 6 + line.size(); i < dest_column; i++)
      cout << " ";
    cout << msg << endl;
    cout.flush();
  }

  waiting= 0;
  column= 0;
}


