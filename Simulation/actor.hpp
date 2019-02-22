#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "position.hpp"

class Actor
{
    private:
        Position position;
    
    public:
        Actor();
        Actor( const Actor & source );
        Actor & operator=( const Actor & source );
};

#endif