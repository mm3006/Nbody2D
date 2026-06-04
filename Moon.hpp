#ifndef MOON_HPP
#define MOON_HPP


#include "CelestialObject.hpp"


namespace Space{


	class Moon: public CelestialObject{
		public:
			Moon(double mass, double x, double y, double vx, double vy, std::string name,std::shared_ptr<CelestialObject> obj);

			// void PlugToOrbiting(std::shared_ptr<CelestialObject> obj)override;
			double getKinEnergy() const override final;
			double getxPos() const override final;
			double getyPos() const override final;
			double getxVel() const override final;
			double getyVel() const override final;
			

		protected:
			std::shared_ptr<CelestialObject> m_isOrbiting;


	};


}
#endif
