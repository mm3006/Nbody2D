#ifndef PLANET_HPP
#define PLANET_HPP

#include "CelestialBody.hpp"


namespace Space{
	class Planet: virtual public CelestialBody{

		public:
			Planet(double mass, double xPos, double yPos, double xVel, double yVel,std::string name,CelestialBody* obj);
			virtual void addForces();
	};


}
#endif

