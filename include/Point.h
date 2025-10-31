#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <ostream>
#include <type_traits>

template<class T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point final
{
public:
    T x;
    T y;

public:
    Point();
    Point(T x, T y);
    Point(const Point& other);
    Point(Point&& other) noexcept;
    ~Point() = default;

public:
    Point& operator=(const Point& other);
    Point& operator=(Point&& other) noexcept; 
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

public:
    template<Scalar S>
    friend std::ostream& operator<<(std::ostream& ostream, Point<S>& point);
};

template<Scalar T>
Point<T>::Point(): x(0.0), y(0.0) {}

template<Scalar T>
Point<T>::Point(T x, T y): x(x), y(y) {}

template<Scalar T>
Point<T>::Point(Point&& other) noexcept: x(std::move(other.x)), y(std::move(other.y)) {}

template<Scalar T>
Point<T>::Point(const Point& other): x(other.x), y(other.y) {}

template<Scalar T>
Point<T>& Point<T>::operator=(const Point& other)
{
    x = other.x;
    y = other.y;

    return *this;
}

template<Scalar T>
Point<T>& Point<T>::operator=(Point&& other) noexcept
{
    x = std::move(other.x);
    y = std::move(other.y);

    other.x = 0.0;
    other.y = 0.0;

    return *this;
}


template<Scalar T>
bool Point<T>::operator==(const Point& other) const
{
    const double EPS = 1e-6;
    if (std::abs(x - other.x) <= EPS && std::abs(y - other.y) <= EPS)
    {
        return true;
    }

    return false;
}


template<Scalar T>
bool Point<T>::operator!=(const Point& other) const
{
    return !(this->operator==(other));
}


template<Scalar T>
std::ostream& operator<<(std::ostream& ostream, Point<T>& point)
{
    ostream << "(" << point.x << ", " << point.y << ")";
    return ostream;
}


#endif // POINT_H