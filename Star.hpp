#ifndef STAR_HPP
#define STAR_HPP

#include "CelestialObject.hpp"

namespace Space{



	class Star: public CelestialObject{

		public:

			Star(double mass, double xPos, double yPos, double xVel, double yVel, std::string name);
			

	};

}



#endif
