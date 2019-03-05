#include <memory>
#include <iostream>
#include <vector>

using namespace std;

class Animal
{
    public:
        virtual void speak() { cout << "Animal!" << endl; }
        // virtual ~Animal() { cout << "Destroy animal!" << endl; }
};

class Cat : public Animal
{
    public:
        virtual void speak() { cout << "Cat!" << endl; }
};

class Pussy : public Cat
{
    public:
        virtual void speak() { cout << "Pussy!" << endl; }
};

class Dog : public Animal
{
    public:
        virtual void speak() { cout << "Dog!" << endl; }
};

class Farm
{
    public:
        vector< Animal* > animals;
    
    public:
        void speak()
        {
            for( int i = 0; i < animals.size(); ++i )
            {
                animals[ i ]->speak();
            }
        }

        void insert( Animal * const animal )
        {
            animals.push_back( animal );
        }

        ~Farm()
        {
            for( int i = 0; i < animals.size(); ++i )
            {
                delete animals[ i ];
            }
        }
};

class SmartFarm
{
    public:
        vector< unique_ptr< Animal > > animals;
    
    public:
        void speak()
        {
            for( int i = 0; i < animals.size(); ++i )
            {
                animals[ i ]->speak();
            }
        }

        void insert( unique_ptr< Animal > && animal )
        {
            animals.push_back( move( animal ) );
        }
};

int main()
{
    Farm farm;
    farm.insert( new Animal );
    farm.insert( new Cat );
    farm.insert( new Dog );
    farm.insert( new Pussy );
    farm.speak();

    SmartFarm smartFarm;
    smartFarm.insert( make_unique< Animal >() );
    smartFarm.insert( make_unique< Cat >() );
    smartFarm.insert( make_unique< Dog >() );
    smartFarm.insert( make_unique< Pussy >() );
    smartFarm.speak();


    return( 0 );
};