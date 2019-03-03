#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "position.hpp"

class Environment;

class ActorAttributes
{
    public:
        Position position;
};

class Actor
{
    protected:
        Environment * environment;
        ActorAttributes * attributes;
    
    public:
        Actor();
        Actor( const ActorAttributes * attributes );
        Actor( const Actor & source );
        Actor & operator=( const Actor & source );
};

#endif