
#include <iostream>
#include <stdexcept>
#include <string>
#include "Unit.h"

using namespace std;

namespace ariel{
/*
  enum class Remainder: int{
        Length,
        Weight,
        Time
};


bool equals(const Remainder& r1 , const Remainder& r2);
*/

class PhysicalNumber{

  double _value;
  Unit _unit;
  int _r;



public:

  PhysicalNumber(double,Unit);

  PhysicalNumber compare(const PhysicalNumber& p1 , const PhysicalNumber& p2);
  friend ostream& operator<<(ostream& os, const PhysicalNumber& num);
  friend istream& operator>> (istream& is,PhysicalNumber& num);

  // arithmetic operators
		const PhysicalNumber operator-() const; // *-1
		const PhysicalNumber operator+() const; // does nothing
		const PhysicalNumber operator+(const PhysicalNumber&); // add and return new
		PhysicalNumber operator-(const PhysicalNumber&) ; //sub
		PhysicalNumber& operator+=(const PhysicalNumber&);  //sum this + other
		PhysicalNumber& operator-=(const PhysicalNumber&); // decrease


    //compare
    bool operator==(const PhysicalNumber&); //equals
    //friend bool operator==(const PhysicalNumber&, const PhysicalNumber&); //[V]
		friend bool operator<(const PhysicalNumber&, const PhysicalNumber&);  //[V]
		friend bool operator!=(const PhysicalNumber&, const PhysicalNumber&); //[V]
		friend bool operator<=(const PhysicalNumber&,const PhysicalNumber&); //[V]
		friend bool operator>=(const PhysicalNumber&,const PhysicalNumber&); //[V]
		friend bool operator>(const PhysicalNumber&,const PhysicalNumber&); //[V]
  /*
    note: assuming friend declaration is needed to get accses to PhysicalNumber's fields

    */

    };
}
