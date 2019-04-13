#include "PhysicalNumber.h"
#include <regex>
#include <math.h>

using namespace ariel;
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
  return PhysicalNumber(_value*(-1),_unit);}

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
   PhysicalNumber ans = *this + other;
   this->_value = ans._value;
   return *this;
 }
PhysicalNumber& PhysicalNumber::operator-=(const PhysicalNumber& other) {
   PhysicalNumber ans = *this - other;
   this->_value = ans._value;
   return *this;
}
PhysicalNumber PhysicalNumber::operator-(const PhysicalNumber& other) {
   const PhysicalNumber c(_value*(-1) , this->_unit);
   PhysicalNumber result = compare(c , other);
   //std::cout << result << '\n';
   //this->_value = ans._value;
   result._value *= -1;
   return result;
}
bool PhysicalNumber::operator==(const PhysicalNumber& other) {
  if (
    (this->_value == other._value) &&  (this->_unit == other._unit)) {
    return true;
}
else {
  return false;
}
}

bool ariel::operator!=(const PhysicalNumber& p1, const PhysicalNumber& p2) { if (!(p2._value
   == p1._value)) return true; else return false; }
bool ariel::operator>=(const PhysicalNumber& p1, const PhysicalNumber& p2) { if (!(p2 <= p1)) return true; else return false; }
bool ariel::operator>(const PhysicalNumber& p1, const PhysicalNumber& p2) {  if ((p1 < p2)) return true; else return false; }
bool ariel::operator<=(const PhysicalNumber& p1, const PhysicalNumber& p2) { if (!(p2 >= p1)) return true; else return false; }
bool ariel::operator<(const PhysicalNumber& p1, const PhysicalNumber& p2) { if (!(p2 > p1)) return true; else return false; }
//bool ariel::operator<(const PhysicalNumber& p1, const PhysicalNumber& p2) { if (!(p2 > p1)) return true; else return false; }


ostream& ariel::operator<< (ostream& os, const PhysicalNumber& num) {
    string printUnit = "";
    switch(num._unit){
        case Unit::KM: printUnit = "[km]"; break;
        case Unit::M: printUnit = "[m]"; break;
        case Unit::CM: printUnit = "[cm]"; break;
        case Unit::SEC: printUnit = "[sec]"; break;
        case Unit::HOUR: printUnit = "[hour]"; break;
        case Unit::G: printUnit = "[g]"; break;
        case Unit::KG: printUnit = "[kg]"; break;
        case Unit::TON: printUnit = "[ton]"; break;
        default: printUnit = "[deafult]"; break; //need to correct, case of cout << a+b << endl;
    }
    return os << num._value << '[' << printUnit << ']';
}

//Input operator, example: istringstream input("700[kg]"); input >> a;
istream& ariel::operator>> (istream& is, PhysicalNumber& num){
    is>> num._value; //need to correct
    return is;
}
PhysicalNumber PhysicalNumber::compare(const PhysicalNumber& p1 , const PhysicalNumber& p2){
  if (p1._r != p2._r) {
    throw string("bad unit types");
  }
  if (int(p1._unit) == int(p2._unit)) {
    std::cout << "I SHOULD NOT GET HERE FOR THIS CHECK" << '\n';
    return PhysicalNumber(p1._value+p2._value,p1._unit);
  }
  else if ((p1._r == p2._r) && int(p1._unit) != int(p2._unit)) {
    //std::cout << "ROW 131" << '\n';
    /* now check cases for covertions */
    int unOfp1 = int(p1._unit);
    int unOfp2 = int(p2._unit);
  //  std::cout << "ROW 135" << '\n';
    double dVal = (unOfp1 < unOfp2) ? p1._value : p2._value ;
    double oVal = (unOfp1 > unOfp2) ? p1._value : p2._value ;
//std::cout << "SHORT IF'S AT ROW 138 NOW" << '\n';
    int toCovert = fmax(unOfp1,unOfp2);
  //  std::cout << "fmax() CALL" << '\n';
    int dominateUnit = unOfp1 < unOfp2 ? unOfp1 : unOfp2 ;
    //std::cout << dominateUnit << '\n';
    //std::cout << toCovert << '\n';
    switch (p1._r) {
      case 0: //distances
      {
        if (dominateUnit==0) {
          if (toCovert==3) {
    //        std::cout << "Sould enter here , crushes" << '\n';
            return PhysicalNumber(dVal + oVal/1000 , Unit::KM);
            break;
          }
          else {return PhysicalNumber(dVal + oVal/100000 , Unit::KM);
          break;
        }
        }
        else if (dominateUnit==3) {
            return PhysicalNumber(dVal + oVal/100 , Unit::M );
            break;
          }
        }
        case 1: //weight
        {
          if (dominateUnit==1) {
               if (toCovert==4) {
                 return PhysicalNumber(dVal + oVal/1000 , Unit::TON);
                 break;
               }
               else{
                 return PhysicalNumber(dVal + oVal/1000000 , Unit::TON);
                 break;
               }
          }
          else if (dominateUnit==4) {
            return PhysicalNumber(dVal + oVal/1000 , Unit::KG);
            break;
          }
        }
        case 2: //Time
        {
          if (dominateUnit==2) {
            if (toCovert==5) {
              return PhysicalNumber(dVal + oVal/60 , Unit::HOUR);
              break;
            }
            else{
              return PhysicalNumber(dVal + oVal/360 , Unit::HOUR);
              break;
            }
          }
          else if (dominateUnit==5) {
            return PhysicalNumber(dVal + oVal/60 , Unit::MIN);
            break;
          }
        }
      }
    }
  }
