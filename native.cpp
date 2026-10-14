#include <iostream>

#include "Organism.h"
#include "emp/base/vector.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

#include "AEWorld.h"
#include "Config.h"

// This is the main function for the NATIVE version of this project.

int main(int argc, char* argv[])
{

  AEConfigBase config;

  bool success = config.Read("MySettings.cfg");
  if(!success) config.Write("MySettings.cfg");

  emp::Random random(config.SEED());
  AEWorld world(random, 100, 100);
  std::cout << "The seed is: " <<  config.SEED() << std::endl;


  for(int update=0; update<40; update++){
    std::cout << "Update: " << update << std::endl;
    world.Update();

  }

}