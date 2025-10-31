#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include <iostream>
#include <istream>


template<Scalar T> 
class Figure
{
public:
    Figure() = default;
    virtual ~Figure() noexcept = default;
    
protected:
    virtual Point<double> calculate_center() const = 0;
    virtual std::ostream& write_to_stream(std::ostream& ostream) const = 0 ;
    virtual std::istream& read_from_stream(std::istream& istream) = 0;
    
public:
    virtual explicit operator double() const;
    
public:
    template<Scalar S>
    friend std::ostream& operator<<(std::ostream& ostream, const Figure<S>& figure);
    template<Scalar S>
    friend std::istream& operator>>(std::istream& istream, Figure<S>& figure);
    virtual double area() const = 0;
    virtual Point<double> get_center() const;
};

template<Scalar T>
std::ostream& operator<<(std::ostream& ostream,const Figure<T>& figure)
{
    figure.write_to_stream(ostream);
    return ostream;
}

template<Scalar T>
std::istream& operator>>(std::istream& istream, Figure<T>& figure)
{
    figure.read_from_stream(istream);
    return istream;
}

template<Scalar T>
Figure<T>::operator double() const
{
    return this->area();
}

template<Scalar T>
Point<double> Figure<T>::get_center() const
{
    return calculate_center();
}

#endif // FIGURE_H