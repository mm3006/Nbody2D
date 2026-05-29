#ifndef STAR_HPP
#define STAR_HPP

#include "CelestialBody.hpp"


namespace Space{



	class Star: virtual public CelestialBody{

		public:

			Star(double mass, double xPos, double yPos, double xVel, double yVel, std::string name);
			

	};

}



#endif
