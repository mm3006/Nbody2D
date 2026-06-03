#ifndef PLANET_CPP
#define PLANET_CPP

#include "Planet.hpp"
#include "CelestialBody.hpp"


namespace Space{

	Planet::Planet(double Mass, double x, double y, double vx, double vy,std::string name,std::shared_ptr<CelestialBody>obj): CelestialBody( Mass,  x,  y,  vx,  vy,  name, obj){
		if(obj !=nullptr){
			setOrbiting(std::shared_ptr<CelestialBody>(obj));
		}
		m_FxAll =0;
		m_FyAll =0;
	};
	void Planet::PlugToOrbiting(std::shared_ptr<CelestialBody> obj){
		if(obj !=nullptr){
			obj->addOrbitingBody(shared_from_this());
		}
	}

}


#endif
