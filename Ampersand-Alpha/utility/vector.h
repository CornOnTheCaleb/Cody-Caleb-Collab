#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>    // For sqrt()

template <unsigned int N>
class Vector
{
  private:
    double m_components[N];
    void process_component_list (const unsigned int n, const double value);
    template <typename ... Args>
    void process_component_list (const unsigned int n, const double value, Args ... args);
  public:
    Vector ();
    Vector (const Vector<N> & vector);
    template <typename ... Args>
    Vector (Args ... args);
    virtual double get_component (const unsigned int n) const;
    virtual void set_component (const unsigned int n, const double value);
    template <typename ... Args>
    void set_components (Args ... args);
    Vector<N> & operator= (const Vector<N> & vector);
    virtual bool operator== (const Vector<N> & vector) const;
    virtual bool operator!= (const Vector<N> & vector) const;
    virtual Vector<N> operator- () const;
    virtual Vector<N> operator* (const double scalar) const;
    virtual Vector<N> operator/ (const double scalar) const;
    virtual Vector<N> operator+ (const Vector<N> & vector) const;
    virtual Vector<N> operator- (const Vector<N> & vector) const;
    virtual Vector<N> & operator*= (const double scalar);
    virtual Vector<N> & operator/= (const double scalar);
    virtual Vector<N> & operator+= (const Vector<N> & vector);
    virtual Vector<N> & operator-= (const Vector<N> & vector);
    virtual double length () const;
    virtual Vector<N> normalize () const;
};

template <unsigned int N>
std::ostream & operator<< (std::ostream & os, const Vector<N> & vector);

#include "vector.hpp"

#endif
