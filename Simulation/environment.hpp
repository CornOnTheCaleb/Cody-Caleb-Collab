#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
//#include "position.hpp"
using std::map;
using std::vector;
using std::string;

class Actor;

const string BLOCK = "▓";

/*
=======================================================================
------------------------------ENVIRONMENT------------------------------
======================================================================= */
class Environment
{
    protected:
        map< string, vector< Actor* > > actors;
        unsigned long long time;
        vector< vector < vector < string > > > grid;
    
    public:
        Environment() {}
        Environment( const int length, const int width); // just for testing
        Environment( const string file_name );
        Environment( const Environment & source );
        /*virtual*/ ~Environment() {};
        int get_width() const;
        int get_length() const;
        int get_height() const;
        Environment & operator=( const Environment & source );
        void spawn_actor(Actor* const actor);
        void run( int time_steps = -1 ); // while loop that basically runs everything
        void print() const;
        // void smart_print();
        void clear();
};

#endif