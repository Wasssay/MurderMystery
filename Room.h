#pragma once
#include <vector>
#include "Clue.h"

class Room {
private:
    std::string roomName;
    std::vector<Clue> clues;

public:
    Room(std::string rn) {
        roomName = rn;
    }

    void addClue(Clue c) {
        clues.push_back(c);
    }

    void exploreRoom() {
        std::cout << "\n===== EXPLORING ROOMS =====\n";
        std::cout << "Room: " << roomName << "\n";
        if (clues.empty()) {
            std::cout << "No clues found here.\n";
        }
        else {
            for (auto c : clues) {
                c.showClue();
            }
        }
    }

    std::string getRoomName() {
        return roomName;
    }
};