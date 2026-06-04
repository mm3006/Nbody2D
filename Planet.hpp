#ifndef PLANET_HPP
#define PLANET_HPP

#include "CelestialObject.hpp"


namespace Space{
	class Planet: public virtual CelestialObject{

		public:
			Planet(double mass, double xPos, double yPos, double xVel, double yVel,std::string name,std::shared_ptr<CelestialObject>obj);
				
		protected:
			std::shared_ptr<CelestialObject> m_isOrbiting;

	};


}
#endif

