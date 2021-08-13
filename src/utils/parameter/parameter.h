#ifndef PARAMETER_H
#define PARAMETER_H
#include <iostream>
#include <type_traits>
  
template <class T>
class parameter {
    std::string name;
    T param;
  public:
    parameter (std::string n, T v)
    {
      name=n; param=v;
    }
    // Overload << for cout
    friend std::ostream& operator<< (std::ostream & os, const parameter& rhs) {
        os << rhs.param;
        return os;
    }
    // Overload ==/<=/>=/</> for comparison
    bool operator <(const T v) { return param < v; }
    bool operator >(const T v) { return v < param; }
    bool operator ==(const T v) { return v == param; }
    bool operator !=(const T v) { return !(v == param); }
    bool operator <=(const T v) { return !(param > v); }
    bool operator >=(const T v) { return !(param < v); }
    operator bool()  { 
        static_assert((std::is_same<T, bool>::value), "Parameter is not a boolean and cannot be used as a bool in IF statement");

        if (std::is_same<T, bool>::value) {
            return param;
        }
        return false;
    }
};


#endif // PARAMETER_H