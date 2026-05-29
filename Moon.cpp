#ifndef MOON_CPP
#define MOON_CPP

#include "Moon.hpp"


namespace Space{

	Moon::Moon(double mass, double x, double y, double vx, double vy,std::string name,CelestialBody*  obj): CelestialBody(mass, x,y,vx,vy,name,obj){
		if(obj !=nullptr){
			obj->addOrbitingBody(this);
			setOrbiting(obj);
		}
		m_FxAll =0;
		m_FyAll =0;

	};

	double Moon::getKinEnergy() const{
		return 0.5*m_Mass*((m_xVel+m_isOrbiting->getxVel())*(m_xVel+m_isOrbiting->getxVel())+(m_yVel+m_isOrbiting->getyVel())*(m_yVel+m_isOrbiting->getyVel()));

	}

	double Moon::getDistX(CelestialBody* obj){
		double x1 = getxPos();
		double x2 = obj->getxPos();
		return (x2-x1);
	}

	double Moon::getDistY(CelestialBody* obj){
		double y1 = getyPos();
		double y2 = obj->getyPos();
		return (y2-y1);
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

