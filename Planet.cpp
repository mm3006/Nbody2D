#ifndef PLANET_CPP
#define PLANET_CPP

#include "Planet.hpp"
#include "CelestialObject.hpp"


namespace Space{

	Planet::Planet(double Mass, double x, double y, double vx, double vy,std::string name,std::shared_ptr<CelestialObject>obj):  CelestialObject( Mass, x, y, vx, vy,  name), m_isOrbiting{obj} {
		
		if(obj !=nullptr){
			setOrbiting(std::shared_ptr<CelestialObject>(obj));
		}
		m_FxAll =0;
		m_FyAll =0;
	};

}


#endif
