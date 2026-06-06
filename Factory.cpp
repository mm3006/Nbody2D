#ifndef FACTORY_CPP
#define FACTORY_CPP

#include "Factory.hpp"

namespace Space{


    std::shared_ptr<Star> CelestialBodyFactory::createStar(std::vector<std::basic_string<char>> row){
        return std::make_shared<Star>(Star(stod(row.at(1)),stod(row.at(2)),stod(row.at(3)),stod(row.at(4)),stod(row.at(5)),row.at(6)));
    }

    std::shared_ptr<Planet> CelestialBodyFactory::createPlanet(std::vector<std::basic_string<char>> row, std::shared_ptr<ICelestialBody> starptr){
        return std::make_shared<Planet>(Planet(stod(row.at(1)),stod(row.at(2)),stod(row.at(3)),stod(row.at(4)),stod(row.at(5)),row.at(6),starptr));
    }

    std::shared_ptr<Moon> CelestialBodyFactory::createMoon(std::vector<std::basic_string<char>> row, std::shared_ptr<ICelestialBody>planetptr){
        return std::make_shared<Moon>(Moon(stod(row.at(1)),stod(row.at(2)),stod(row.at(3)),stod(row.at(4))+planetptr->getxVel(),stod(row.at(5)),row.at(6),planetptr));
    }

}

#endif