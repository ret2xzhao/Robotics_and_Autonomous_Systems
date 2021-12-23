#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

struct Shape {
    virtual double Area() const = 0;
};

struct Circle : public Shape{
    double radius = 1.0;
    double Area() const override{
        return M_PI * radius * radius;
    }
};

struct Square : public Shape{
    double width  = 1.0;
    double height = 1.0;
    double Area() const override{
        return width * height;
    }
};

struct Triangle : public Shape{
    double width  = 1.0;
    double height = 1.0;
    double Area() const override{
        return 0.5 * width * height;
    }
};

void PrintArea(const Shape& s){
    std::cout << s.Area() << "\n";
}

int main() {
    Circle c;
    Shape& s = c;
    std::cout << s.Area() << "\n";

    Triangle t;
    PrintArea(t);

    std::cout << "--------" << "\n";
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Square>());
    shapes.push_back(std::make_unique<Triangle>());

    for(const auto&sh: shapes){
        PrintArea(*sh);
    }
    return 0;
}