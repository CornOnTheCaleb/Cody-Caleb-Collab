#ifndef POSITION_HPP
#define POSITION_HPP

#include <cmath>

struct Position;
struct Direction;

struct Position
{
    long x;
    long y;

    Position();
    Position( const long x, const long y );
    Position( const Position & source );
    Position & operator=( const Position & source );
    bool operator==( const Position & rhs ) const;
    bool operator!=( const Position & rhs ) const;
    Position operator+( const Direction & rhs ) const;
    Position & operator+= ( const Direction & rhs );
    Position operator-( const Direction & rhs ) const;
    Position & operator-= ( const Direction & rhs );
    Direction operator-( const Position & rhs ) const;
};

const Position ORIGIN( 0, 0 );

struct Direction
{
    long x;
    long y;

    Direction();
    Direction( const long x, const long y );
    Direction( const Direction & source );
    Direction & operator=( const Direction & source );
    bool operator==( const Direction & rhs ) const;
    bool operator!=( const Direction & rhs ) const; 
    Direction operator+( const Direction & rhs ) const;
    Direction & operator+=( const Direction & rhs );
    Direction operator-( const Direction & rhs ) const;
    Direction & operator-=( const Direction & rhs );
    Direction operator*( const long scalar ) const;
    Direction & operator*=( const long scalar );
    Direction operator/( const long scalar ) const;
    Direction & operator/=( const long scalar );
    Direction operator!() const;
    double magnitude() const;
};

const Direction UP( 0, 1 );
const Direction DOWN( 0, -1 );
const Direction LEFT( -1, 0 );
const Direction RIGHT( 1, 0 );

const Direction DIRECTIONS[] = { UP, DOWN, LEFT, RIGHT };
const unsigned short NUM_DIRECTIONS = ( sizeof( DIRECTIONS ) / sizeof( DIRECTIONS[ 0 ] ) );

#endif  /* POSITION_HPP */