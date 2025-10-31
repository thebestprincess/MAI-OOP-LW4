#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>

#include "../include/Point.h"
#include "../include/Array.h"
#include "../include/Figure.h"
#include "../include/Polygon.h"
#include "../include/Rectangle.h"
#include "../include/Rhombus.h"
#include "../include/Trapezoid.h"

// ============================================================================
// TESTS FOR POINT
// ============================================================================

TEST(PointTest, DefaultConstructor)
{
    Point<int> p(0, 0);
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor)
{
    Point<double> p(3.5, 2.7);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 2.7);
}

TEST(PointTest, CopyConstructor)
{
    Point<float> p1(1.1f, 2.2f);
    Point<float> p2(p1);
    EXPECT_FLOAT_EQ(p2.x, 1.1f);
    EXPECT_FLOAT_EQ(p2.y, 2.2f);
}

TEST(PointTest, MoveConstructor)
{
    Point<double> p1(5.5, 6.6);
    Point<double> p2(std::move(p1));
    EXPECT_DOUBLE_EQ(p2.x, 5.5);
    EXPECT_DOUBLE_EQ(p2.y, 6.6);
}

TEST(PointTest, CopyAssignment)
{
    Point<int> p1(10, 20);
    Point<int> p2;
    p2 = p1;
    EXPECT_EQ(p2.x, 10);
    EXPECT_EQ(p2.y, 20);
}

TEST(PointTest, MoveAssignment)
{
    Point<double> p1(7.7, 8.8);
    Point<double> p2;
    p2 = std::move(p1);
    EXPECT_DOUBLE_EQ(p2.x, 7.7);
    EXPECT_DOUBLE_EQ(p2.y, 8.8);
}

TEST(PointTest, EqualityOperator)
{
    Point<int> p1(5, 10);
    Point<int> p2(5, 10);
    Point<int> p3(5, 11);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InequalityOperator)
{
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(1.0, 2.1);
    
    EXPECT_FALSE(p1 != p2);
    EXPECT_TRUE(p1 != p3);
}

TEST(PointTest, OutputOperator)
{
    Point<int> p(3, 4);
    testing::internal::CaptureStdout();
    std::cout << p;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(3, 4)");
}

// ============================================================================
// TESTS FOR ARRAY
// ============================================================================

TEST(ArrayTest, DefaultConstructor)
{
    Array<int> arr;
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_EQ(arr.get_capacity(), 16);
    EXPECT_TRUE(arr.get_size() == 0);
}

TEST(ArrayTest, SizeConstructor)
{
    Array<double> arr(10);
    EXPECT_EQ(arr.get_size(), 0);
    EXPECT_GE(arr.get_capacity(), 10);
}

TEST(ArrayTest, SizeConstructorInvalidSize)
{
    EXPECT_THROW(Array<int> arr(0), std::invalid_argument);
}

TEST(ArrayTest, CopyConstructor)
{
    Array<int> arr1;
    arr1.append(1).append(2).append(3);
    
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.get_size(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveConstructor)
{
    Array<std::string> arr1;
    arr1.append("hello").append("world");
    
    Array<std::string> arr2(std::move(arr1));
    EXPECT_EQ(arr2.get_size(), 2);
    EXPECT_EQ(arr2[0], "hello");
    EXPECT_EQ(arr2[1], "world");
    EXPECT_EQ(arr1.get_size(), 0);
}

TEST(ArrayTest, AppendLValue)
{
    Array<int> arr;
    int value = 42;
    arr.append(value);
    
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr[0], 42);
}

TEST(ArrayTest, AppendRValue)
{
    Array<std::string> arr;
    arr.append("test");
    
    EXPECT_EQ(arr.get_size(), 1);
    EXPECT_EQ(arr[0], "test");
}

TEST(ArrayTest, AppendMultipleWithResize)
{
    Array<int> arr;
    const int NUM_ELEMENTS = 100;
    
    for (int i = 0; i < NUM_ELEMENTS; ++i)
    {
        arr.append(i);
    }
    
    EXPECT_EQ(arr.get_size(), NUM_ELEMENTS);
    for (int i = 0; i < NUM_ELEMENTS; ++i)
    {
        EXPECT_EQ(arr[i], i);
    }
    EXPECT_GE(arr.get_capacity(), NUM_ELEMENTS);
}

TEST(ArrayTest, RemoveElement)
{
    Array<int> arr;
    arr.append(1).append(2).append(3).append(4);
    
    arr.remove(1);
    
    EXPECT_EQ(arr.get_size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 4);
}

TEST(ArrayTest, RemoveFirstElement)
{
    Array<int> arr;
    arr.append(10).append(20).append(30);
    
    arr.remove(0);
    
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 30);
}

TEST(ArrayTest, RemoveLastElement)
{
    Array<int> arr;
    arr.append(10).append(20).append(30);
    
    arr.remove(2);
    
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}

TEST(ArrayTest, RemoveInvalidIndex)
{
    Array<int> arr;
    arr.append(1);
    
    EXPECT_THROW(arr.remove(5), std::out_of_range);
    EXPECT_THROW(arr.remove(-1), std::out_of_range);
}

TEST(ArrayTest, AccessOperator)
{
    Array<double> arr;
    arr.append(1.1).append(2.2);
    
    EXPECT_DOUBLE_EQ(arr[0], 1.1);
    EXPECT_DOUBLE_EQ(arr[1], 2.2);
}

TEST(ArrayTest, AccessOperatorOutOfRange)
{
    Array<int> arr;
    arr.append(42);
    
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr[100], std::out_of_range);
}

TEST(ArrayTest, ConstAccessOperator)
{
    Array<int> arr;
    arr.append(10).append(20);
    
    const Array<int>& const_arr = arr;
    EXPECT_EQ(const_arr[0], 10);
    EXPECT_EQ(const_arr[1], 20);
}

TEST(ArrayTest, CopyAssignment)
{
    Array<int> arr1;
    arr1.append(1).append(2).append(3);
    
    Array<int> arr2;
    arr2 = arr1;
    
    EXPECT_EQ(arr2.get_size(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, SelfAssignment)
{
    Array<int> arr;
    arr.append(1).append(2);
    
    arr = arr; // Self-assignment should be safe
    
    EXPECT_EQ(arr.get_size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(ArrayTest, MoveAssignment)
{
    Array<std::string> arr1;
    arr1.append("move").append("test");
    
    Array<std::string> arr2;
    arr2 = std::move(arr1);
    
    EXPECT_EQ(arr2.get_size(), 2);
    EXPECT_EQ(arr2[0], "move");
    EXPECT_EQ(arr2[1], "test");
    EXPECT_EQ(arr1.get_size(), 0);
}

TEST(ArrayTest, PrintEmptyArray)
{
    Array<int> arr;
    
    testing::internal::CaptureStdout();
    arr.print();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "Array is empty\n");
}

TEST(ArrayTest, PrintSingleElement)
{
    Array<int> arr;
    arr.append(42);
    
    testing::internal::CaptureStdout();
    arr.print(0);
    std::string output = testing::internal::GetCapturedStdout();
    
    // Зависит от реализации оператора << для типа T
    EXPECT_TRUE(output.find("42") != std::string::npos);
}

// ============================================================================
// TESTS FOR POLYGON
// ============================================================================

TEST(PolygonTest, ConstructorValidSize)
{
    EXPECT_NO_THROW(Polygon<double> triangle(3));
    EXPECT_NO_THROW(Polygon<int> square(4));
    EXPECT_NO_THROW(Polygon<float> pentagon(5));
}

TEST(PolygonTest, ConstructorInvalidSize)
{
    EXPECT_THROW(Polygon<double> invalid1(0), std::invalid_argument);
    EXPECT_THROW(Polygon<double> invalid2(1), std::invalid_argument);
    EXPECT_THROW(Polygon<double> invalid3(2), std::invalid_argument);
}

TEST(PolygonTest, TriangleAreaAndCenter)
{
    Polygon<double> triangle(3);
    triangle.set_vertex(0, Point<double>(0, 0));
    triangle.set_vertex(1, Point<double>(3, 0));
    triangle.set_vertex(2, Point<double>(0, 4));
    
    Point<double> center = triangle.get_center();
    double area = triangle.area();
    
    EXPECT_NEAR(center.x, 1.0, 1e-9);
    EXPECT_NEAR(center.y, 1.333333333, 1e-9);
    EXPECT_NEAR(area, 6.0, 1e-9);
}

TEST(PolygonTest, SquareAreaAndCenter)
{
    Polygon<double> square(4);
    square.set_vertex(0, Point<double>(0, 0));
    square.set_vertex(1, Point<double>(2, 0));
    square.set_vertex(2, Point<double>(2, 2));
    square.set_vertex(3, Point<double>(0, 2));
    
    Point<double> center = square.get_center();
    double area = square.area();
    
    EXPECT_NEAR(center.x, 1.0, 1e-9);
    EXPECT_NEAR(center.y, 1.0, 1e-9);
    EXPECT_NEAR(area, 4.0, 1e-9);
}

TEST(PolygonTest, CopyConstructor)
{
    Polygon<double> original(4);
    original.set_vertex(0, Point<double>(0, 0));
    original.set_vertex(1, Point<double>(1, 0));
    original.set_vertex(2, Point<double>(1, 1));
    original.set_vertex(3, Point<double>(0, 1));
    
    Polygon<double> copy(original);
    
    EXPECT_EQ(copy.vertex_count(), 4);
    EXPECT_NEAR(copy.area(), 1.0, 1e-9);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_TRUE(copy.get_vertex(i) == original.get_vertex(i));
    }
}

TEST(PolygonTest, MoveConstructor)
{
    Polygon<double> original(3);
    original.set_vertex(0, Point<double>(0, 0));
    original.set_vertex(1, Point<double>(2, 0));
    original.set_vertex(2, Point<double>(1, 2));
    
    double original_area = original.area();
    Polygon<double> moved(std::move(original));
    
    EXPECT_EQ(moved.vertex_count(), 3);
    EXPECT_NEAR(moved.area(), original_area, 1e-9);
    EXPECT_EQ(original.vertex_count(), 0); 
}

TEST(PolygonTest, AssignmentOperators)
{
    Polygon<double> poly1(3);
    poly1.set_vertex(0, Point<double>(0, 0));
    poly1.set_vertex(1, Point<double>(3, 0));
    poly1.set_vertex(2, Point<double>(0, 3));
    
    Polygon<double> poly2(4);
    poly2 = poly1; // Copy assignment
    
    EXPECT_EQ(poly2.vertex_count(), 3);
    EXPECT_NEAR(poly2.area(), 4.5, 1e-9);
    
    Polygon<double> poly3 = std::move(poly2); // Move assignment
    
    EXPECT_EQ(poly3.vertex_count(), 3);
    EXPECT_NEAR(poly3.area(), 4.5, 1e-9);
    EXPECT_EQ(poly2.vertex_count(), 0);
}

TEST(PolygonTest, VertexAccess)
{
    Polygon<int> square(4);
    Point<int> p1(1, 2);
    Point<int> p2(3, 4);
    
    square.set_vertex(0, p1);
    square.set_vertex(1, p2);
    
    EXPECT_TRUE(square.get_vertex(0) == p1);
    EXPECT_TRUE(square.get_vertex(1) == p2);
}

TEST(PolygonTest, VertexAccessOutOfRange)
{
    Polygon<double> triangle(3);
    
    EXPECT_THROW(triangle.set_vertex(5, Point<double>(0, 0)), std::out_of_range);
    EXPECT_THROW(triangle.get_vertex(5), std::out_of_range);
}

TEST(PolygonTest, EqualityOperator)
{
    Polygon<double> poly1(3);
    poly1.set_vertex(0, Point<double>(0, 0));
    poly1.set_vertex(1, Point<double>(1, 0));
    poly1.set_vertex(2, Point<double>(0, 1));
    
    Polygon<double> poly2(3);
    poly2.set_vertex(0, Point<double>(0, 0));
    poly2.set_vertex(1, Point<double>(1, 0));
    poly2.set_vertex(2, Point<double>(0, 1));
    
    Polygon<double> poly3(3);
    poly3.set_vertex(0, Point<double>(0, 0));
    poly3.set_vertex(1, Point<double>(2, 0));
    poly3.set_vertex(2, Point<double>(0, 1));
    
    EXPECT_TRUE(static_cast<double>(poly1) == static_cast<double>(poly2));
    EXPECT_FALSE(static_cast<double>(poly1) == static_cast<double>(poly3));
}

TEST(PolygonTest, DoubleConversionOperator)
{
    Polygon<double> triangle(3);
    triangle.set_vertex(0, Point<double>(0, 0));
    triangle.set_vertex(1, Point<double>(4, 0));
    triangle.set_vertex(2, Point<double>(0, 3));
    
    double area = static_cast<double>(triangle);
    EXPECT_NEAR(area, 6.0, 1e-9);
}

// ============================================================================
// TESTS FOR RECTANGLE, RHOMBUS, TRAPEZOID
// ============================================================================

TEST(RectangleTest, DefaultConstructor)
{
    Rectangle<double> rect;
    EXPECT_EQ(rect.vertex_count(), 4);
}

TEST(RectangleTest, CopyConstructor)
{
    Rectangle<double> rect1;
    rect1.set_vertex(0, Point<double>(0, 0));
    rect1.set_vertex(1, Point<double>(5, 0));
    rect1.set_vertex(2, Point<double>(5, 3));
    rect1.set_vertex(3, Point<double>(0, 3));
    
    Rectangle<double> rect2(rect1);
    EXPECT_EQ(rect2.vertex_count(), 4);
    EXPECT_NEAR(rect2.area(), 15.0, 1e-9);
}

TEST(RhombusTest, DefaultConstructor)
{
    Rhombus<float> rhombus;
    EXPECT_EQ(rhombus.vertex_count(), 4);
}

TEST(TrapezoidTest, DefaultConstructor)
{
    Trapezoid<int> trapezoid;
    EXPECT_EQ(trapezoid.vertex_count(), 4);
}

// ============================================================================
// INTEGRATION TESTS
// ============================================================================

TEST(IntegrationTest, ArrayOfFigures)
{
    Array<std::shared_ptr<Figure<double>>> figures;
    
    auto triangle = std::make_shared<Polygon<double>>(3);
    triangle->set_vertex(0, Point<double>(0, 0));
    triangle->set_vertex(1, Point<double>(3, 0));
    triangle->set_vertex(2, Point<double>(0, 4));
    
    auto square = std::make_shared<Polygon<double>>(4);
    square->set_vertex(0, Point<double>(0, 0));
    square->set_vertex(1, Point<double>(2, 0));
    square->set_vertex(2, Point<double>(2, 2));
    square->set_vertex(3, Point<double>(0, 2));
    
    figures.append(triangle);
    figures.append(square);
    
    EXPECT_EQ(figures.get_size(), 2);
    EXPECT_NEAR(static_cast<double>(*figures[0]), 6.0, 1e-9);
    EXPECT_NEAR(static_cast<double>(*figures[1]), 4.0, 1e-9);
}

TEST(IntegrationTest, ComplexFigureOperations)
{
    Array<Polygon<double>> polygons;
    
    Polygon<double> triangle(3);
    triangle.set_vertex(0, Point<double>(0, 0));
    triangle.set_vertex(1, Point<double>(2, 0));
    triangle.set_vertex(2, Point<double>(1, 2));
    
    Polygon<double> square(4);
    square.set_vertex(0, Point<double>(0, 0));
    square.set_vertex(1, Point<double>(1, 0));
    square.set_vertex(2, Point<double>(1, 1));
    square.set_vertex(3, Point<double>(0, 1));
    
    polygons.append(triangle);
    polygons.append(square);
    
    EXPECT_EQ(polygons.get_size(), 2);
    EXPECT_NEAR(polygons[0].area(), 2.0, 1e-9);
    EXPECT_NEAR(polygons[1].area(), 1.0, 1e-9);
    
    polygons.remove(0);
    EXPECT_EQ(polygons.get_size(), 1);
    EXPECT_NEAR(polygons[0].area(), 1.0, 1e-9);
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

TEST(EdgeCaseTest, ArrayStressTest)
{
    Array<int> arr;
    const int STRESS_COUNT = 1000;
    
    for (int i = 0; i < STRESS_COUNT; ++i) {
        arr.append(i);
    }
    
    EXPECT_EQ(arr.get_size(), STRESS_COUNT);
    
    for (int i = STRESS_COUNT - 1; i >= 0; i -= 2) {
        arr.remove(i);
    }
    
    EXPECT_EQ(arr.get_size(), STRESS_COUNT / 2);
}

TEST(EdgeCaseTest, SelfComparison)
{
    Polygon<double> poly(3);
    poly.set_vertex(0, Point<double>(1, 1));
    poly.set_vertex(1, Point<double>(2, 2));
    poly.set_vertex(2, Point<double>(1, 3));
    
    EXPECT_TRUE(static_cast<double>(poly) == static_cast<double>(poly)); // Self-comparison should be true
}

TEST(EdgeCaseTest, ZeroAreaPolygon)
{
    Polygon<double> line(3);
    line.set_vertex(0, Point<double>(0, 0));
    line.set_vertex(1, Point<double>(1, 1));
    line.set_vertex(2, Point<double>(2, 2));
    
    EXPECT_NEAR(line.area(), 0.0, 1e-9);
}

// ============================================================================
// MAIN FOR TESTS
// ============================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}