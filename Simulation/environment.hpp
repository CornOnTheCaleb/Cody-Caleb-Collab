#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <string>
#include "position.hpp"
using std::map;
using std::vector;
using std::string;

class Actor;

/*
=======================================================================
------------------------------ENVIRONMENT------------------------------
======================================================================= */
class Environment
{
    protected:
        map< string, vector< Actor* > > actors;
        unsigned long long time;
        vector< vector < string > > grid;
    
    public:
        Environment();
        Environment( const string file_name );
        Environment( const Environment & source );
        virtual ~Environment();
        Environment & operator=( const Environment & source );
        void spawn_actor(Actor* const actor);
        void run( int time_steps = -1 ); // while loop that basically runs everything
        // void smart_print();
        void clear();
};

#endif