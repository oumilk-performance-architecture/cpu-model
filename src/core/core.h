#ifndef CORE_H
#define CORE_H

#include <func.h> // REMOVE

// Forward Declare Class
class Fetch;
class Decode;
class Allocate;
class Rename;
class Execute;
class Rob;
class FreeTable;
class RegisterAliasTable;


class Core {
    public:
        Core();
        
        void Process(int cycle);
    private:
        int cycle_;
        bool reset_;
        std::unique_ptr<Fetch>    fetch_;
        std::unique_ptr<Decode>   decode_;
        std::unique_ptr<Allocate> allocate_;
        std::unique_ptr<Execute>  execute_;

        std::shared_ptr<Rob>      rob_;
        std::shared_ptr<RegisterAliasTable> rat_;
        std::shared_ptr<RegisterAliasTable> srat_;
        std::shared_ptr<FreeTable> free_table_;
};

#endif // CORE_H