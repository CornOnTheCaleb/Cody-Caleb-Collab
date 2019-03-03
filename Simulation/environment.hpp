#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <string>
#include "position.hpp"

class Actor;

class Environment
{
    protected:
        std::vector< Actor* > actors;
        unsigned long long time;
        std::vector< std::vector < std::string > > grid;
    
    public:
        Environment();
        Environment( const Environment & source );
        Environment & operator=( const Environment & source );
};

#endif