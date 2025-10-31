#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Polygon.h"

template<Scalar T>
class Rhombus final : public Polygon<T>
{
    constexpr static size_t _amount_of_vertices = 4;

public:
    Rhombus();
    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;
    ~Rhombus() noexcept override = default;

public:
    Rhombus& operator=(Rhombus&& other) noexcept; 
    Rhombus& operator=(const Rhombus& other);
};


template<Scalar T>
Rhombus<T>::Rhombus(): Polygon<T>(_amount_of_vertices) {}

template<Scalar T>
Rhombus<T>::Rhombus(const Rhombus& other): Polygon<T>(other) {}

template<Scalar T>
Rhombus<T>::Rhombus(Rhombus&& other) noexcept: Polygon<T>(std::move(other)) {}

template<Scalar T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus& other)
{
    if (this != &other)
    {
        Polygon<T>::operator=(other);
    }

    return *this;
}  

template<Scalar T>
Rhombus<T>& Rhombus<T>::operator=(Rhombus&& other) noexcept
{
    if (this != &other)
    {
        Polygon<T>::operator=(std::move(other));
    }

    return *this;
}

#endif // RHOUMUS_H