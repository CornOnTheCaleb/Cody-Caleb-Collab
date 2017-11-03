#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "vector.h"

template <unsigned int N>
void Vector<N>::process_component_list (const unsigned int n, const double value)
{
  set_component(n, value);
  return;
}

template <unsigned int N>
template <typename ... Args>
void Vector<N>::process_component_list (const unsigned int n, const double value, Args ... args)
{
  set_component(n, value);
  process_component_list(n + 1, args...);
  return;
}

template <unsigned int N>
Vector<N>::Vector ()
{
  for (unsigned int n = 0; n < N; ++n)
  {
    set_component(n, 0.0);
  }
}

template <unsigned int N>
Vector<N>::Vector (const Vector<N> & vector)
{
  *this = vector;
}

template <unsigned int N>
template <typename ... Args>
Vector<N>::Vector (Args ... args)
{
  for (unsigned int n = 0; n < N; ++n)
  {
    set_component(n, 0.0);
  }
  set_components(args...);
}

template <unsigned int N>
Vector<N> & Vector<N>::operator= (const Vector<N> & vector)
{
  for (unsigned int n = 0; n < N; ++n)
  {
    set_component(n, vector.get_component(n));
  }
  return (*this);
}

template <unsigned int N>
double Vector<N>::get_component (const unsigned int n) const
{
  return m_components[n];
}

template <unsigned int N>
void Vector<N>::set_component (const unsigned int n, const double value)
{
  m_components[n] = value;
  return;
}

template <unsigned int N>
template <typename ... Args>
void Vector<N>::set_components (Args ... args)
{
  if (sizeof...(args) > N)
  {
    throw 0;
  }
  process_component_list(0, args...);
  return;
}

template <unsigned int N>
bool Vector<N>::operator== (const Vector<N> & vector) const
{
  return !((*this) != vector);
}

template <unsigned int N>
bool Vector<N>::operator!= (const Vector<N> & vector) const
{
  bool equivalent = true;
  unsigned int n = 0;
  while (n < N && equivalent)
  {
    if (get_component(n) != vector.get_component(n))
    {
      equivalent = false;
    }
    ++n;
  }
  return !equivalent;
}

template <unsigned int N>
Vector<N> Vector<N>::operator- () const
{
  return ((*this) * -1);
}

template <unsigned int N>
Vector<N> Vector<N>::operator* (const double scalar) const
{
  Vector<N> result;
  for (unsigned int n = 0; n < N; ++n)
  {
    result.set_component(n, get_component(n) * scalar);
  }
  return result;
}

template <unsigned int N>
Vector<N> Vector<N>::operator/ (const double scalar) const
{
  return ((*this) * (1 / scalar));
}

template <unsigned int N>
Vector<N> Vector<N>::operator+ (const Vector<N> & vector) const
{
  Vector<N> result;
  for (unsigned int n = 0; n < N; ++n)
  {
    result.set_component(n, get_component(n) + vector.get_component(n));
  }
  return result;
}

template <unsigned int N>
Vector<N> Vector<N>::operator- (const Vector<N> & vector) const
{
  return ((*this) + (-vector));
}

template <unsigned int N>
Vector<N> & Vector<N>::operator*= (const double scalar)
{
  for (unsigned int n = 0; n < N; ++n)
  {
    set_component(n, get_component(n) * scalar);
  }
  return (*this);
}

template <unsigned int N>
Vector<N> & Vector<N>::operator/= (const double scalar)
{
  return ((*this) *= (1 / scalar));
}

template <unsigned int N>
Vector<N> & Vector<N>::operator+= (const Vector<N> & vector)
{
  for (unsigned int n = 0; n < N; ++n)
  {
    set_component(n, get_component(n) + vector.get_component(n));
  }
  return (*this);
}

template <unsigned int N>
Vector<N> & Vector<N>::operator-= (const Vector<N> & vector)
{
  return ((*this) += (-vector));
}

template <unsigned int N>
double Vector<N>::length () const
{
  double sumOfSquares = 0;
  for (unsigned int n = 0; n < N; ++n)
  {
    sumOfSquares += (get_component(n) * get_component(n));
  }
  return sqrt(sumOfSquares);
}

template <unsigned int N>
Vector<N> Vector<N>::normalize () const
{
  return ((*this) / length());
}

template <unsigned int N>
std::ostream & operator<< (std::ostream & os, const Vector<N> & vector)
{
  os << "(";
  for (unsigned int n = 0; n < N; ++n)
  {
    os << vector.get_component(n) << (n != N - 1 ? ", " : "");
  }
  os << ")";
  return os;
}

#endif
