#pragma once
#include "Person.h"

class Suspect : public Person {
protected:
    std::string alibi;
    bool guilty;

public:
    Suspect(std::string n, int a, std::string al, bool g)
        : Person(n, a) {
        alibi = al;
        guilty = g;
    }

    virtual void interact() override {
        std::cout << name << ": " << alibi << "\n";
    }

    bool isGuilty() {
        return guilty;
    }
};

class NervousSuspect : public Suspect {
public:
    NervousSuspect(std::string n, int a, std::string al, bool g)
        : Suspect(n, a, al, g) {
    }

    void interact() override {
        std::cout << name << " looks nervous and says: " << alibi << "\n";
    }
};

class CalmSuspect : public Suspect {
public:
    CalmSuspect(std::string n, int a, std::string al, bool g)
        : Suspect(n, a, al, g) {
    }

    void interact() override {
        std::cout << name << " calmly says: " << alibi << "\n";
    }
};