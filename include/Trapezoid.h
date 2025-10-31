#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Polygon.h"
#include <cstddef>

template<Scalar T>
class Trapezoid final : public Polygon<T>
{
    constexpr static size_t _amount_of_vertices = 4;
public:
    Trapezoid();
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    ~Trapezoid() noexcept override = default;

public:
    Trapezoid& operator=(Trapezoid&& other) noexcept; 
    Trapezoid& operator=(const Trapezoid& other);
};

template<Scalar T>
Trapezoid<T>::Trapezoid(): Polygon<T>(_amount_of_vertices) {}

template<Scalar T>
Trapezoid<T>::Trapezoid(const Trapezoid& other): Polygon<T>(other) {}

template<Scalar T>
Trapezoid<T>::Trapezoid(Trapezoid&& other) noexcept: Polygon<T>(std::move(other)) {}

template<Scalar T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid& other)
{
    if (this != &other)
    {
        Polygon<T>::operator=(other);
    }

    return *this;
}  

template<Scalar T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid&& other) noexcept
{
    if (this != &other)
    {
        Polygon<T>::operator=(std::move(other));
    }

    return *this;
}

#endif // TRAPEZOID_H