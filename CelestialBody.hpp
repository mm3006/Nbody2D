#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include <iostream>
#include <vector>
namespace Space{


class CelestialBody{

	protected:
		static constexpr double m_G = 6.674e-11;
		const double m_Mass;
		double m_xPos;
		double m_yPos;
		double m_xVel;
		double m_yVel;
		double m_FxAll;
		double m_FyAll;
		const std::string m_name;
		std::vector<CelestialBody*> orbitingBodies;
		CelestialBody* isOrbiting;
		std::vector<CelestialBody*> m_relevantBodies;


	public:
	
		//Constructor
		CelestialBody(double Mass, double xPos, double yPos, double xVel,double yVel,std::string name,CelestialBody* isOrbiting);
		CelestialBody(double Mass, double xPos, double yPos, double xVel,double yVel,std::string name);
		CelestialBody();
		//getters
		double getMass() const;
		virtual double getxPos() const;
		virtual double getyPos() const;
		virtual double getxVel() const;
		virtual double getyVel() const;
		double getFx() const;
		double getFy() const;
		virtual double getKinEnergy() const;
		double getG() const;
		virtual double getDistX(CelestialBody* obj);
		virtual double getDistY(CelestialBody* obj);
		std::string getName() const;
		std::vector<CelestialBody*> getObjects() const;
		std::vector<CelestialBody*> getRelevantBodies() const;
		CelestialBody* getOrbittingBody() const;

		virtual void addForces();
		virtual void RK4(double dt);

		//setters
		void setxPos(double x);
		void setyPos(double y);
		void setxVel(double vx);
		void setyVel(double vy);
		void setFx (double fx);
		void setFy (double fy);
		void addOrbitingBody(CelestialBody*);
		void setOrbiting(CelestialBody*);
		void setRelevantBodies(CelestialBody*);
		void eulerStep(double dt);
		void setRelevantBodiesAll(CelestialBody* obj);



};
	std::ostream& operator<<(std::ostream& os, const CelestialBody& obj) ;


}
#endif
