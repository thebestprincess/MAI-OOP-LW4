#ifndef POLYGON_H
#define POLYGON_H


#include "Figure.h"
#include "Point.h"
#include <cstddef>
#include <memory>
#include <stdexcept>


template<Scalar T>
class Polygon: public Figure<T> 
{
private:
    size_t size;
    std::unique_ptr<Point<T>[]> vertices;

public:
    Polygon() = default;
    Polygon(size_t size);
    Polygon(const Polygon& other);
    Polygon(Polygon&& other) noexcept;
    ~Polygon() noexcept = default;

protected: 
    Point<double> calculate_center() const override;
    std::ostream& write_to_stream(std::ostream& ostream) const override;
    std::istream& read_from_stream(std::istream& istream) override;
    
public:
    double area() const override;
    void set_vertex(size_t index, Point<T> point);
    Point<double> get_center() const override;
    size_t vertex_count() const;
    Point<T> get_vertex(size_t index) const;
    explicit operator double() const override;
    Polygon& operator=(const Polygon& other);
    Polygon& operator=(Polygon&& other) noexcept;
};

template <Scalar T>
Polygon<T>::Polygon(size_t size): size(size)
{
    if (size < 3)
    {
        throw std::invalid_argument("The number of vertices of a polygon is not less than 3.");
    }

    vertices = std::make_unique<Point<T>[]>(size);
}


template <Scalar T>
Polygon<T>::Polygon(const Polygon& other)
{
    size = other.size;
    vertices = std::make_unique<Point<T>[]>(size);

    for (size_t i = 0; i < size; ++i)
    {
        vertices[i] = other.vertices[i];
    }
}


template <Scalar T>
Polygon<T>::Polygon(Polygon&& other) noexcept
{
    size = other.size;
    vertices = std::move(other.vertices);

    other.size = 0;
    other.vertices = nullptr;
}


template <Scalar T>
Point<double> Polygon<T>::calculate_center() const
{
    if (vertices == nullptr)
    {
        throw std::runtime_error("The pointer to the vertices is equal to nullptr.");
    }

    double x_center = 0.0;
    double y_center = 0.0;

    for (size_t i = 0; i < size; ++i)
    {
        x_center += static_cast<double>(vertices[i].x);
        y_center += static_cast<double>(vertices[i].y);
    }
    
    return Point<double>(x_center / size, y_center / size);
}


template<Scalar T>
std::ostream& Polygon<T>::write_to_stream(std::ostream& ostream) const
{
    if (size == 0)
    {
        return ostream << "Empty";
    }

    for (int i = 0; i < size; ++i)
    {
        ostream << "(" << this->vertices[i].x << ", " << this->vertices[i].y << ")" << std::endl; 
    }

    return ostream;
}


template<Scalar T>
std::istream& Polygon<T>::read_from_stream(std::istream& istream)
{
    for (size_t i = 0; i < size; ++i)
    {
        T x, y;
        istream >> x >> y;
        vertices[i] = Point<T>(x, y);
	}

	return istream;
}


template<Scalar T>
void Polygon<T>::set_vertex(size_t index, Point<T> point)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Error: index out of range.");
    }

    vertices[index] = point;
}


template<Scalar T>
double Polygon<T>::area() const
{
    double area = 0;

    for (int i = 0; i < size; ++i) {
        const Point<T>& current = vertices[i];
        const Point<T>& next = vertices[(i + 1) % size];
        area += (current.x * next.y - next.x * current.y);
    }

    return std::abs(area) / 2.0;
}


template<Scalar T>
Point<double> Polygon<T>::get_center() const
{
    return this->calculate_center();
}


template<Scalar T>
size_t Polygon<T>::vertex_count() const
{
    return size;
}


template<Scalar T>
Point<T> Polygon<T>::get_vertex(size_t index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Error: index out of range.");
    }

    return vertices[index];
}


template<Scalar T>
Polygon<T>::operator double() const
{
    return this->area();
}


template<Scalar T>
Polygon<T>& Polygon<T>::operator=(const Polygon& other)
{
    if (this == &other)
    {
        return *this;
    }

    size = other.size;
    vertices = std::make_unique<Point<T>[]>(size);

    for (size_t i = 0; i < size; ++i)
    {
        vertices[i] = other.vertices[i];
    }

    return *this;
}  


template<Scalar T>
Polygon<T>& Polygon<T>::operator=(Polygon&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    size = other.size;
    vertices = std::move(other.vertices);

    other.size = 0;
    other.vertices = nullptr;

    return *this;
}


#endif // POLYGON_H