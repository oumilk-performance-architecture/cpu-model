#ifndef ROB_H
#define ROB_H

#include <vector>
#include <delay.h>

class Rob {
    
    public:
        Rob();

        struct RobTable {
            bool finished = false;
            //int phys_reg = -1;
        };
        int  Dispatch();
        void CommitUInstr(int rob_entry);
        bool Commit(int num_uops);
        int  EntriesAvailable();

    private:
        // Note - should implement with an array of available retirement gaps
        //  1,2,3,4,8,12,16,etc.

        int IncrementPointer(int &rob_ptr);

        // Variables
        int cycle_;
        std::vector<RobTable> table_;
        int rob_head_;
        int rob_tail_;
        int num_dispatched_;

};
#endif