#ifndef AEWORLD
#define AEWORLD

#include "Empirical/include/emp/base/Ptr.hpp"
#include "emp/Evolve/World.hpp"
#include "Organism.h"
#include "emp/Evolve/World_structure.hpp"

class AEWorld : public emp::World<Organism> {
    public:
    AEWorld(emp::Random &_random, int _width, int _height) : emp::World<Organism>(_random) {
        SetPopStruct_Grid(_width, _height);
        Resize(_width, _height);
        AddOrgAt(emp::NewPtr<Organism>(), 2);

    }

    bool MoveOrganism(emp::WorldPosition from_pos, emp::WorldPosition to_pos) {
        size_t from_id = from_pos.GetIndex();
        size_t to_id = to_pos.GetIndex();

        if (!IsOccupied(from_id)) { // Nothing was there...
            return false;
        }

        pop[to_id] = pop[from_id];
        pop[from_id] = nullptr;
        return true;
    }

    void Update() {
        emp::World<Organism>::Update();

        // Make sure no organism gets to go twice if they move to an unprocessed location
        for (size_t i = 0; i< GetSize(); i++) {
            if (IsOccupied(i)) {
                pop[i]->SetUpdated(false);
            }
        }

        emp::vector<size_t> schedule = emp::GetPermutation(GetRandom(), GetSize());
        for(int i : schedule) {
            if(!IsOccupied(i)) {continue;}
            if(pop[i]->GetUpdated()) {continue;} // they already got to go at a previous location

            pop[i]->SetUpdated(true);
            pop[i]->Process(i);
            
        }


    }
};

#endif