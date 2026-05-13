#pragma once
#include <iostream>
#include <string>

class Weapon {
private:
    std::string weaponName;

public:
    Weapon(std::string wn) {
        weaponName = wn;
    }

    void showWeapon() {
        std::cout << "Weapon Found: " << weaponName << "\n";
    }
};