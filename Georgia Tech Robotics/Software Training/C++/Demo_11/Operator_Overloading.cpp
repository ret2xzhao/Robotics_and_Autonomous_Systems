#include <iostream>

struct Point {
    double x;
    double y;

    Point operator+(const Point& other) {
        Point result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }

    Point operator/(const double& scalar) {
        Point result;
        result.x = x / scalar;
        result.y = y / scalar;
        return result;
    }
};

std::ostream& operator<<(std::ostream& stream, const Point& p) {
    stream << "(" << p.x << ", " << p.y << ")";
    return stream;
}

int main() {
    Point a{0, 0};
    Point b{1, 1};
    Point mid = (a+b)/2;
    std::cout << mid << "\n";
    return 0;
}
