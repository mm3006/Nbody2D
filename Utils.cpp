#ifndef UTILS_CPP
#define UTILS_CPP
#include "CelestialBody.hpp"
#include "Moon.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "System.hpp"
#include <vector>
#include <fstream>
#include <sstream>

namespace Space{

std::vector<CelestialBody*> readFile(System& syst,std::string filename = "solarsystem.csv"){
	std::string data,line;
	std::vector<CelestialBody*>bodies;
	std::vector<std::string> row;
	std::ifstream file(filename);

    if(file.fail()){
		filename="solarsystem.csv";
     	std::ifstream file(filename);
    }
	std::cout << "Filename: " << filename <<"\n";


	if (file.is_open()){

		while(getline(file,line)){
			row.clear();
			std::stringstream s(line);

			while(getline(s, data, ',')){
					row.push_back(data);
			}
			if(row.at(0) == "Star"){
				bodies.push_back(static_cast<CelestialBody*>(new Space::Star(stod(row.at(1)),stod(row.at(2)),stod(row.at(3)),stod(row.at(4)),stod(row.at(5)),row.at(6))));
				syst.addOrbitingBody(bodies.at(bodies.size()-1));
			}else if (row.at(0) == "Planet") {
				Space::CelestialBody* starptr=nullptr;
				for(auto i: bodies){
					if(i->getName() == row.at(7)){
						starptr = i;
					}
				}
				
				bodies.push_back(new Space::Planet(stod(row.at(1)),stod(row.at(2)),stod(row.at(3)),stod(row.at(4)),stod(row.at(5)),row.at(6),starptr));
				syst.addOrbitingBody(bodies.at(bodies.size()-1));
			}else if (row.at(0) == "Moon"){

				Space::CelestialBody* planetptr=nullptr;
				for (auto i : bodies){
					if(i->getName() == row.at(7)){
						planetptr = i;
						
					}
				}
				if(planetptr==nullptr) //if there is no parent object for moons, treat moons as other planets
					planetptr=bodies.at(0);

				bodies.push_back(new Space::Moon(stod(row.at(1)),stod(row.at(2)),stod(row.at(3)),stod(row.at(4)),stod(row.at(5)),row.at(6),planetptr));
				syst.addOrbitingBody(bodies.at(bodies.size()-1));
			}
			
		}
	}

	return bodies;
}



}
#endif
