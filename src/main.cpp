#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>


#include "../include/Point.h"
#include "../include/Array.h"
#include "../include/Figure.h"
#include "../include/Polygon.h"
#include "../include/Rectangle.h"
#include "../include/Rhombus.h"
#include "../include/Trapezoid.h"


void demonstrate_points()
{
    std::cout << "=== DEMONSTRATING POINTS ===" << std::endl;
    
    Point<int> int_point(5, 10);
    Point<double> double_point(3.14, 2.71);
    Point<float> float_point(1.5f, 2.5f);
    
    std::cout << "Integer point: " << int_point << std::endl;
    std::cout << "Double point: " << double_point << std::endl;
    std::cout << "Float point: " << float_point << std::endl;
    
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 2.1);
    
    std::cout << "p1 == p2: " << (p1 == p2) << std::endl;
    std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
    std::cout << "p1 != p3: " << (p1 != p3) << std::endl;
    std::cout << std::endl;
}


void demonstrate_array_basic_types()
{
    std::cout << "=== DEMONSTRATING ARRAY WITH BASIC TYPES ===" << std::endl;
    
    Array<int> int_array;
    for (int i = 0; i < 10; ++i)
    {
        int_array.append(i * i);
    }
    
    std::cout << "Integer array contents: ";
    int_array.print();
    
    Array<std::string> string_array;
    string_array.append("Hello").append("World").append("!");
    
    std::cout << "\nString array contents: ";
    string_array.print();
    std::cout << std::endl;
}


void demonstrate_figures_array() {
    std::cout << "=== DEMONSTRATING ARRAY OF FIGURES ===" << std::endl;
    
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto triangle = std::make_shared<Polygon<double>>(3);
    triangle->set_vertex(0, Point<double>(0, 0));
    triangle->set_vertex(1, Point<double>(4, 0));
    triangle->set_vertex(2, Point<double>(0, 3));
    
    auto pentagon = std::make_shared<Polygon<double>>(5);
    pentagon->set_vertex(0, Point<double>(0, 1));
    pentagon->set_vertex(1, Point<double>(0.95, 0.31));
    pentagon->set_vertex(2, Point<double>(0.59, -0.81));
    pentagon->set_vertex(3, Point<double>(-0.59, -0.81));
    pentagon->set_vertex(4, Point<double>(-0.95, 0.31));
    
    auto rectangle = std::make_shared<Rectangle<double>>();
    rectangle->set_vertex(0, Point<double>(0, 0));
    rectangle->set_vertex(1, Point<double>(5, 0));
    rectangle->set_vertex(2, Point<double>(5, 2));
    rectangle->set_vertex(3, Point<double>(0, 2));
    
    figures.append(triangle);
    figures.append(pentagon);
    figures.append(rectangle);
    
    std::cout << "Total figures in array: " << figures.get_size() << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    
    double total_area = 0.0;
    for (size_t i = 0; i < figures.get_size(); ++i)
    {
        std::cout << "Figure " << i << " - ";
        figures.print(i);
        total_area += figures[i]->area();
    }
    
    std::cout << "\nTotal area of all figures: " << total_area << std::endl;
    std::cout << std::endl;
}

void demonstrate_array_operations() {
    std::cout << "=== DEMONSTRATING ARRAY OPERATIONS ===" << std::endl;
    
    Array<Point<double>> points_array;
    
    points_array.append(Point<double>(1, 1));
    points_array.append(Point<double>(2, 2));
    points_array.append(Point<double>(3, 3));
    points_array.append(Point<double>(4, 4));
    
    std::cout << "Initial array: ";
    points_array.print();
    
    points_array.remove(1);
    std::cout << "\nAfter removing index 1: ";
    points_array.print();
    
    points_array.append(Point<double>(5, 5));
    points_array.append(Point<double>(6, 6));
    
    std::cout << "\nAfter adding more elements: ";
    points_array.print();
    
    std::cout << "\nFinal size: " << points_array.get_size() << std::endl;
    std::cout << "Final capacity: " << points_array.get_capacity() << std::endl;
    std::cout << std::endl;
}

void demonstrate_concept_usage() {
    std::cout << "=== DEMONSTRATING CONCEPT USAGE ===" << std::endl;
    
    // Эти компилируются (скалярные типы)
    Point<int> p1;
    Point<double> p2;
    Point<float> p3;
    
    // Эти НЕ скомпилируются (раскомментируйте для проверки)
    // Point<std::string> p4; // Ошибка: не удовлетворяет концепту Scalar
    // Point<std::vector<int>> p5; // Ошибка: не удовлетворяет концепту Scalar
    
    std::cout << "Concepts work correctly - only scalar types allowed!" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "GEOMETRY LIBRARY DEMONSTRATION\n" << std::endl;
    
    try {
        demonstrate_points();
        demonstrate_array_basic_types();
        demonstrate_figures_array();
        demonstrate_array_operations();
        demonstrate_concept_usage();
        
        std::cout << "=== DEMONSTRATION COMPLETED SUCCESSFULLY ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error during demonstration: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}