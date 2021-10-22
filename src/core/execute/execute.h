#ifndef EXECUTE_H
#define EXECUTE_H

#include <utility>
#include <delay.h>

// Forward Class Declaration
class UInstr;
using UInstrPtr = std::shared_ptr<UInstr>;

class Execute {
    public:
        Execute();

        void Process(int cycle, bool reset);
        void InsertRS();

    private:
        int cycle_;
        DelayPtr<UInstrPtr> rename_to_reservation_wp;

};

#endif // EXECUTE_H