//
// Created by alice on 28.09.2025.
//
#include <iostream>
#include <cmath>


class Triangle {
private:
    double sideA, sideB, sideC;

public:
    Triangle(double a, double b, double c) {
        sideA = a;
        sideB = b;
        sideC = c;
    }

    [[nodiscard]] double area() const {
        double p = perimeter() / 2.0;
        return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
    }

    [[nodiscard]] double perimeter() const {
        return sideA + sideB + sideC;
    }

    void print() const {
        std::cout << "Треугольник: стороны " << sideA << ", " << sideB << ", " << sideC
                  << ", периметр = " << perimeter() << ", площадь = " << area() << std::endl;
    }
};

class Square {
private:
    double side;

public:
    explicit Square(double s) {
        side = s;
    }

    [[nodiscard]] double area() const {
        return side * side;
    }

    [[nodiscard]] double perimeter() const {
        return 4 * side;
    }

    void print() const {
        std::cout << "Квадрат: сторона " << side
                  << ", периметр = " << perimeter() << ", площадь = " << area() << std::endl;
    }
};

class Circle {
private:
    double radius;

public:
    explicit Circle(double r) {
        radius = r;
    }

    [[nodiscard]] double area() const {
        return std::numbers::pi * radius * radius;
    }

    [[nodiscard]] double perimeter() const {
        return 2 * std::numbers::pi * radius;
    }

    void print() const {
        std::cout << "Окружность: радиус " << radius
                  << ", периметр = " << perimeter() << ", площадь = " << area() << std::endl;
    }
};

int main() {
    Triangle triangle(3.0, 4.0, 5.0);
    Square square(5.0);
    Circle circle(3.0);

    triangle.print();
    square.print();
    circle.print();

    return 0;
}