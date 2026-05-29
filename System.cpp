#ifndef SYSTEM_CPP
#define SYSTEM_CPP

#include "System.hpp"
#include <cmath>
#include <fstream>
#include <sstream>
#include "Moon.hpp"
#include "Planet.hpp"
#include "Star.hpp"

namespace Space{


    System::System(){};

    void System::addOrbitingBody(CelestialBody*obj){
		orbiting.push_back(obj);
	}

    std::vector<CelestialBody*> System::getOribttingBodies() const {
        std::vector<CelestialBody*> x;
        for(auto i: orbiting){
            x.push_back(i);
        } 
        return x;
    }


    void System::printObjects() const{
        std::vector<CelestialBody* > bodies = getOribttingBodies();
        for (auto x : bodies)
            std::cout << *x << std::endl;
    }


    void System::calculateRelevantBodiesAll() const {
        auto bodies = getOribttingBodies();
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


    void System::calculateRelevantBodies() const {
        auto x = getOribttingBodies();
        std::cout << "Calculating relevant bodies for each of the object (dimensionality reduction)...\n";

        for (auto i : x){
            if (i->getOrbittingBody() != nullptr){
                i->setRelevantBodies(i->getOrbittingBody());
            }
        }

        std::cout << "Done!\n";

    }

    double System::calculatePotentialEnergy() const{
        auto bodies = getOribttingBodies();
        double Ep=0;
        for(unsigned int i = 0 ; i < bodies.size() ; ++i){
            for(unsigned int j = i+1 ; j < bodies.size() ; ++j){
                double x = bodies.at(i)->getDistX(bodies.at(j));
                double y = bodies.at(i)->getDistY(bodies.at(j));
                Ep +=  bodies.at(i)->getG()*bodies.at(i)->getMass()*bodies.at(j)->getMass()/std::sqrt(x*x+y*y);
            }

        }

        return -Ep;
    }

    double System::calculateKineticEnergy() const{
        auto bodies = getOribttingBodies();
        double Ek=0;
        for (auto i : bodies)
            Ek+=i->getKinEnergy();
        return Ek;
    }


void System::saveOutput(int body, double time,std::string name) const{
	
	auto obj = getOribttingBodies();
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
	double Ek =calculateKineticEnergy();
	double Ep =calculatePotentialEnergy();

	os << Ek<< " " << Ep << " " << Ek+Ep << "\n";
	os.close();
}


void System::evolve(int N = 1000000,double dt = 36.5576, int saveStep =1000,int index = -1,std::string name ="coords.csv",bool doRK4=false){
	std::ofstream file(name);
	file.close();
	for(int iter = 0; iter < N ; ++iter){
		for (auto i : getOribttingBodies()){
			i->addForces();
		}

		for (auto i : getOribttingBodies()){
			if(doRK4){
				i->RK4(dt);
			}else{
				i->eulerStep(dt);
			}
		}
		if(iter%saveStep==0){
			saveOutput(index,iter*dt,name);
		}
	}
}


void System::readFile(std::string filename = "solarsystem.csv"){
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
				addOrbitingBody(bodies.at(bodies.size()-1));
			}else if (row.at(0) == "Planet") {
				Space::CelestialBody* starptr=nullptr;
				for(auto i: bodies){
					if(i->getName() == row.at(7)){
						starptr = i;
					}
				}
				
				bodies.push_back(new Space::Planet(stod(row.at(1)),stod(row.at(2)),stod(row.at(3)),stod(row.at(4)),stod(row.at(5)),row.at(6),starptr));
				addOrbitingBody(bodies.at(bodies.size()-1));
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
				addOrbitingBody(bodies.at(bodies.size()-1));
			}
			
		}
	}

}

}





#endif

