#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include "CelestialBody.hpp"
#include "System.hpp"

namespace Space{
std::vector<CelestialBody*> DeclareObjectsSolarSystem();
std::vector<CelestialBody*> readFile(System& syst,std::string s="solarsystem.csv");

// void evolve(System* syst,int N = 1000000,double dt = 36.5576, int saveStep =1000,int index=-1,std::string name ="coords.csv",bool doRK4=false);
// void saveOutput(System* syst, CelestialBody* body, double time,std::string name);
}
#endif