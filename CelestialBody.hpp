#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
namespace Space{


class CelestialBody: public std::enable_shared_from_this<CelestialBody>{

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
		std::vector<std::shared_ptr<CelestialBody>> m_orbitingBodies;
		std::shared_ptr<CelestialBody> m_isOrbiting=nullptr;
		std::vector<std::shared_ptr<CelestialBody>> m_relevantBodies;


	public:
	
		//Constructor
		CelestialBody(double Mass, double xPos, double yPos, double xVel,double yVel,std::string name,std::shared_ptr<CelestialBody>isOrbiting);
		CelestialBody(double Mass, double xPos, double yPos, double xVel,double yVel,std::string name);
		CelestialBody();
		// virtual ~CelestialBody();
		//getters
		virtual double getMass() const;
		virtual double getxPos() const;
		virtual double getyPos() const;
		virtual double getxVel() const;
		virtual double getyVel() const;
		virtual double getFx() const;
		virtual double getFy() const;
		virtual double getKinEnergy() const;
		virtual double getG() const;
		virtual double getDistX(std::shared_ptr<CelestialBody> obj);
		virtual double getDistY(std::shared_ptr<CelestialBody> obj);
		virtual double getDistX(std::shared_ptr<CelestialBody> obj,double);
		virtual double getDistY(std::shared_ptr<CelestialBody> obj,double);
		virtual void PlugToOrbiting(std::shared_ptr<CelestialBody> obj);
		virtual std::string getName() const;
		virtual std::vector<std::shared_ptr<CelestialBody>> getObjects() const;
		virtual std::vector<std::shared_ptr<CelestialBody>> getRelevantBodies() const;
		virtual std::shared_ptr<CelestialBody> getOrbittingBody()const;

		virtual void addForces();
		virtual std::pair<double,double>  getAcc(double, double);
		virtual void RK4(double dt);

		//setters

		virtual void setxPos(double x);
		virtual void setyPos(double y);
		virtual void setxVel(double vx);
		virtual void setyVel(double vy);
		virtual void setFx (double fx);
		virtual void setFy (double fy);
		virtual void addOrbitingBody(std::shared_ptr<CelestialBody>);
		virtual void setOrbiting(std::shared_ptr<CelestialBody>);
		virtual void setRelevantBodies();
		virtual void eulerStep(double dt);
		virtual void setRelevantBodiesAll(std::shared_ptr<CelestialBody> obj);



};
	std::ostream& operator<<(std::ostream& os, const CelestialBody& obj) ;


}
#endif
