#ifndef CONFIG_H
#define CONFIG_H

#include "emp/config/config.hpp"

#include <limits>
#include <string>


EMP_BUILD_CONFIG(AEConfigBase,
    GROUP(MAIN, "Global Settings"),
    VALUE(SEED, int, 10, "What value should the random seed be? If seed <= 0, then it is randomly re-chosen."),
    VALUE(DATA_INT, int, 100, "How frequently, in updates, should data print?")
)
#endif