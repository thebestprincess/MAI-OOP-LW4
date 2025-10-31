#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "Polygon.h"

template<Scalar T>
class Rectangle final : public Polygon<T>
{
    constexpr static size_t _amount_of_vertices = 4;

public:
    Rectangle();
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    ~Rectangle() noexcept override = default;

public:
    Rectangle& operator=(Rectangle&& other) noexcept; 
    Rectangle& operator=(const Rectangle& other);
};


template<Scalar T>
Rectangle<T>::Rectangle(): Polygon<T>(_amount_of_vertices) {}

template<Scalar T>
Rectangle<T>::Rectangle(const Rectangle& other): Polygon<T>(other) {}

template<Scalar T>
Rectangle<T>::Rectangle(Rectangle&& other) noexcept: Polygon<T>(std::move(other)) {}

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle& other)
{
    if (this != &other)
    {
        Polygon<T>::operator=(other);
    }

    return *this;
}  

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle&& other) noexcept
{
    if (this != &other)
    {
        Polygon<T>::operator=(std::move(other));
    }

    return *this;
}


#endif // RECTANGLE_H