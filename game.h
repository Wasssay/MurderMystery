#pragma once
#include <vector>
#include <limits>
#include "Room.h"
#include "Person.h"
#include "Detective.h"
#include "Victim.h"
#include "Weapon.h"
#include "FileManager.h"
#include "Suspects.h"

class Game {
private:
    std::vector<Room> rooms;
    std::vector<Person*> suspects;
    Detective detective;
    Victim victim;
    Weapon murderWeapon;
    FileManager fileManager;
    time_t startTime;

public:
    Game(std::string detectiveName)
        : detective(detectiveName, 30),
        victim("Lord Blackwood", 60),
        murderWeapon("Silver Dagger"),
        fileManager(detectiveName) {
        startTime = time(0);
    }

    void setupGame() {
        Room library("Library");
        library.addClue(Clue("A torn diary page mentioning betrayal."));
        library.addClue(Clue("Footprints near the bookshelf."));

        Room kitchen("Kitchen");
        kitchen.addClue(Clue("A bloody knife missing from the rack."));
        kitchen.addClue(Clue("Broken wine glass on the floor."));

        Room bedroom("Master Bedroom");
        bedroom.addClue(Clue("A secret letter hidden under the bed."));
        bedroom.addClue(Clue("A black glove covered in dust."));

        Room garden("Garden");
        garden.addClue(Clue("Fresh muddy footprints."));
        garden.addClue(Clue("A torn piece of red fabric."));

        rooms.push_back(library);
        rooms.push_back(kitchen);
        rooms.push_back(bedroom);
        rooms.push_back(garden);

        suspects.push_back(new CalmSuspect("Miss Scarlet", 28, "I was reading in the library.", false));
        suspects.push_back(new NervousSuspect("Professor Moriarty", 45, "I was in the garden all evening!", true));
        suspects.push_back(new CalmSuspect("Dr. Watson", 40, "I was preparing medicine.", false));
        suspects.push_back(new NervousSuspect("Lady Catherine", 35, "I heard a scream from upstairs.", false));
    }

    void exploreRooms() {
        for (auto r : rooms) {
            r.exploreRoom();
        }
    }

    void talkToSuspects() {
        std::cout << "\n===== TALKING TO SUSPECTS =====\n";
        for (auto s : suspects) {
            s->interact();
        }
    }

    void showWeapon() {
        std::cout << "\n===== MURDER WEAPON =====\n";
        murderWeapon.showWeapon();
    }

    void accuseSuspect() {
        std::cout << "\n===== FINAL ACCUSATION =====\n";
        for (size_t i = 0; i < suspects.size(); i++) {
            std::cout << i + 1 << ". " << suspects[i]->getName() << "\n";
        }

        int choice;
        std::cout << "\nChoose suspect number: ";
        std::cin >> choice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        choice--;

        if (choice < 0 || choice >= suspects.size()) {
            std::cout << "\nInvalid choice!\n";
            return;
        }

        Suspect* s = dynamic_cast<Suspect*>(suspects[choice]);
        bool solved = false;

        if (s && s->isGuilty()) {
            std::cout << "\nCorrect! You solved the murder mystery.\n";
            solved = true;
        }
        else {
            std::cout << "\nWrong accusation! The real killer escaped.\n";
        }

        time_t endTime = time(0);
        int timeElapsed = static_cast<int>(difftime(endTime, startTime));

        fileManager.saveGameRecord(solved, timeElapsed);
    }

    void startGame() {
        int choice;
        bool gameActive = true;

        do {
            std::cout << "\n========== MENU ==========\n";
            std::cout << "1. Explore Rooms\n";
            std::cout << "2. Talk To Suspects\n";
            std::cout << "3. View Murder Weapon\n";
            std::cout << "4. Show Detective Notebook\n";
            std::cout << "5. Make Final Accusation\n";
            std::cout << "6. View Your Past Records\n";
            std::cout << "7. Exit Game\n";

            std::cout << "\nEnter Choice: ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = 0;
            }

            switch (choice) {
            case 1: exploreRooms(); break;
            case 2: talkToSuspects(); break;
            case 3: showWeapon(); break;
            case 4: detective.showNotebook(); break;
            case 5: accuseSuspect(); gameActive = false; break;
            case 6: fileManager.displayUserHistory(); break;
            case 7: std::cout << "\nExiting Game...\n"; gameActive = false; break;
            default: std::cout << "\nInvalid Choice! Please enter a number from 1 to 7.\n";
            }
        } while (gameActive);
    }

    ~Game() {
        for (auto s : suspects) {
            delete s;
        }
    }
};