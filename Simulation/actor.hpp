#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>
#include <string>
#include "position.hpp"

using namespace std;

class Actor;
class Environment;

class ActorAttributes
{
    public:
        Position position;
        bool impassable;
        string symbol;
        unsigned long long age;

    public:
        ActorAttributes( const Position & position, const bool impassable, const string & symbol );
};

class Action
{
    public:
        virtual void perform( Actor * const actor ) = 0;
};

class Actor
{
    protected:
        Environment * environment;
        ActorAttributes * attributes;
        vector< Action* > actions;
    
    public:
        Actor();
        Actor( ActorAttributes * const attributes );
        Actor( const Actor & source );
        virtual ~Actor();
        Actor & operator=( const Actor & source );
        virtual void update();

        friend class Action;
        friend class Environment;
};

#endif