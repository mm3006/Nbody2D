#ifndef CELESTIALOBJECT_CPP
#define CELESTIALOBJECT_CPP

#include "CelestialObject.hpp"
#include <ostream>
#include <cmath>

namespace Space{

	CelestialObject::CelestialObject(double Mass, double xPos, double yPos, double xVel, double yVel, std::string name): m_Mass{Mass}, m_xPos{xPos}, m_yPos{yPos}, m_xVel{xVel}, m_yVel{yVel}, m_name{name} {};

	CelestialObject::CelestialObject(): m_Mass{0}, m_xPos{0}, m_yPos{0}, m_xVel{0}, m_yVel{0}, m_name{""}{};

	//Getters
	double CelestialObject::getxPos() const { return m_xPos;}
	double CelestialObject::getyPos() const { return m_yPos;}
	double CelestialObject::getxVel() const { return m_xVel;}
	double CelestialObject::getyVel() const { return m_yVel;}
	double CelestialObject::getFx() const { return m_FxAll;}
	double CelestialObject::getFy() const { return m_FyAll;}
	double CelestialObject::getMass() const { return m_Mass;}
	double CelestialObject::getKinEnergy() const{
		if(m_isOrbiting !=nullptr)
			return 0.5*m_Mass*((m_xVel+m_isOrbiting->getxVel())*(m_xVel+m_isOrbiting->getxVel())+(m_yVel+m_isOrbiting->getyVel())*(m_yVel+m_isOrbiting->getyVel()));
		else
			return 0.5*(getxVel()*getxVel() + getyVel()*getyVel())*getMass();

	}
	std::string CelestialObject::getName() const { return m_name;}
	std::shared_ptr<CelestialBody> CelestialObject::getOrbittingBody() const {return m_isOrbiting; }
	double CelestialObject::getG() const {return m_G;}

	std::vector<std::shared_ptr<CelestialBody>> CelestialObject::getObjects() const{
		return m_orbitingBodies;
	}
	std::vector<std::shared_ptr<CelestialBody> > CelestialObject::getRelevantBodies() const{
		return m_relevantBodies;
	}

	//setters

	void CelestialObject::setFx(double x){ m_FxAll =x;}
	void CelestialObject::setFy(double y){ m_FyAll =y;}
	void CelestialObject::setxPos(double x){ m_xPos = x;}
	void CelestialObject::setyPos(double y){ m_yPos = y;}
	void CelestialObject::setxVel(double vx){ m_xVel = vx;}
	void CelestialObject::setyVel(double vy){ m_yVel = vy;}

	void CelestialObject::setRelevantBodies() {

		for(auto i: getObjects()){
			if(i->getName() != getName()){
				m_relevantBodies.push_back(i);
			}
		}

		if(getOrbittingBody() !=nullptr){
			m_relevantBodies.push_back(getOrbittingBody());
			for(auto i : getOrbittingBody()->getObjects()){
				if(i->getName() != getName()){
					m_relevantBodies.push_back(i);
				}
			}
	}
	}

	void CelestialObject::setRelevantBodiesAll(std::shared_ptr<CelestialBody> obj) {
		m_relevantBodies.push_back(obj);
	}

	void CelestialObject::PlugToOrbiting(std::shared_ptr<CelestialBody> obj){
		obj->addOrbitingBody(shared_from_this());
	}

	//print operator for the objects
 	std::ostream& operator<<(std::ostream& os, const Space::CelestialBody& obj){

		auto orbiting =  obj.getObjects();

		if(obj.getOrbittingBody() != nullptr){

			os <<  obj.getName() << ":\n=============================\n"   << 
			"\nX position: " << obj.getxPos() << "\nY position: " << obj.getyPos() << "\nX velocity: " << obj.getxVel() << "\nY velocity: " << obj.getyVel() << "\nMass: " << obj.getMass()<< "\nOrbiting around: "<< obj.getOrbittingBody()->getName()<<"\nOrbiting bodies: " <<  
			"\n-----------------------------------------\n";


			for (unsigned int i = 0 ; i < orbiting.size() ; ++i){
				os <<"\n    "<< orbiting.at(i)->getName() << "\n";
			}
			os << "\n-----------------------------------------\n";

			os << "\nRelevant bodies:\n";
			for (auto i : obj.getRelevantBodies())
				os <<"\n    "<< i->getName() << "\n";
		}else {
					os <<  obj.getName() << ":\n=============================\n"   << 
			"\nX position: " << obj.getxPos() << "\nY position: " << obj.getyPos() << "\nX velocity: " << obj.getxVel() << "\nY velocity: " << obj.getyVel() << "\nMass: " << obj.getMass()<< "\nOrbiting around: "<< "Not orbiting around anything" <<"\nOrbiting bodies: " <<  
			"\n-----------------------------------------\n";

			for (unsigned int i = 0 ; i < orbiting.size() ; ++i){

				os <<"\n    "<< orbiting.at(i)->getName() << "\n";
			}
			os << "\n-----------------------------------------\n";

		}
		return os;
	}

	double CelestialObject::getDistX(std::shared_ptr<CelestialBody> obj) const{
		return (obj->getxPos()-getxPos());
	}


	double CelestialObject::getDistX(std::shared_ptr<CelestialBody> obj,double x) const{
		double x2 = obj->getxPos();
		return (x2-x);
	}

	double CelestialObject::getDistY(std::shared_ptr<CelestialBody> obj)const{
		return (obj->getyPos()-getyPos());
	}

	double CelestialObject::getDistY(std::shared_ptr<CelestialBody>  obj,double y)const{
		return (obj->getyPos()-y);
	}
	void CelestialObject::setOrbiting(std::shared_ptr<CelestialBody> obj){
		m_isOrbiting=obj;
	}

	void CelestialObject::addOrbitingBody(std::shared_ptr<CelestialBody>  obj){
		m_orbitingBodies.push_back(obj);
	}
	//evolution function

	void CelestialObject::addForces(){
		m_FxAll=0;
		m_FyAll=0;
		auto bodies = getRelevantBodies();


		for(auto i : bodies){
			const double GMm = getMass()*i->getMass()*getG();
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

	std::pair<double,double> CelestialObject::getAcc(double x, double y){
		double Fx=0;
		double Fy=0;
		std::vector<std::shared_ptr<CelestialBody>> bodies = getRelevantBodies();
		for(auto i : bodies){
			const double GMm = getMass()*i->getMass()*getG();
			double rx=getDistX(i,x);
			double ry=getDistY(i,y);
			double F = GMm/(rx*rx+ry*ry);
			if(rx<0)
				Fx-=F*std::abs(rx)/std::sqrt(rx*rx+ry*ry);
			else
				Fx+=F*std::abs(rx)/std::sqrt(rx*rx+ry*ry);

			if(ry<0)
				Fy-=F*std::abs(ry)/std::sqrt(rx*rx+ry*ry);
			else
				Fy+=F*std::abs(ry)/std::sqrt(rx*rx+ry*ry);

		}
		return std::make_pair(Fx/getMass(),Fy/getMass());
	}



	//euler method
	void CelestialObject::eulerStep(double dt){

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


	void CelestialObject::RK4(double dt){

		double kvx[4],kvy[4],krx[4],kry[4];

		double x = getxPos();
		double y = getyPos();


		krx[0]=m_xVel;
		kry[0]=m_yVel;
		kvx[0]=getAcc(x,y).first;
		kvy[0]=getAcc(x,y).second;


		krx[1]=m_xVel+kvx[0]*dt/2.0;
		kry[1]=m_yVel+kvy[0]*dt/2.0;
		kvx[1]=getAcc(x+krx[0]*dt*0.5,y+kry[0]*dt*0.5).first; 
		kvy[1]=getAcc(x+krx[0]*dt*0.5,y+kry[0]*dt*0.5).second;

		kvx[2]=getAcc(x+krx[1]*dt*0.5,y+kry[1]*dt*0.5).first;
		kvy[2]=getAcc(x+krx[1]*dt*0.5,y+kry[1]*dt*0.5).second;
		krx[2]=m_xVel+kvx[1]*dt/2.0;
		kry[2]=m_yVel+kvy[1]*dt/2.0;


		kvx[3]=getAcc(x+krx[2]*dt,y+kry[2]*dt).first;
		kvy[3]=getAcc(x+krx[2]*dt,y+kry[2]*dt).second;
		krx[3]=m_xVel+kvx[2]*dt;
		kry[3]=m_yVel+kvy[2]*dt;

		setxPos(m_xPos+dt/6.0*(krx[0]+2*krx[1]+2*krx[2]+krx[3]));
		setyPos(m_yPos+dt/6.0*(kry[0]+2*kry[1]+2*kry[2]+kry[3]));
		setxVel(m_xVel+dt/6.0*(kvx[0]+2*kvx[1]+2*kvx[2]+kvx[3]));
		setyVel(m_yVel+dt/6.0*(kvy[0]+2*kvy[1]+2*kvy[2]+kvy[3]));

		setFx(0);
		setFy(0);

	}


}





#endif
