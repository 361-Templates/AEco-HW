#ifndef ORGANISM
#define ORGANISM

#include "emp/Evolve/World.hpp"

class Organism {

    bool updated_this_step = false;

    public:

    Organism(const Organism &) = default;
    Organism() = default;

    void SetUpdated(bool _in) {updated_this_step = _in;}
    bool GetUpdated() {return updated_this_step;}

    void Process(emp::WorldPosition pos) {

    }
};

#endif