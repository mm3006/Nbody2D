#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Star.hpp"
#include "Planet.hpp"
#include "Moon.hpp"


namespace Space{


class Factory{

    public:
    virtual std::shared_ptr<Star> createStar(std::vector<std::basic_string<char>> ) = 0;
    virtual std::shared_ptr<Planet> createPlanet(std::vector<std::basic_string<char>>,std::shared_ptr<ICelestialBody> ) = 0;
    virtual std::shared_ptr<Moon> createMoon(std::vector<std::basic_string<char>>,std::shared_ptr<ICelestialBody> ) = 0;


};

class CelestialBodyFactory: public Factory{
    public:
    virtual std::shared_ptr<Star> createStar(std::vector<std::basic_string<char>> ) override final;
    virtual std::shared_ptr<Planet> createPlanet(std::vector<std::basic_string<char>>,std::shared_ptr<ICelestialBody>) override final;
    virtual std::shared_ptr<Moon> createMoon(std::vector<std::basic_string<char>>,std::shared_ptr<ICelestialBody> ) override final;

};



}

#endif