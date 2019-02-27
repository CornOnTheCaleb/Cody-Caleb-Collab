#include "position.hpp"

Position::Position() :
    x( 0 ),
    y( 0 )
{

}   /* Position::Position() */

Position::Position( const long x, const long y ) :
    x( x ),
    y( y )
{

}   /* Position::Position() */

Position::Position( const Position & source )
{
    ( *this ) = source;

}   /* Position::Position() */

Position & Position::operator=( const Position & source )
{
    if( this != &source )
    {
        this->x = source.x;
        this->y = source.y;
    }
    return( *this );

}   /* Position::operator=() */

bool Position::operator==( const Position & rhs ) const
{
    return( !( ( *this ) != rhs ) );

}   /* Position::operator==() */

bool Position::operator!=( const Position & rhs ) const
{
    return( ( this->x != rhs.x ) || ( this->y != rhs.y ) );

}   /* Position::operator!=() */

Position Position::operator+( const Direction & rhs ) const
{
    Position result( *this );
    return( result += rhs );

}   /* Position::operator+() */

Position & Position::operator+= ( const Direction & rhs )
{
    this->x += rhs.x;
    this->y += rhs.y;
    return( *this );

}   /* Position::operator+=() */

Position Position::operator-( const Direction & rhs ) const
{
    Position result( *this );
    return( result -= rhs );

}   /* Position::operator-() */

Position & Position::operator-= ( const Direction & rhs )
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return( *this );

}   /* Position::operator-=() */

Direction Position::operator-( const Position & rhs ) const
{
    Direction result( ( rhs.x - this->x ), ( rhs.y - this->y ) );
    return( result );

}   /* Position::operator-() */

Direction::Direction() :
    x( 0 ),
    y( 0 )
{

}   /* Direction::Direction() */

Direction::Direction( const long x, const long y ) :
    x( x ),
    y( y )
{

}   /* Direction::Direction() */

Direction::Direction( const Direction & source )
{
    ( *this ) = source;

}   /* Direction::Direction() */

Direction & Direction::operator=( const Direction & source )
{
    if( this != &source )
    {
        this->x = source.x;
        this->y = source.y;
    }
    return( *this );

}   /* Direction::operator=() */

bool Direction::operator==( const Direction & rhs ) const
{
    return( !( ( *this ) != rhs ) );

}   /* Direction::operator==() */

bool Direction::operator!=( const Direction & rhs ) const
{
    return( ( this->x != rhs.x ) || ( this->y != rhs.y ) );

}   /* Direction::operator!=() */

Direction Direction::operator+( const Direction & rhs ) const
{
    Direction result( *this );
    return( result += rhs );

}   /* Direction::operator+() */

Direction & Direction::operator+= ( const Direction & rhs )
{
    this->x += rhs.x;
    this->y += rhs.y;
    return( *this );

}   /* Direction::operator+=() */

Direction Direction::operator-( const Direction & rhs ) const
{
    Direction result( *this );
    return( result -= rhs );

}   /* Direction::operator-() */

Direction & Direction::operator-= ( const Direction & rhs )
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return( *this );

}   /* Direction::operator-=() */

Direction Direction::operator*( const long scalar ) const
{
    Direction result( *this );
    return( result *= scalar );

}   /* Direction::operator*() */

Direction & Direction::operator*=( const long scalar )
{
    this->x *= scalar;
    this->y *= scalar;
    return( *this );

}   /* Direction::operator*=() */

Direction Direction::operator/( const long scalar ) const
{
    Direction result( *this );
    return( result /= scalar );

}   /* Direction::operator/() */

Direction & Direction::operator/=( const long scalar )
{
    this->x = static_cast< long >( this->x / scalar );
    this->y = static_cast< long >( this->y / scalar );
    return( *this );

}   /* Direction::operator/=() */

Direction Direction::operator!() const
{
    Direction result( -( this->x ), -( this->y ) );
    return( result );

}   /* Direction::operator!() */

double Direction::magnitude() const
{
    return( sqrt( ( this->x * this->x ) + ( this->y * this->y ) ) );

}   /* Direction::magnitude() */