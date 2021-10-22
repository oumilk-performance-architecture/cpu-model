#ifndef RESERVATION_H
#define RESERVATION_H

#include <utility>
#include <vector>

// Forward Class Declaration
class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;

class Reservation {
    public:
        Reservation(int size);

        bool CanInsert();
        int  NumFreeEntries();
        void Insert(UInstrPtr uinstr);

        UInstrPtr PickOldest(int port);
        UInstrPtr PickSpecialCase(int port);
        
        void RedoEntry(int entry);
        void DeallocEntry(int entry);

        //struct ResTable {
        //    UInstrPtr uinstr;
        //};

    private:
        std::vector<UInstrPtr> table_;
        int size_;
};

#endif // RESERVATION_H