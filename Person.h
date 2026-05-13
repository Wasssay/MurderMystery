#pragma once
#include <iostream>
#include <string>

class Person {
protected:
    std::string name;
    int age;

public:
    Person(std::string n, int a) {
        name = n;
        age = a;
    }

    virtual void interact() {
        std::cout << name << " says hello.\n";
    }

    std::string getName() {
        return name;
    }

    virtual ~Person() {}
};
