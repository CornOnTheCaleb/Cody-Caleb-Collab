#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

enum ErrorEnum
{
    MISCELLANEOUS_ERROR
};

template< ErrorEnum E >
class Error
{
    private:
        string msg;

    public:
        Error() {}
        Error( const string & msg ) : msg( msg ) {}
        const string message() const { return( this->msg ); }
};

#endif