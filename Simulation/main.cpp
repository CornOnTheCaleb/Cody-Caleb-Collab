#include "position.hpp"

#include <iostream>

std::ostream & operator<<( std::ostream & os, const Position & position )
{
    os << "(" << position.x << ", " << position.y << ")";
    return( os );

}

int main()
{
    Position p1( 3, 4 );
    std::cout << "Distance to origin: " << ( ( p1 - ORIGIN ) * 2 ).magnitude() << std::endl;
    std::cout << p1 + !UP + !LEFT << std::endl;
    return( 0 );
}