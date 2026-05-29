#ifndef PLANET_CPP
#define PLANET_CPP

#include "Planet.hpp"
#include "CelestialBody.hpp"
#include <cmath>

namespace Space{

	Planet::Planet(double Mass, double x, double y, double vx, double vy,std::string name,CelestialBody* obj): CelestialBody( Mass,  x,  y,  vx,  vy,  name, obj){
		if(obj !=nullptr){
			obj->addOrbitingBody(this);
			setOrbiting(obj);
		}
		m_FxAll =0;
		m_FyAll =0;
	};


	void Planet::addForces(){
		m_FxAll=0;
		m_FyAll=0;
		std::vector<CelestialBody*> bodies = getRelevantBodies();
		for(auto i : bodies){
			const double GMm = getMass()*i->getMass()*getG();
			double rx=getDistX(std::move(i));
			double ry=getDistY(std::move(i));
			double F = GMm/(rx*rx+ry*ry);
			if(rx<0)
				m_FxAll-=F*std::abs(rx)/std::sqrt(rx*rx+ry*ry);
			else
				m_FxAll+=F*std::abs(rx)/std::sqrt(rx*rx+ry*ry);

			if(ry<0)
				m_FyAll-=F*std::abs(ry)/std::sqrt(rx*rx+ry*ry);
			else
				m_FyAll+=F*std::abs(ry)/std::sqrt(rx*rx+ry*ry);

		}
	}
	

}


#endif
