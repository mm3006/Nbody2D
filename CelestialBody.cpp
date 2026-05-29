#ifndef CELESTIALBODY_CPP
#define CELESTIALBODY_CPP

#include "CelestialBody.hpp"
#include <cmath>
#include <ostream>

namespace Space{



	CelestialBody::CelestialBody(double Mass, double xPos, double yPos, double xVel, double yVel, std::string name,CelestialBody* isOrbiting): m_Mass{Mass}, m_xPos{xPos}, m_yPos{yPos}, m_xVel{xVel}, m_yVel{yVel}, m_name{name}, isOrbiting{isOrbiting} {};

	CelestialBody::CelestialBody(double Mass, double xPos, double yPos, double xVel, double yVel, std::string name): m_Mass{Mass}, m_xPos{xPos}, m_yPos{yPos}, m_xVel{xVel}, m_yVel{yVel}, m_name{name} {};

	CelestialBody::CelestialBody(): m_Mass{0}, m_xPos{0}, m_yPos{0}, m_xVel{0}, m_yVel{0}, m_name{0}{};
	//Getters
	double CelestialBody::getxPos() const { return m_xPos;}
	double CelestialBody::getyPos() const { return m_yPos;}
	double CelestialBody::getxVel() const { return m_xVel;}
	double CelestialBody::getyVel() const { return m_yVel;}
	double CelestialBody::getFx() const { return m_FxAll;}
	double CelestialBody::getFy() const { return m_FyAll;}
	double CelestialBody::getMass() const { return m_Mass;}
	double CelestialBody::getKinEnergy() const{

	if(isOrbiting !=nullptr)
		return 0.5*m_Mass*((m_xVel+isOrbiting->getxVel())*(m_xVel+isOrbiting->getxVel())+(m_yVel+isOrbiting->getyVel())*(m_yVel+isOrbiting->getyVel()));
	else
		return 0.5*(getxVel()*getxVel() + getyVel()*getyVel())*getMass();

	}
	std::string CelestialBody::getName() const { return m_name;}
	CelestialBody* CelestialBody::getOrbittingBody() const {return isOrbiting; }
	double CelestialBody::getG() const {return m_G;}
	std::vector<CelestialBody*> CelestialBody::getObjects() const{
		return orbitingBodies;
	}
	std::vector<CelestialBody*> CelestialBody::getRelevantBodies() const{
		return m_relevantBodies;
	}

	//setters
	void CelestialBody::setFx(double x){ m_FxAll =x;}
	void CelestialBody::setFy(double y){ m_FyAll =y;}
	void CelestialBody::setxPos(double x){ m_xPos = x;}
	void CelestialBody::setyPos(double y){ m_yPos = y;}
	void CelestialBody::setxVel(double vx){ m_xVel = vx;}
	void CelestialBody::setyVel(double vy){ m_yVel = vy;}

	void CelestialBody::setRelevantBodies(CelestialBody* obj) {
		for(auto i: obj->getObjects()){
			if(i->getName() != this->getName()){
				m_relevantBodies.push_back(i);
			}
		}
		if(this->getOrbittingBody() !=nullptr){
			m_relevantBodies.push_back(this->getOrbittingBody());
		}
	}


	void CelestialBody::setRelevantBodiesAll(CelestialBody* obj) {
		m_relevantBodies.push_back(obj);
	}
	//print operator for the objects
 	std::ostream& operator<<(std::ostream& os, const CelestialBody& obj){

		std::vector<CelestialBody*> orbiting =  obj.getObjects();
		
		if(obj.getOrbittingBody() != nullptr){

			os <<  obj.getName() << ":\n=============================\n"   << 
			"\nX position: " << obj.getxPos() << "\nY position: " << obj.getyPos() << "\nX velocity: " << obj.getxVel() << "\nY velocity: " << obj.getyVel() << "\nMass: " << obj.getMass()<< "\nOrbiting around: "<< obj.getOrbittingBody()->getName()<<"\nOrbiting bodies: " <<  
			"\n-----------------------------------------\n";


			for (auto i : orbiting)
				os <<"\n    "<< i->getName() << "\n";
			os << "\n-----------------------------------------\n";

			os << "\nRelevant bodies:\n";
			for (auto i : obj.getRelevantBodies())
				os <<"\n    "<< i->getName() << "\n";
		}else {
					os <<  obj.getName() << ":\n=============================\n"   << 
			"\nX position: " << obj.getxPos() << "\nY position: " << obj.getyPos() << "\nX velocity: " << obj.getxVel() << "\nY velocity: " << obj.getyVel() << "\nMass: " << obj.getMass()<< "\nOrbiting around: "<< "Not orbiting around anything" <<"\nOrbiting bodies: " <<  
			"\n-----------------------------------------\n";


			for (auto i : orbiting)
				os <<"\n    "<< i->getName() << "\n";
			os << "\n-----------------------------------------\n";


		}
		return os;
	}

	double CelestialBody::getDistX(CelestialBody* obj){
		double x1 = this->getxPos();
		double x2 = obj->getxPos();
		return (x2-x1);
	}

		double CelestialBody::getDistY(CelestialBody* obj){

		double y1 = this->getyPos();
		double y2 = obj->getyPos();
		return (y2-y1);
	}
	void CelestialBody::setOrbiting(CelestialBody* obj){
		isOrbiting=obj;
	}

	void CelestialBody::addOrbitingBody(CelestialBody*obj){
		orbitingBodies.push_back(obj);
	}
	//evolution function

	void CelestialBody::addForces(){
		m_FxAll=0;
		m_FyAll=0;
		std::vector<CelestialBody*> bodies = getRelevantBodies();
		for(auto i : bodies){
			const double GMm = this->getMass()*i->getMass()*this->getG();
			double rx=getDistX(i);
			double ry=getDistY(i);
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

	//euler method
	void CelestialBody::eulerStep(double dt){

		double ax = m_FxAll/m_Mass;
		double ay = m_FyAll/m_Mass;
		double vx = m_xVel + ax*dt;
		double vy =	m_yVel + ay*dt;
		double dx = m_xPos + vx*dt;
		double dy = m_yPos + vy*dt;

		setxPos(dx);
		setyPos(dy);
		setxVel(vx);
		setyVel(vy);
		setFx(0);
		setFy(0);

	}


	void CelestialBody::RK4(double dt){

		double kvx[4],kvy[4],krx[4],kry[4];
		
		double ax= m_FxAll/m_Mass;
		double ay =m_FyAll/m_Mass;
		// std::cout << ax << " " << ay << std::endl;
		kvx[0]=ax;
		kvy[0]=ay;
		krx[0]=m_xVel;
		kry[0]=m_yVel;

		kvx[1]=ax; //assuming constant acceleration for the future step to reduce the number of computations
		kvy[1]=ay; //this is wrong
		krx[1]=m_xVel+kvx[0]*dt/2.0;
		kry[1]=m_yVel+kvy[0]*dt/2.0;

		kvx[2]=ax;
		kvy[2]=ay;
		krx[2]=m_xVel+kvx[1]*dt/2.0;
		kry[2]=m_yVel+kvy[1]*dt/2.0;


		kvx[3]=ax;
		kvy[3]=ay;
		krx[3]=m_xVel+kvx[2]*dt;
		kry[3]=m_yVel+kvy[2]*dt;

		setxPos(m_xPos+dt/6.0*(krx[0]+2*krx[1]+2*krx[2]+krx[3]));
		setyPos(m_yPos+dt/6.0*(kry[0]+2*kry[1]+2*kry[2]+kry[3]));
		setxVel(m_xVel+dt/6.0*(kvx[0]+2*kvx[1]+2*kvx[2]+kvx[3]));
		setyVel(m_yVel+dt/6.0*(kvy[0]+2*kvy[1]+2*kvy[2]+kvy[3]));
		// std::cout << dt/6.0*(krx[0]+2*krx[1]+2*krx[2]+krx[3]) << std::endl;
		setFx(0);
		setFy(0);

	}


}





#endif
