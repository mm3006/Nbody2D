#ifndef ICELESTIALBODY_H
#define ICELESTIALBODY_H

#include <memory>
#include <vector>
namespace Space{


class ICelestialBody{
	public:
		//getters
		virtual double getMass() const = 0;
		virtual double getxPos() const = 0;
		virtual double getyPos() const = 0;
		virtual double getxVel() const = 0;
		virtual double getyVel() const = 0;
		virtual double getFx() const = 0;
		virtual double getFy() const = 0;
		virtual double getKinEnergy() const = 0;
		virtual double getG() const = 0;
		virtual double getDistX(std::shared_ptr<ICelestialBody> obj) const= 0;
		virtual double getDistY(std::shared_ptr<ICelestialBody> obj) const = 0;
		virtual double getDistX(std::shared_ptr<ICelestialBody> obj,double) const = 0;
		virtual double getDistY(std::shared_ptr<ICelestialBody> obj,double) const = 0;
		virtual std::string getName() const = 0;
		virtual std::vector<std::shared_ptr<ICelestialBody>> getObjects() const = 0;
		virtual std::vector<std::shared_ptr<ICelestialBody>> getRelevantBodies() const = 0;
		virtual std::shared_ptr<ICelestialBody> getOrbittingBody()const = 0;

		//setters

		virtual void setxPos(double x) = 0;
		virtual void setyPos(double y) = 0;
		virtual void setxVel(double vx) = 0;
		virtual void setyVel(double vy) = 0;
		virtual void setFx (double fx) = 0;
		virtual void setFy (double fy) = 0;
		virtual void addOrbitingBody(std::shared_ptr<ICelestialBody>) = 0;
		virtual void setOrbiting(std::shared_ptr<ICelestialBody>) = 0;
		virtual void setRelevantBodies() = 0;
		virtual void eulerStep(double dt) = 0;
		virtual void setRelevantBodiesAll(std::shared_ptr<ICelestialBody> obj) = 0;

		virtual void PlugToOrbiting(std::shared_ptr<ICelestialBody> obj)=0;
		virtual void addForces() = 0;
		virtual std::pair<double,double>  getAcc(double, double) = 0;
		virtual void RK4(double dt) = 0;

	};

}
#endif
