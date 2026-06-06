#ifndef MOON_HPP
#define MOON_HPP


#include "CelestialBody.hpp"


namespace Space{


	class Moon: public CelestialBody{
		public:
			Moon();
			Moon(double mass, double x, double y, double vx, double vy, std::string name,std::shared_ptr<ICelestialBody> obj);

			double getKinEnergy() const override final;
			double getxPos() const override final;
			double getyPos() const override final;
			double getxVel() const override final;
			double getyVel() const override final;
			

		protected:
			std::shared_ptr<ICelestialBody> m_isOrbiting;


	};


}
#endif
