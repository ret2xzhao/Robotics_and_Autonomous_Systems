#include <iostream>
#include <vector>

class Radio {};

class Robot
{
public:
    Radio& radio_;
};

std::vector<Robot> InitializeRobots(){
    std::vector<Robot> v;
    Radio radio;
    for(int i=0; i<3; ++i){
        Robot robot{radio};
        v.push_back(robot);
    }
    return v;
}

int main()
{
    std::vector<Robot> v = InitializeRobots();

    return 0;
}

// To solve the problem for this specific example, we could do one of two things: we could shift ownership of our radio object to something that does
// outlive our robots such as the main function, we might take this radio object move it into the main function and pass it into InitializeRobots()
// as a parameter or we could leverage language features that allow for shared ownership between a collection of objects.