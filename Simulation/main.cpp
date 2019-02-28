#include "position.hpp"

#include <iostream>

using namespace std;

std::ostream & operator<<( std::ostream & os, const Position & position )
{
    os << "(" << position.x << ", " << position.y << ")";
    return( os );

}

class A
{
    public:
        virtual void talk() const
        {
            cout << "A" << endl;
        }
};

class B : public A
{
    public:
        virtual void talk() const
        {
            cout << "B" << endl;
        }
};

class C : public A
{
    public:
        virtual void talk() const
        {
            cout << "C" << endl;
        }
};

int main()
{
    A a;
    B b;
    C c;
    A * as[ 2 ] = { &b, &c };
    a.talk();
    b.talk();
    c.talk();
    as[ 0 ]->talk();
    as[ 1 ]->talk();
    return( 0 );
}