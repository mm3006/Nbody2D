#ifndef PLANET_HPP
#define PLANET_HPP

#include "CelestialBody.hpp"


namespace Space{
	class Planet: public virtual CelestialBody{

		public:
			Planet();
			Planet(double mass, double xPos, double yPos, double xVel, double yVel,std::string name,std::shared_ptr<ICelestialBody>obj);
				
		protected:
			std::shared_ptr<ICelestialBody> m_isOrbiting;

	};


}
#endif

