//
// This software may only be used by you under license from the
// University of Notre Dame.  A copy of the University of Notre Dame's
// Source Code Agreement is available at the inilib Internet website
// having the URL: <http://inilib.sourceforge.net/license/> If you
// received this software without first entering into a license with the
// University of Notre Dame, you have an infringing copy of this software
// and cannot use it without violating the University of Notre Dame's
// intellectual property rights.
//
// $Id: int_attribute.h,v 1.9 2002/05/09 18:51:21 bwbarrett Exp $
//
// FUNCTION: Parse initialization files,
//           maintain state of program
//           save state of program

#ifndef INI_INT_ATTRIBUTE_H_
#define INI_INT_ATTRIBUTE_H_

#include <string>

#include "attribute.h"

namespace INI {
  class int_attribute : public attribute {
  public:
    int_attribute(int);

    virtual attribute& operator=(int);
    virtual attribute& operator=(double);
    virtual attribute& operator=(const std::string&);
    virtual attribute& operator=(bool);
    virtual attribute& operator=(const attribute&);
    virtual attribute& operator=(const char*);

    virtual operator int() const;
    virtual operator double() const;
    virtual operator std::string() const;
    virtual operator bool() const;

    virtual attribute& operator*=(bool);
    virtual attribute& operator*=(double);
    virtual attribute& operator*=(int);
    virtual attribute& operator*=(const std::string&);
    virtual attribute& operator*=(const attribute&);

    virtual attribute& operator/=(bool);
    virtual attribute& operator/=(double);
    virtual attribute& operator/=(int);
    virtual attribute& operator/=(const std::string&);
    virtual attribute& operator/=(const attribute&);

    virtual attribute& operator%=(bool);
    virtual attribute& operator%=(double);
    virtual attribute& operator%=(int);
    virtual attribute& operator%=(const std::string&);
    virtual attribute& operator%=(const attribute&);

    virtual attribute& operator+=(bool);
    virtual attribute& operator+=(double);
    virtual attribute& operator+=(int);
    virtual attribute& operator+=(const std::string&);
    virtual attribute& operator+=(const attribute&);

    virtual attribute& operator-=(bool);
    virtual attribute& operator-=(double);
    virtual attribute& operator-=(int);
    virtual attribute& operator-=(const std::string&);
    virtual attribute& operator-=(const attribute&);

    virtual attribute& operator++(); // prefix
    virtual attribute& operator--(); 

    virtual attr_type get_type() const;

  protected:
    virtual attribute* make_copy() const;
    int value;

  private:
  };
}

#endif // INI_INT_ATTRIBUTE_H_
