#ifndef MOON_HPP
#define MOON_HPP


#include "CelestialBody.hpp"


namespace Space{


	class Moon: virtual public CelestialBody{

		public:
			Moon(double mass, double x, double y, double vx, double vy, std::string name,CelestialBody*  obj);

			virtual double getKinEnergy() const;
			virtual double getDistX(CelestialBody* obj);
			virtual double getDistY(CelestialBody* obj);
			virtual double getxPos() const;
			virtual double getyPos() const;
			virtual double getxVel() const;
			virtual double getyVel() const;


	};


}
#endif
