// person.hpp

#include <string>

class Person
{
public:
    Person(std::string name_val, int age_val);
    ~Person();
    void IntroduceSelf() const;
    void CelebrateBirthday();

private:
    std::string name = "Jane Doe";
    int age = 0;
};