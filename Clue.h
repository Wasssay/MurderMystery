#pragma once
#include <iostream>
#include <string>

class Clue {
private:
    std::string description;

public:
    Clue(std::string d) {
        description = d;
    }

    void showClue() {
        std::cout << "- " << description << "\n";
    }

    std::string getDescription() {
        return description;
    }
};