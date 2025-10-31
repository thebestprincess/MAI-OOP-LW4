#ifndef ARRAY_H
#define ARRAY_H


#include <cstddef>
#include <memory>
#include <iomanip>
#include <iostream>
#include <stdexcept>


template<class T>
class Array final
{
private:
    size_t size = 0;
    size_t capacity = 16;
    std::shared_ptr<T[]> array;

private:
    void resize();

public:
    Array();
    Array(size_t size);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array() noexcept = default;

public:
    Array& append(const T& figure);
    Array& append(T&& figure);
    void remove(size_t index);
    void print() const;
    void print(size_t index) const;
    void total_area() const;
    size_t get_size() const;
    size_t get_capacity() const;

public:
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    operator double() const;
    T& operator[](size_t index);
    T operator[](size_t index) const;
};


template<class T>
void Array<T>::resize()
{
    capacity *= 2;
    auto new_array = std::make_shared<T[]>(capacity);

    for (size_t i = 0; i < size; ++i)
    {
        new_array[i] = std::move(array[i]);
    }

    array = std::move(new_array);
}


template<class T>
Array<T>::Array()
{
    array = std::make_shared<T[]>(capacity);
}


template<class T>
Array<T>::Array(size_t reserve_size): capacity(reserve_size)
{
    if (reserve_size <= 0)
    {
        throw std::invalid_argument("Error: You passed incorrect size for array.\nSize should be greater than 0.");
    }
    array = std::make_shared<T[]>(capacity);
}


template<class T>
Array<T>::Array(const Array& other): size(other.size), capacity(other.capacity)
{
    array = std::make_shared<T[]>(capacity);

    for (size_t i = 0; i < size; ++i)
    {
        array[i] = other.array[i];
    }
}


template<class T>
Array<T>::Array(Array&& other) noexcept: size(other.size), capacity(other.capacity), array(std::move(other.array))
{
    other.size = 0;
    other.capacity = 0;
    other.array = nullptr;
}


template<class T>
Array<T>& Array<T>::append(const T& figure)
{
    if (size == capacity)
    {
        resize();
    }

    array[size++] = figure;

    return *this;
}


template<class T>
Array<T>& Array<T>::append(T&& figure)
{
    if (size == capacity)
    {
        resize();
    }

    array[size++] = std::move(figure);

    return *this;
}



template<class T>
void Array<T>::remove(size_t index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Error: Index out of range.");
    }

    for (size_t i = index + 1; i < size; ++i)
    {
        array[i - 1] = array[i];
    }

    --size;
}


template<class T>
void Array<T>::print() const
{
    if (size == 0)
    {
        std::cout << "Array is empty" << std::endl;
    }

    for (size_t i = 0; i < size; ++i)
    {
        std::cout << array[i];
    }
}


template<class T>
void Array<T>::print(size_t index) const
{
    if (index < 0 || index >= size)
    {
        throw std::invalid_argument("Error: index out of range.");
    }

    std::cout << array[index] << std::endl;
}


template<class T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this == &other)
    {
        return *this;
    }

    size = other.size;
    capacity = other.capacity;
    array = std::make_shared<T[]>(capacity);

    for (size_t i = 0; i < size; ++i)
    {
        array[i] = other.array[i]; 
    }
    
    return *this;
}


template<class T>
Array<T>& Array<T>::operator=(Array&& other) noexcept
{
    size = other.size;
    capacity = other.capacity;
    array = std::move(other.array);

    other.size = 0;
    other.capacity = 0;
    other.array = nullptr;

    return *this;
}


template<class T>
void Array<T>::total_area() const
{
    if (size == 0)
    {
        std::cout << "Total area is: 0\n";
        return;
    }

    long double total_area = 0.0;

    for (size_t i = 0; i < size; ++i)
    {
        total_area += static_cast<double>(array);
    }
    
    std::cout << "Total area is: " << std::setprecision(2) << total_area << std::endl;
}


template<class T>
size_t Array<T>::get_size() const
{
    return size;
}


template<class T>
size_t Array<T>::get_capacity() const
{
    return capacity;
}


template<class T>
T& Array<T>::operator[](size_t index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Error: index out of range.");
    }

    return array[index];
}


template<class T>
T Array<T>::operator[](size_t index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Error: index out of range.");
    }

    return array[index];
}


#endif // ARRAY_H