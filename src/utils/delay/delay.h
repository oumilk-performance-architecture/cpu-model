#ifndef DELAY_H
#define DELAY_H
/*
    @brief Contains all code used for communication between different modules. 
        Storage<T>       - Template class used to store information passed by Delay
        StorageInterface - Base class for Storage<T> to be used as the pointer to Storage<T> (Can't do a vector of different template types)
        DelayBase        - Base class for Delay/DelayWrite/DelayRead.  Just to store the static vector of all ports
        Delay            - Template class with some shared functions between DelayWrite and DelayRead
        DelayWrite       - Write class, specifies how many writes per cycle
        DelayRead        - Read class, specifies how many cycles before reading

    @author Jonathan Ou
*/
#include <utility>
#include <queue>
#include <iostream>

// StorageInterface 
//   Can't do a vector of different template types so having a base class 
//   that can be used as a pointer
class StorageInterface {
    public:
        StorageInterface(std::string name) {
            name_ = name;
        };
        std::string GetName()  {
            return name_;
        }
    private:
        std::string name_;
};
// Storage for each port
template <class T>
class Storage : public StorageInterface {
    public:
        Storage (std::string name) : StorageInterface(name) {
            //num_readers = 0;
        };
        std::deque<std::pair<T,int>> fifo;
        //bool Send(std::pair <T,int> data) {
        //    fifo.push_back(data);
        //};

    private:
        
        //int num_readers;
};

class DelayBase {
    protected:
        inline static std::vector<std::shared_ptr<StorageInterface>> all_ports;
};

template <class T>
class Delay : public DelayBase {
    public:
        Delay (std::string name) {
            name_ = name;
            latency_ = 1;
            Connect();
        };

        void SetLatency(int latency) {
            latency_ = latency;
        }

        void Send(T d, int c) {
            port_ptr->fifo.push_back(std::make_pair(d,c));
        }
        /*bool IsReady(int c) {
            auto TIsReady = [c](std::pair<T,int> curr) {
                return curr.second == c;
            };
            if (std::find(fifo.begin(), fifo.end(), TIsReady())) {
                return true;
            }
            return false;
        }*/

        bool Receive(T& d, int c) {
            auto msg = std::find_if(port_ptr->fifo.begin(), port_ptr->fifo.end(), [c, l=latency_](std::pair<T,int> curr) {
                return curr.second + l <= c;
            });
            if (msg != port_ptr->fifo.end()) {
                d = msg->first;
                port_ptr->fifo.erase(msg);
                return true;
            }
            return false;
            //assert("Template Delay must have data before receive is called\n");
        }

        void DisplayAll() {
            std::cout << "Displaying delay data: \n";
            std::for_each(port_ptr->fifo.begin(), port_ptr->fifo.end(), [] (std::pair<T,int> curr) {
                std::cout << "  " << curr.first << "\n";
            });
            std::cout << "\n";
        }

    private:
        std::shared_ptr<Storage<T>> port_ptr;
        std::string name_;
        int latency_;

        void Connect() {
            auto find_port = [name = name_] (std::shared_ptr<StorageInterface> p) {
                return p->GetName() ==name;
            };
            auto port = std::find_if(all_ports.begin(), all_ports.end(), find_port);
            if (port == all_ports.end()) {
                port_ptr = std::make_shared<Storage<T>>(name_);
                all_ports.push_back(port_ptr);
            } else {
                port_ptr = std::static_pointer_cast<Storage<T>>(*port);
            }
            
        }
        //std::vector<std::pair<T,int>> fifo;
        
};

#endif // DELAY_H

// TODO
//  Using Vector to store everything is bad...if size increases
//     all the pointers are invalidated