#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include "CelestialBody.hpp"
namespace Space{


	class System: virtual public CelestialBody{

        protected:
            std::vector<CelestialBody*> orbiting;

		public:
			System(CelestialBody* star);
            System();
            void addOrbitingBody(CelestialBody*);
            virtual std::vector<CelestialBody*> getOribttingBodies() const;
            virtual double calculatePotentialEnergy() const;
            virtual double calculateKineticEnergy() const;
	};


}
#endif
