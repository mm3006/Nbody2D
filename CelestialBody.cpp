#ifndef CELESTIALBODY_CPP
#define CELESTIALBODY_CPP

#include "CelestialBody.hpp"
#include <cmath>

namespace Space{

	CelestialBody::CelestialBody(double Mass, double xPos, double yPos, double xVel, double yVel, std::string name): m_Mass{Mass}, m_xPos{xPos}, m_yPos{yPos}, m_xVel{xVel}, m_yVel{yVel}, m_name{name} {};

	CelestialBody::CelestialBody(): m_Mass{0}, m_xPos{0}, m_yPos{0}, m_xVel{0}, m_yVel{0}, m_name{""}{};

	//Getters
	double CelestialBody::getxPos() const { return m_xPos;}
	double CelestialBody::getyPos() const { return m_yPos;}
	double CelestialBody::getxVel() const { return m_xVel;}
	double CelestialBody::getyVel() const { return m_yVel;}
	double CelestialBody::getFx() const { return m_FxAll;}
	double CelestialBody::getFy() const { return m_FyAll;}
	double CelestialBody::getMass() const { return m_Mass;}
	double CelestialBody::getKinEnergy() const{

			return 0.5*(getxVel()*getxVel() + getyVel()*getyVel())*getMass();

	}
	std::string CelestialBody::getName() const { return m_name;}
	std::shared_ptr<ICelestialBody> CelestialBody::getOrbittingBody() const {return m_isOrbiting; }
	double CelestialBody::getG() const {return m_G;}

	std::vector<std::shared_ptr<ICelestialBody>> CelestialBody::getObjects() const{
		return m_orbitingBodies;
	}
	std::vector<std::shared_ptr<ICelestialBody> > CelestialBody::getRelevantBodies() const{
		return m_relevantBodies;
	}

	//setters

	void CelestialBody::setFx(double x){ m_FxAll =x;}
	void CelestialBody::setFy(double y){ m_FyAll =y;}
	void CelestialBody::setxPos(double x){ m_xPos = x;}
	void CelestialBody::setyPos(double y){ m_yPos = y;}
	void CelestialBody::setxVel(double vx){ m_xVel = vx;}
	void CelestialBody::setyVel(double vy){ m_yVel = vy;}

	void CelestialBody::setRelevantBodies() {

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

	void CelestialBody::setRelevantBodiesAll(std::shared_ptr<ICelestialBody> obj) {
		m_relevantBodies.push_back(obj);
	}

	void CelestialBody::PlugToOrbiting(std::shared_ptr<ICelestialBody> obj){
		obj->addOrbitingBody(shared_from_this());
	}

	//print operator for the objects
 	std::ostream& operator<<(std::ostream& os, const Space::ICelestialBody& obj){

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

	double CelestialBody::getDistX(std::shared_ptr<ICelestialBody> obj) const{
		return (obj->getxPos()-getxPos());
	}


	double CelestialBody::getDistX(std::shared_ptr<ICelestialBody> obj,double x) const{
		double x2 = obj->getxPos();
		return (x2-x);
	}

	double CelestialBody::getDistY(std::shared_ptr<ICelestialBody> obj)const{
		return (obj->getyPos()-getyPos());
	}

	double CelestialBody::getDistY(std::shared_ptr<ICelestialBody>  obj,double y)const{
		return (obj->getyPos()-y);
	}
	void CelestialBody::setOrbiting(std::shared_ptr<ICelestialBody> obj){
		m_isOrbiting=obj;
	}

	void CelestialBody::addOrbitingBody(std::shared_ptr<ICelestialBody>  obj){
		m_orbitingBodies.push_back(obj);
	}
	//evolution function

	void CelestialBody::addForces(){
		m_FxAll=0;
		m_FyAll=0;
		auto bodies = getRelevantBodies();


		for(auto i : bodies){
			const double GMm = getMass()*i->getMass()*getG();
			double rx=getDistX(i);
			double ry=getDistY(i);

			double F = GMm/(rx*rx+ry*ry);

			m_FxAll+=((rx>0)-(rx<0))*F*std::abs(rx)/std::sqrt(rx*rx+ry*ry);
			m_FyAll+=((ry>0)-(ry<0))*F*std::abs(ry)/std::sqrt(rx*rx+ry*ry);


		}
	}

	std::pair<double,double> CelestialBody::getAcc(double x, double y){
		double Fx=0;
		double Fy=0;
		std::vector<std::shared_ptr<ICelestialBody>> bodies = getRelevantBodies();
		for(auto i : bodies){
			const double GMm = getMass()*i->getMass()*getG();
			double rx=getDistX(i,x);
			double ry=getDistY(i,y);
			double F = GMm/(rx*rx+ry*ry);
			
			m_FxAll+=((rx>0)-(rx<0))*F*std::abs(rx)/std::sqrt(rx*rx+ry*ry);
			m_FyAll+=((ry>0)-(ry<0))*F*std::abs(ry)/std::sqrt(rx*rx+ry*ry);

		}
		return std::make_pair(Fx/getMass(),Fy/getMass());
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
