#ifndef PARAMETER_H
#define PARAMETER_H
#include <iostream>
#include <type_traits>
#include <map>
#include <any>
/*
    @brief Contains all code used for parameters to modify model
        Parameter<T>    - Template class used to modify model characteristics
        ParameterBase   - Base class for Parameter<T> to be used as pointer

*/
class ParameterBase {
    public:
        void ReadConfigFile();
        // Need to call this for each parameter in config file
        /*void TempModifyOne(std::string name ) {
            auto it = all_parameters_.find(name);
            if (it != all_parameters_.end()) {
                ParameterBase* temp = it->second;
                temp->SetValue(2);
            }
        }*/

        // Not sure of a more efficient way to do this...
        virtual void SetValue(int v) {}
        virtual void SetValue(bool v) {}

    protected:
        inline static std::map<std::string,ParameterBase*> all_parameters_;
};

template <class T>
class parameter : public ParameterBase {
    std::string name;
    T param;
  public:
    parameter (std::string n, T v)
    {
      name=n; 
      param=v;
      Connect();
    }

    T value() {
        return param;
    }

    void SetValue(T v) {
        param = v;
    };

    void Connect() {
        if (all_parameters_.find(name) == all_parameters_.end()) {
            all_parameters_.insert(std::pair<std::string,ParameterBase*>(name,this));
        } else {
            std::cout << "Error: more than one parameter with the name - " << name << "\n";
            throw std::invalid_argument("More than one parameter with the same name");
        }
    }

    operator T() const {
        return param;
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
    // Overload '-'
    friend T operator -(const parameter<T>& v, const parameter<T>& p) { 
        return (v.param - p.param); 
    };
    friend T operator -(const T v, const parameter<T>& p) { 
        return (v - p.param); 
    };
    friend T operator -(const parameter<T>& p, const T v) { 
        return (p.param - v); 
    };
    // Overload '+'
    friend T operator +(const parameter<T>& v, const parameter<T>& p) { 
        return (v.param + p.param); 
    };
    friend T operator +(const T v, const parameter<T>& p) { 
        return (v + p.param); 
    };
    friend T operator +(const parameter<T>& p, const T v) { 
        return (p.param + v); 
    };
    // Overload '*'
    friend T operator *(const parameter<T>& v, const parameter<T>& p) { 
        return (v.param * p.param); 
    };
    friend T operator *(const T v, const parameter<T>& p) { 
        return (v * p.param); 
    };
    friend T operator *(const parameter<T>& p, const T v) { 
        return (p.param * v); 
    };
    // Overload '/'
    friend T operator /(const parameter<T>& v, const parameter<T>& p) { 
        return (v.param / p.param); 
    };
    friend T operator /(const T v, const parameter<T>& p) { 
        return (v / p.param); 
    };
    friend T operator /(const parameter<T>& p, const T v) { 
        return (p.param / v); 
    };

    // This seems to be called over the Operator T(), don't need this.
    /*operator bool()  { 
        //static_assert((std::is_same<T, bool>::value), "Parameter is not a boolean and cannot be used as a bool in IF statement");
        if (std::is_same<T, bool>::value) {
            return param;
        }
        std::cout << "This is being used\n";
        return false;
    }*/
};

#endif // PARAMETER_H