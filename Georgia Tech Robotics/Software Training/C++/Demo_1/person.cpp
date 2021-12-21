// person.cpp

#include <iostream>
#include "person.hpp"

Person::Person(std::string name_val, int age_val)
    : name(name_val), age(age_val)
{
    // Do extra setup steps here
}

Person::~Person()
{
    // Do cleanup steps here
}

void Person::IntroduceSelf() const
{
    std::cout << "Hello! My name is " << name << " and I am " << age << " years old.\n";
}

void Person::CelebrateBirthday(){
    ++age;
}