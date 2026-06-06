#ifndef STAR_HPP
#define STAR_HPP

#include "CelestialBody.hpp"

namespace Space{



	class Star: public CelestialBody{

		public:
			Star();
			Star(double mass, double xPos, double yPos, double xVel, double yVel, std::string name);
			

	};


	
}



#endif
