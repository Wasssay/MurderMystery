#pragma once
#include "Person.h"

class Victim : public Person {
public:
    Victim(std::string n, int a) : Person(n, a) {}

    void interact() override {
        std::cout << "The victim can no longer speak.\n";
    }
};
