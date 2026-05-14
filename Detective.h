#pragma once
#include <vector>
#include "Person.h"
#include "Clue.h"

class Detective : public Person {
private:
    std::vector<Clue> notebook;

public:
    Detective(std::string n, int a) : Person(n, a) {}

    void collectClue(Clue c) {
        notebook.push_back(c);
    }

    void showNotebook() {
        std::cout << "\n===== DETECTIVE NOTEBOOK =====\n";
        if (notebook.empty()) {
            std::cout << "No clues collected yet.\n";
        }
        else {
            std::cout << "Clues saved!\n";
            for (auto c : notebook) {
                c.showClue();
            }
        }
    }

    void interact() override {
        std::cout << "Detective " << name << " is investigating the case.\n";
    }
};
