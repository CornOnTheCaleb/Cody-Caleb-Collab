#include "actor.hpp"

ActorAttributes::ActorAttributes( const Position & position, const bool impassable, const string & symbol ) :
    position( position ),
    impassable( impassable ),
    symbol( symbol ),
    age( 0 )
{

}   /* ActorAttributes::ActorAtributes() */

Actor::Actor() :
    environment( nullptr ),
    attributes( nullptr ),
    actions( {} )
{

}   /* Actor::Actor() */

Actor::Actor( ActorAttributes * const attributes ) :
    environment( nullptr ),
    attributes( attributes ),
    actions( {} )
{

}   /* Actor::Actor() */

Actor::Actor( const Actor & source )
{

}   /* Actor::Actor() */

Actor::~Actor()
{

}   /* Actor::~Actor() */

Actor & Actor::operator=( const Actor & source )
{

}   /* Actor::operator=() */

void Actor::update()
{
    for( auto it = this->actions.begin(); it < this->actions.end(); ++it )
    {
        ( *it )->perform( this );
    }
    ++( this->attributes->age );

}   /* Actor::update() */