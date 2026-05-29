#ifndef SYSTEM_CPP
#define SYSTEM_CPP

#include "System.hpp"
#include <cmath>

namespace Space{

    System::System(CelestialBody* star){
        orbiting.push_back(star);
    }
    System::System(){};
    void System::addOrbitingBody(CelestialBody*obj){
		orbiting.push_back(obj);
	}

    std::vector<CelestialBody*> System::getOribttingBodies() const {
        return orbiting;
    }


    double System::calculatePotentialEnergy() const{
        auto bodies = this->getOribttingBodies();
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

    double System::calculateKineticEnergy() const{
        auto bodies = this->getOribttingBodies();
        double Ek=0;
        for (auto i: bodies)
            Ek+=i->getKinEnergy();
        return Ek;
    }
}





#endif

