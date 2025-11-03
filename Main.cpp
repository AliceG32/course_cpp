//
// Created by alice on 11.10.2025.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <numbers>
#include <cassert>

class Shape {
public:
    virtual ~Shape() = default;

    [[nodiscard]] virtual double perimeter() const = 0;

    [[nodiscard]] virtual double area() const = 0;
};

class Triangle : public Shape {
private:
    double sideA, sideB, sideC;

public:
    Triangle(double a, double b, double c) : sideA(a), sideB(b), sideC(c) {}

    [[nodiscard]] double perimeter() const final {
        return sideA + sideB + sideC;
    }

    [[nodiscard]] double area() const final {
        double p = perimeter() / 2.0;
        return std::sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
    }

};

class Square : public Shape {
private:
    double side;

public:
    explicit Square(double s) : side(s) {}

    [[nodiscard]] double perimeter() const final {
        return 4 * side;
    }

    [[nodiscard]] double area() const final {
        return side * side;
    }

};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}

    [[nodiscard]] double perimeter() const final {
        return 2 * std::numbers::pi * radius;
    }

    [[nodiscard]] double area() const final {
        return std::numbers::pi * radius * radius;
    }
};

int main() {
    std::vector<Shape *> shapes;

    shapes.push_back(new Triangle(3.0, 4.0, 5.0));
    shapes.push_back(new Square(5.0));
    shapes.push_back(new Circle(3.0));


    Triangle triangle(3.0, 4.0, 5.0);
    assert(triangle.perimeter() == 12.0);
    assert(triangle.area() == 6.0);

    Square square(5.0);
    assert(square.perimeter() == 20.0);
    assert(square.area() == 25.0);

    Circle circle(3.0);
    double expected_circle_perimeter = 2 * std::numbers::pi * 3.0;
    double expected_circle_area = std::numbers::pi * 3.0 * 3.0;

    assert(std::abs(circle.perimeter() - expected_circle_perimeter) < 0.0001);
    assert(std::abs(circle.area() - expected_circle_area) < 0.0001);

    Shape *shape1 = &triangle;
    Shape *shape2 = &square;
    Shape *shape3 = &circle;

    assert(shape1->perimeter() == 12.0);
    assert(shape1->area() == 6.0);

    assert(shape2->perimeter() == 20.0);
    assert(shape2->area() == 25.0);

    assert(std::abs(shape3->perimeter() - expected_circle_perimeter) < 0.0001);
    assert(std::abs(shape3->area() - expected_circle_area) < 0.0001);

    assert(shapes.size() == 3);
    assert(shapes[0]->perimeter() == 12.0);
    assert(shapes[1]->area() == 25.0);
    assert(std::abs(shapes[2]->perimeter() - expected_circle_perimeter) < 0.0001);


    for (auto &shape: shapes) {
        delete shape;
    }
    shapes.clear();

    return 0;
}