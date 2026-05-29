#ifndef UTILS_CPP
#define UTILS_CPP
#include "CelestialBody.hpp"
#include "Moon.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "System.hpp"
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

namespace Space{


void calculateRelevantBodies(std::vector<CelestialBody*> bodies){

	std::cout << "Calculating relevant bodies for each of the object (dimensionality reduction)...\n";
	for (auto i : bodies){
		if (i->getOrbittingBody() != nullptr)
			i->setRelevantBodies(i->getOrbittingBody());
	}
	std::cout << "Done!\n";

}

void calculateRelevantBodiesAll(std::vector<CelestialBody*> bodies){

	std::cout << "Calculating relevant bodies for each of the object (all interactions)...\n";
	for (unsigned int i = 0 ; i < bodies.size() ; ++i){
		for (unsigned int j = 0 ; j <  bodies.size() ; ++j){
			if(i!=j){
				bodies.at(i)->setRelevantBodiesAll(bodies.at(j));
			}
		}
	}
	std::cout << "Done!\n";

}

void calculateRelevantBodies(System* syst){
	auto x = syst->getOribttingBodies();
	std::cout << "Calculating relevant bodies for each of the object (dimensionality reduction)...\n";

	for (auto i : x){
		if (i->getOrbittingBody() != nullptr)
			i->setRelevantBodies(i->getOrbittingBody());
	}

	std::cout << "Done!\n";

}

void printObjects(std::vector<CelestialBody*> bodies){
	for (auto x : bodies)
		std::cout << *x << std::endl;
}

std::vector<CelestialBody*> readFile(System& syst,std::string filename = "solarsystem.csv"){
	std::string data,line;
	std::vector<CelestialBody*>bodies;
	std::vector<std::string> row;
	// std::vector<Space::Star*> stars;
	// std::vector<Space::Planet*> planets;
	// std::vector<Space::Moon*> moons;
	// Space::System* syst = new System();
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
			// for(int i = 0 ; i < row.size() ; ++i){
			// 	std::cout << i << " " << row.at(i) << "\n";
			// }
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


double calculatePotentialEnergy(std::vector<CelestialBody*> bodies){

	double Ep=0;
	for(unsigned int i = 0 ; i < bodies.size() ; ++i){
		for(unsigned int j = i+1 ; j < bodies.size() ; ++j){
			double x = bodies.at(i)->getDistX(bodies.at(j));
			double y = bodies.at(i)->getDistY(bodies.at(j));
			Ep +=  bodies.at(i)->getG()*bodies.at(i)->getMass()*bodies.at(j)->getMass()/std::sqrt(x*x+y*y);
		}

	}

	return Ep;
}


void saveOutput(System& syst, int body, double time,std::string name){
	
	auto obj = syst.getOribttingBodies();
	double base_posx=0;
	double base_posy=0;
	if (body ==-1){
		base_posx=0;
		base_posy=0;
	}
	else{
		base_posx=obj.at(body)->getxPos();
		base_posy=obj.at(body)->getyPos();
		
	}
	
	std::ofstream os;
	os.open(name,std::ios_base::app);
	os << time<< " ";
	for(auto i : obj){
		os << i->getxPos()-base_posx << " " << i->getyPos()-base_posy << " ";
		
	}
	double Ek =syst.calculateKineticEnergy();
	double Ep =syst.calculatePotentialEnergy();

	os << Ek<< " " << -Ep << " " << Ek-Ep << "\n";
	os.close();
}

void evolve(System*  syst,int N = 1000000,double dt = 36.5576, int saveStep =1000,int index = -1,std::string name ="coords.csv",bool doRK4=false){
	std::ofstream file(name);
	file.close();
	for(int iter = 0; iter < N ; ++iter){
	

		for (auto i : syst->getOribttingBodies()){
			i->addForces();
		}
	

		for (auto i : syst->getOribttingBodies()){

			if(doRK4){

				i->RK4(dt);

			}else{
				i->eulerStep(dt);
			}
		}
	

		if(iter%saveStep==0){
			saveOutput(*syst,index,iter*dt,name);
		}

	}

}



}
#endif
