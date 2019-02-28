#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include "actor.hpp"
#include "position.hpp"

class Environment
{
    private:
        std::vector< Actor* > actors;
    
    public:
        Environment();
        Environment( const Environment & source );
        Environment & operator=( const Environment & source );
};

#endif