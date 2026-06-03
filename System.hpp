#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include <memory>
#include <vector>
#include "CelestialBody.hpp"
namespace Space{


	class System: virtual public CelestialBody{

        protected:
            std::vector<std::shared_ptr<CelestialBody>> orbiting;


	public:
            System();
            System(std::string,std::string,int,double,int,int,bool,bool);
            virtual void addOrbitingBody(std::shared_ptr<CelestialBody> );
            virtual void printObjects() const;
            virtual std::vector<std::shared_ptr<CelestialBody>> getOribttingBodies() const;
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
