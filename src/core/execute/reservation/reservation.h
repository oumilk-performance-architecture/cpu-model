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

        // Insertion Related
        bool CanInsert();
        int  NumFreeEntries();
        void Insert(UInstrPtr uinstr);

        // Pick Related
        UInstrPtr PickOldest(int port);
        UInstrPtr PickSpecialCase(int port);

        // Reissue Related
        void RedoEntry(int entry);
        
        // Deallocation Related
        void DeallocEntry(int entry);
        void SetDstReady();

        //struct ResTable {
        //    UInstrPtr uinstr;
        //};

    private:
        std::vector<UInstrPtr> table_;
        int size_;
};

#endif // RESERVATION_H