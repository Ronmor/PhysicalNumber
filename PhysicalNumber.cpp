#include "PhysicalNumber.h"
#include <regex>
#include <math.h>

using namespace ariel;
/*
#define KM Unit::KM
#define TON Unit::TON
#define HOUR Unit::HOUR
#define M Unit::M
#define KG Unit::KG
#define MIN Unit::MIN
#define CM Unit::CM
#define G Unit::G
#define SE Unit::SEC
*/

//using ariel::Remainder, ariel::PhysicalNumber;
/*
bool ariel::equals(const Remainder& r1 , const Remainder& r2){
    if(r1==r2) return true;
    else{return false;}
}

ariel::PhysicalNumber(const float num , Unit unit) {
    switch(unit){
        case Unit::KM: Remainder::Length;
        case Unit::TON: Remainder::Weight;
        case Unit::HOUR: Remainder::Time;
        case Unit::M: Remainder::Length;
        case Unit::KG: Remainder::Weight;
        case Unit::MIN: Remainder::Time;
        case Unit::CM: Remainder::Length;
        case Unit::G: Remainder::Weight;
        case Unit::SEC: Remainder::Time;
    }
    this->_unit = unit;
    this->_value = num;
  }
*/

ariel::PhysicalNumber::PhysicalNumber(double num , Unit unit){
  this->_value = num;
  this->_unit = unit;
  this->_r = int(unit) % 3;
}


const PhysicalNumber PhysicalNumber::operator-() const{
  return PhysicalNumber(_value*(-1),_unit);
}

const PhysicalNumber PhysicalNumber::operator+() const{
//  std::cout << "row 40" << '\n';
  return *this;
}
const PhysicalNumber PhysicalNumber::operator+(const PhysicalNumber& other){
  const PhysicalNumber phy = compare(*this , other);
  //std::cout << "i have returned" << '\n';
  return phy;
}
PhysicalNumber& PhysicalNumber::operator+=(const PhysicalNumber& other) {
  try{
    if (this->_r == other._r) {
   const PhysicalNumber ans = compare(*this , other);
   this->_value = ans._value;
   this->_unit = ans._unit;
 }
}
 catch (const std::exception& ex) {
   cout << ex.what() << endl; // Prints "Units do not match - [m] cannot be converted to [kg]"
 }
catch (...) {
 cout << "Bad Units" << endl;
}
   return *this;
 }
PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other) {
   PhysicalNumber ans = *this - other;
   this->_value = ans._value;
   return *this;
}
PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& other) {
   const PhysicalNumber c(_value*(-1) + 0 , this->_unit);
   PhysicalNumber result = compare(c , other);
   //std::cout << result << '\n';
   //this->_value = ans._value;
   result._value *= -1;
   if (result._value== -0.0) {
     result._value = 0;
   }
   return result;
}
bool PhysicalNumber::operator==(const PhysicalNumber& other) {
  const PhysicalNumber p = +(other);
  PhysicalNumber n = operator-(other);
  if (this->_value-other._value == 0){
    return true;
}
else {
  return false;
}
}
bool ariel::operator!=(const PhysicalNumber& p1, const PhysicalNumber& p2)
{
   if (!(p2._value==p1._value)) {return true;}
    else
    {return false;}
    }
bool ariel::operator>=(const PhysicalNumber& p1, const PhysicalNumber& p2) { if (!(p2 <= p1)) return true; else return false; }
bool ariel::operator>(const PhysicalNumber& p1,const PhysicalNumber& p2)
{
  //std::cout << p1._r << p2._r << '\n';
  if (p1._r != p2._r) {
    return false;
  }
   else
   {
     PhysicalNumber n = +(p2);
  //   std::cout << n._value << '\n';
     return n._value>0;
   }
   }
bool ariel::operator<=(const PhysicalNumber& p1, const PhysicalNumber& p2){
  return p2>p1;
  }
bool ariel::operator<(const PhysicalNumber& p1, const PhysicalNumber& p2) {
   return p2<=p1;}
//bool ariel::operator<(const PhysicalNumber& p1, const PhysicalNumber& p2) { if (!(p2 > p1)) return true; else return false; }


ostream& ariel::operator<< (ostream& os, const PhysicalNumber& num) {
    string printUnit = "";
    switch(num._unit){
        case Unit::KM: printUnit = "[km]"; break;
        case Unit::M: printUnit = "[m]"; break;
        case Unit::CM: printUnit = "[cm]"; break;
        case Unit::SEC: printUnit = "[sec]"; break;
        case Unit::HOUR: printUnit = "[hour]"; break;
        case Unit::MIN: printUnit = "[min]"; break;
        case Unit::G: printUnit = "[g]"; break;
        case Unit::KG: printUnit = "[kg]"; break;
        case Unit::TON: printUnit = "[ton]"; break;
        default: printUnit = "[deafult]"; break; //need to correct, case of cout << a+b << endl;
    }
    return os << num._value << printUnit;
}

//Input operator, example: istringstream input("700[kg]"); input >> a;
istream& ariel::operator>> (istream& is, PhysicalNumber& num){
    string printUnit = "";
    is>> num._value >>printUnit; //need to correct
    return is;
}
  /*
  string input_string = "";
  double val;
  string unit_string = "";
  Unit unit;

  is >> input_string;
  if(sscanf(input_string.c_str(), "%lf[%s]", &val, unit_string) == 2){
    switch (unit_string) {
      case "cm":    unit = Unit::CM;
      case "m":     unit = Unit::M;
      case "km":    unit = Unit::KM;
      case "sec":   unit = Unit::SEC;
      case "min":   unit = Unit::MIN;
      case "hour":  unit = Unit::HOUR;
      case "g":     unit = Unit::G;
      case "kg":    unit = Unit::KG;
      case "ton":   unit = Unit::TON;
      case default: // exception;
    }
    num._value = val;
    num._unit = unit;
  }
  else {
    //exception
  }
  return is;
}
*/
PhysicalNumber PhysicalNumber::compare(const PhysicalNumber& p1 , const PhysicalNumber& p2){
  if (p1._r != p2._r) {
    throw string("bad unit types");
  }
  if (int(p1._unit) == int(p2._unit)) {
  //  std::cout << "I SHOULD NOT GET HERE FOR THIS CHECK" << '\n';
    return PhysicalNumber(p1._value+p2._value,p1._unit);
  }
  else if ((p1._r == p2._r) && int(p1._unit) != int(p2._unit)) {
    //std::cout << "ROW 131" << '\n';
    /* now check cases for covertions */
    int unOfp1 = int(p1._unit);
    int unOfp2 = int(p2._unit);
  //  std::cout << "ROW 135" << '\n';
    double dVal = p1._value;
    double oVal = p2._value;
//std::cout << "SHORT IF'S AT ROW 138 NOW" << '\n';
    //int toCovert = fmax(unOfp1,unOfp2);
  //  std::cout << "fmax() CALL" << '\n';
    //int dominateUnit = unOfp1 < unOfp2 ? unOfp1 : unOfp2 ;
    //std::cout << dominateUnit << '\n';
    //std::cout << toCovert << '\n';
    switch (p1._r) {
      case 0: //distances
      {
        if (unOfp1==0) {
          if (unOfp2==3) {
    //        std::cout << "Sould enter here , crushes" << '\n';
            return PhysicalNumber(dVal + oVal/1000 , Unit::KM);
            break;
          }
          else {return PhysicalNumber(dVal + oVal/100000 , Unit::KM);
          break;
        }
        }
        else if (unOfp1==3) {
          if (unOfp2==0) {
            return PhysicalNumber(dVal + oVal*1000,Unit::M);
          }
          else{
            return PhysicalNumber(dVal + oVal/100 , Unit::M );
            break;
          }
        }
        else {
          if (unOfp2==0) {
            return PhysicalNumber(dVal + oVal*100000 , Unit::CM);
          }
          else{
            return PhysicalNumber(dVal + oVal*100 , Unit::CM);
          }
        }
        case 1: //weight
        {
          if (unOfp1==1) { //TON
               if (unOfp2==4) { //KG
                 return PhysicalNumber(dVal + oVal/1000 , Unit::TON);
                 break;
               }
               else{ //G
                 return PhysicalNumber(dVal + oVal/1000000 , Unit::TON);
                 break;
               }
          }
          else if (unOfp1==4) { //KG
            if (unOfp2==1) { //TON
              return PhysicalNumber(dVal+oVal*1000 , Unit::KG);
            }//gram
            return PhysicalNumber(dVal + oVal/1000 , Unit::KG);
            break;
          }
          else // in gram
          {
            if (unOfp2==1) { //TON
              return PhysicalNumber(dVal + oVal/1000000 , Unit::G);
            }
            else{ //KG
              return PhysicalNumber(dVal + oVal/1000 , Unit::G);
            }
          }
        }
        case 2: //Time
        {
          if (unOfp1==2) { //HOUR
            if (unOfp2==5) { //MIN
              return PhysicalNumber(dVal + oVal/60 , Unit::HOUR);
              break;
            }
            else{ //SEC
              return PhysicalNumber(dVal + oVal/3600 , Unit::HOUR);
              break;
            }
          }
          else if (unOfp1==5) { //MIN
            if (unOfp2==2) { //HOUR
              return PhysicalNumber(dVal + oVal*60 , Unit::MIN);
            }
            else{ //SEC
            return PhysicalNumber(dVal + oVal/60 , Unit::MIN);
            break;
          }
        }
        else //SEC
         {
           if (unOfp2==2) { //HOUR
             return PhysicalNumber(dVal + oVal*3600 , Unit::SEC);
           }
           else { //MIN
             return PhysicalNumber(dVal + oVal*60 , Unit::SEC);
           }
        }
        }
      }
    }
  }
}
