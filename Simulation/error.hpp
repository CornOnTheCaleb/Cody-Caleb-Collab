/*
Programmer: Caleb Berg
Course: 5400 SP2019
File: error.hpp
Date: 02/17/19
*/

#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

enum ErrorEnum
{
    FILE_OPEN_ERROR,
    PARSE_ERROR,
    COMMAND_LINE_ERROR
};

template< ErrorEnum E >
class Error
{
    private:
        string msg;

    public:
        // Description: Default constructor
        // Pre: None
        // Post: Error is constructed with no message
        Error() {}

        // Description: Parameterized constructor
        // Pre: None
        // Post: Error is constructed with passed message
        Error( const string & msg ) : msg( msg ) {}

        // Description: The message() function returns a message describing the error
        // Pre: None
        // Post: Returns the message describing the error as a string
        const string message() const { return( this->msg ); }
};

#endif