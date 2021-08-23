#ifndef DELAY_H
#define DELAY_H

#include <utility>
#include <vector>
#include <iostream>

template <class T>
class Delay {
    T data;
    int cycle;

  public:
    void Send(T d, int c) {
        fifo.push_back(std::make_pair(d,c));
    }

    bool Receive(T& d, int c) {
        auto msg = std::find_if(fifo.begin(), fifo.end(), [c](std::pair<T,int> curr) {
            return curr.second == c;
        });
        if (msg != fifo.end()) {
            d = msg->first;
            fifo.erase(msg);
            return true;
        }
        return false;
    }

    void displayAll() {
        std::cout << "Displaying delay data: \n";
        std::for_each(fifo.begin(), fifo.end(), [] (std::pair<T,int> curr) {
            std::cout << "  " << curr.first << "\n";
        });
        std::cout << "\n";
    }

  private:
    std::vector<std::pair<T,int>> fifo;
    
};
#endif // DELAY_H