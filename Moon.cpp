#ifndef MOON_CPP
#define MOON_CPP

#include "Moon.hpp"


namespace Space{

	Moon::Moon(double mass, double x, double y, double vx, double vy,std::string name, CelestialBody* obj): CelestialBody(mass, x,y,vx,vy,name,obj){
		obj->addOrbitingBody(this);
		setOrbiting(obj);
		m_FxAll =0;
		m_FyAll =0;

	};

	double Moon::getKinEnergy() const{
		return 0.5*m_Mass*((m_xVel+isOrbiting->getxVel())*(m_xVel+isOrbiting->getxVel())+(m_yVel+isOrbiting->getyVel())*(m_yVel+isOrbiting->getyVel()));

	}

	double Moon::getDistX(CelestialBody* obj){
		double x1 = this->getxPos();
		double x2 = obj->getxPos();
		return (x2-x1);
	}

	double Moon::getDistY(CelestialBody* obj){
		double y1 = this->getyPos();
		double y2 = obj->getyPos();
		return (y2-y1);
	}


	double Moon::getxPos() const{
		return this->getOrbittingBody()->getxPos()+m_xPos;
	}
	
	double Moon::getyPos() const{
		return this->getOrbittingBody()->getyPos()+m_yPos;
	}

	double Moon::getxVel() const{
		return this->getOrbittingBody()->getxVel()+m_xVel;
	}
	
	double Moon::getyVel() const{
		return this->getOrbittingBody()->getyVel()+m_yVel;
	}

}





#endif

