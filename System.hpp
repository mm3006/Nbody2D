#ifndef SYSTEM_HPP
#define SYSTEM_HPP
// #include "ICelestialBody.hpp"

#include "Factory.hpp"

namespace Space{


	class System{

        protected:
            std::vector<std::shared_ptr<ICelestialBody>> orbiting;

	    public:
            System();
            System(std::string,std::string,int,double,int,int,bool,bool);
            void addOrbitingBody(std::shared_ptr<ICelestialBody> );
            void printObjects() const;
            std::vector<std::shared_ptr<ICelestialBody>> getOrbitingBodies() const;
            void calculateRelevantBodiesAll() const;
            void calculateRelevantBodies() const;
            double calculatePotentialEnergy() const;
            double calculateKineticEnergy() const;
            void saveOutput(int body, double time,std::string name) const;
            void evolve(int ,double , int ,int ,std::string ,bool );
            void readFile(std::string);

	};


}
#endif
