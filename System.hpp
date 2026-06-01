#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include "CelestialBody.hpp"
namespace Space{


	class System: virtual public CelestialBody{

        protected:
            std::vector<CelestialBody*> orbiting;


	public:
            System();
            virtual ~System();
            virtual void addOrbitingBody(CelestialBody* );
            virtual void printObjects() const;
            virtual std::vector<CelestialBody* > getOribttingBodies() const;
            virtual void calculateRelevantBodiesAll() const;
            virtual void calculateRelevantBodies() const;
            virtual double calculatePotentialEnergy() const;
            virtual double calculateKineticEnergy() const;
            virtual void saveOutput(int body, double time,std::string name) const;
            virtual void evolve(int ,double , int ,int ,std::string ,bool );
            virtual void readFile(std::string);

	};


}
#endif
