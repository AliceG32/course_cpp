//
// Created by alice on 28.09.2025.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Rectangle {
    double upperLeftX;
    double upperLeftY;
    double downRightX;
    double downRightY;

    Rectangle() : upperLeftX(0), upperLeftY(0), downRightX(0), downRightY(0) {}

    Rectangle(double ulx, double uly, double drx, double dry)
            : upperLeftX(ulx), upperLeftY(uly), downRightX(drx), downRightY(dry) {}

    [[nodiscard]] bool isEmpty() const {
        return upperLeftX >= downRightX || upperLeftY >= downRightY;
    }

    [[nodiscard]] double width() const {
        return isEmpty() ? 0 : downRightX - upperLeftX;
    }

    [[nodiscard]] double height() const {
        return isEmpty() ? 0 : downRightY - upperLeftY;
    }

    [[nodiscard]] double area() const {
        return width() * height();
    }

    void print() const {
        std::cout << "Rectangle:(" << upperLeftX << "," << upperLeftY
                  << "), (" << downRightX << "," << downRightY << ")";
        if (isEmpty()) {
            std::cout << " Empty";
        }
        std::cout << " Area: " << area() << std::endl;
    }
};

Rectangle intersection(const Rectangle &a, const Rectangle &b) {

    double left = std::max(a.upperLeftX, b.upperLeftX);
    double top = std::max(a.upperLeftY, b.upperLeftY);
    double right = std::min(a.downRightX, b.downRightX);
    double bottom = std::min(a.downRightY, b.downRightY);

    Rectangle intersectionRect(left, top, right, bottom);

    if (intersectionRect.isEmpty()) {
        return {0, 0, 0, 0};
    }

    return intersectionRect;
}

double intersectionArea(const std::vector<Rectangle> &rectangles) {
    if (rectangles.empty()) {
        return 0.0;
    }

    Rectangle currentIntersection = rectangles[0];

    for (size_t i = 1; i < rectangles.size(); ++i) {
        currentIntersection = intersection(currentIntersection, rectangles[i]);

        if (currentIntersection.isEmpty()) {
            return 0.0;
        }
    }

    return currentIntersection.area();
}

Rectangle boundingBox(const std::vector<Rectangle> &rectangles) {
    if (rectangles.empty()) {
        return {0, 0, 0, 0};
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    bool foundValid = false;
    for (const auto &rect: rectangles) {
        if (!rect.isEmpty()) {
            minX = std::min(minX, rect.upperLeftX);
            minY = std::min(minY, rect.upperLeftY);
            maxX = std::max(maxX, rect.downRightX);
            maxY = std::max(maxY, rect.downRightY);
            foundValid = true;
        }
    }

    if (!foundValid) {
        return {0, 0, 0, 0};
    }

    return {minX, minY, maxX, maxY};
}

int main() {

    Rectangle rect1(0, 0, 5, 5);
    Rectangle rect2(2, 2, 7, 7);
    Rectangle rect3(10, 10, 15, 15);
    Rectangle rect4(2, 5, 7, 7);

    std::vector<Rectangle> rect12 = {rect1, rect2};
    std::vector<Rectangle> rect123 = {rect1, rect2, rect3};
    std::vector<Rectangle> rect1234 = {rect1, rect2, rect3, rect4};

    std::cout << intersectionArea(rect12) << std::endl;
    std::cout << intersectionArea(rect123) << std::endl;
    std::cout << intersectionArea(rect1234) << std::endl;
    Rectangle bbox = boundingBox(rect12);
    std::cout << "Минимальный ограничивающий прямоугольник: ";
    bbox.print();
}

