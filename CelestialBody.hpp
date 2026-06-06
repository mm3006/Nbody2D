#ifndef CelestialBody_HPP
#define CelestialBody_HPP

#include <ostream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "ICelestialBody.hpp"

namespace Space{


class CelestialBody:public ICelestialBody, public std::enable_shared_from_this<CelestialBody>{

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
		std::vector<std::shared_ptr<ICelestialBody>> m_orbitingBodies;
		std::shared_ptr<ICelestialBody> m_isOrbiting=nullptr;
		std::vector<std::shared_ptr<ICelestialBody>> m_relevantBodies;


	public:
	
		CelestialBody(double Mass, double xPos, double yPos, double xVel,double yVel,std::string name);
		CelestialBody();
		//getters
		virtual double getMass() const override;
		virtual double getxPos() const override;
		virtual double getyPos() const override;
		virtual double getxVel() const override;
		virtual double getyVel() const override;
		virtual double getFx() const override;
		virtual double getFy() const override;
		virtual double getKinEnergy() const override;
		virtual double getG() const override;
		virtual double getDistX(std::shared_ptr<ICelestialBody> obj) const override;
		virtual double getDistY(std::shared_ptr<ICelestialBody> obj) const override;
		virtual double getDistX(std::shared_ptr<ICelestialBody> obj,double) const override;
		virtual double getDistY(std::shared_ptr<ICelestialBody> obj,double) const override;
		virtual void PlugToOrbiting(std::shared_ptr<ICelestialBody> obj) override;
		virtual std::string getName() const override;
		virtual std::vector<std::shared_ptr<ICelestialBody>> getObjects() const override;
		virtual std::vector<std::shared_ptr<ICelestialBody>> getRelevantBodies() const override;
        virtual std::shared_ptr<ICelestialBody> getOrbittingBody() const override;

		//setters

		virtual void setxPos(double x) override;
		virtual void setyPos(double y) override;
		virtual void setxVel(double vx) override;
		virtual void setyVel(double vy) override;
		virtual void setFx (double fx) override;
		virtual void setFy (double fy) override;
		virtual void addOrbitingBody(std::shared_ptr<ICelestialBody>) override ;
		virtual void setOrbiting(std::shared_ptr<ICelestialBody>) override ;
		virtual void setRelevantBodies() override;
		virtual void eulerStep(double dt) override;
		virtual void setRelevantBodiesAll(std::shared_ptr<ICelestialBody> obj) override ;

		virtual void addForces() override;
		virtual std::pair<double,double>  getAcc(double, double) override;
		virtual void RK4(double dt) override;


};
	std::ostream& operator<<(std::ostream& os, const ICelestialBody& obj) ;


}
#endif
