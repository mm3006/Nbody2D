#ifndef MOON_CPP
#define MOON_CPP

#include "Moon.hpp"


namespace Space{

	Moon::Moon(double mass, double x, double y, double vx, double vy,std::string name,std::shared_ptr<CelestialBody> obj): CelestialBody(mass, x,y,vx,vy,name,obj){
		if(obj !=nullptr){
			setOrbiting(std::shared_ptr<CelestialBody>(obj));
		}
		m_FxAll =0;
		m_FyAll =0;

	};

	void Moon::PlugToOrbiting(std::shared_ptr<CelestialBody> obj) {
		obj->addOrbitingBody(shared_from_this());
	}

	double Moon::getKinEnergy() const{
		return 0.5*m_Mass*((m_xVel+m_isOrbiting->getxVel())*(m_xVel+m_isOrbiting->getxVel())+(m_yVel+m_isOrbiting->getyVel())*(m_yVel+m_isOrbiting->getyVel()));

	}


	double Moon::getxPos()const{
		return getOrbittingBody()->getxPos()+m_xPos;
	}
	
	double Moon::getyPos()const{
		return getOrbittingBody()->getyPos()+m_yPos;
	}

	double Moon::getxVel()const{
		return getOrbittingBody()->getxVel()+m_xVel;
	}
	
	double Moon::getyVel()const{
		return getOrbittingBody()->getyVel()+m_yVel;
	}

}





#endif

