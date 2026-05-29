#ifndef STAR_CPP
#define STAR_CPP

#include "Star.hpp"
#include "CelestialBody.hpp"

namespace Space{


	Star::Star(double Mass, double xPos, double yPos, double xVel, double yVel, std::string name): CelestialBody(Mass,xPos,yPos,xVel,yVel,name) {

	};
	

}


#endif