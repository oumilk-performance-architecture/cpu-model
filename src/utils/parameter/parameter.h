#ifndef PARAMETER_H
#define PARAMETER_H
#include <iostream>
#include <type_traits>

template<class T> class parameter;

template <class T>
class parameter {
    std::string name;
    T param;
  public:
    parameter (std::string n, T v)
    {
      name=n; 
      param=v;
    }
    parameter (T v): param(v) {

    }

    // Overload << for cout
    friend std::ostream& operator<< (std::ostream & os, const parameter& rhs) {
        os << rhs.param;
        return os;
    }
    // Overload '<'
    friend bool operator <(const parameter<T>& v, const parameter<T>& p) { 
        return p.param > v.param; 
    };
    friend bool operator <(const T v, const parameter<T>& p) { 
        return p.param > v; 
    };
    friend bool operator >(const parameter<T>& p, const T v) { 
        return p.param > v; 
    };
    // Overload '>'
    friend bool operator >(const parameter<T>& v, const parameter<T>& p) { 
        return v.param > p.param; 
    }
    friend bool operator >(const T v, const parameter<T>& p) { 
        return v > p.param; 
    }
    friend bool operator <(const parameter<T>& p, const T v) { 
        return v > p.param; 
    }
    // Overload '=='
    friend bool operator == (const parameter<T>& v, const parameter<T>& p) {
        return p.param == v.param;
    };
    friend bool operator == (const T v, const parameter<T>& p) {
        return p.param == v;
    };
    friend bool operator == (const parameter<T>& p, const T v) {
        return p.param == v;
    };
    // Overload '!='
    friend bool operator != (const parameter<T>& v, const parameter<T>& p) {
        return p.param != v.param;
    };
    friend bool operator != (const T v, const parameter<T>& p) {
        return p.param != v;
    };
    friend bool operator != (const parameter<T>& p, const T v) {
        return p.param != v;
    };
    // Overload '<='
    friend bool operator <=(const parameter<T>& v, const parameter<T>& p) { 
        return !(p.param < v.param); 
    };
    friend bool operator <=(const T v, const parameter<T>& p) { 
        return !(p.param < v); 
    };
    friend bool operator >=(const parameter<T>& p, const T v) { 
        return !(p.param < v); 
    };
    // Overload '>='
    friend bool operator >=(const parameter<T>& v, const parameter<T>& p) { 
        return !(v.param < p.param); 
    }
    friend bool operator >=(const T v, const parameter<T>& p) { 
        return !(v < p.param); 
    }
    friend bool operator <=(const parameter<T>& p, const T v) { 
        return !(v < p.param); 
    }

    operator bool()  { 
        //static_assert((std::is_same<T, bool>::value), "Parameter is not a boolean and cannot be used as a bool in IF statement");
        if (std::is_same<T, bool>::value) {
            return param;
        }
        return false;
    }
};

#endif // PARAMETER_H