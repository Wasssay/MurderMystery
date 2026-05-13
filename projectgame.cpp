#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#include <limits> 

using namespace std;

void showTitle() {
    cout << "\n\n";
    cout << "\t\t\t\t================================\n";
    cout << "\t\t\t\t      MURDER MYSTERY GAME\n";
    cout << "\t\t\t\t================================\n\n";
}

string welcomeDetective() {
    string name;

    cout << "Welcome, Detective!\n";
    cout << "Enter your first name: ";
    cin >> name;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nGood luck Detective " << name << "!\n";
    cout << "A murder has taken place inside Blackwood Mansion.\n";
    cout << "Find clues, question suspects, and solve the mystery.\n\n";

    return name;
}

// BASE CLASS 
class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) {
        name = n;
        age = a;
    }

    virtual void interact() {
        cout << name << " says hello.\n";
    }

    string getName() {
        return name;
    }

    virtual ~Person() {}
};

// CLUE CLASS 
class Clue {
private:
    string description;

public:
    Clue(string d) {
        description = d;
    }

    void showClue() {
        cout << "- " << description << endl;
    }

    string getDescription() {
        return description;
    }
};

// ROOM CLASS
class Room {
private:
    string roomName;
    vector<Clue> clues;

public:
    Room(string rn) {
        roomName = rn;
    }

    void addClue(Clue c) {
        clues.push_back(c);
    }

    void exploreRoom() {
        cout << "\n===== EXPLORING ROOMS =====\n";
        cout << "Room: " << roomName << endl;
        if (clues.empty()) {
            cout << "No clues found here.\n";
        }
        else {
            for (auto c : clues) {
                c.showClue();
            }
        }
    }

    string getRoomName() {
        return roomName;
    }
};

// WEAPON CLASS 
class Weapon {
private:
    string weaponName;

public:
    Weapon(string wn) {
        weaponName = wn;
    }

    void showWeapon() {
        cout << "Weapon Found: " << weaponName << endl;
    }
};

// VICTIM CLASS 
class Victim : public Person {
public:
    Victim(string n, int a) : Person(n, a) {}

    void interact() override {
        cout << "The victim can no longer speak.\n";
    }
};

// DETECTIVE CLASS 
class Detective : public Person {
private:
    vector<Clue> notebook;

public:
    Detective(string n, int a) : Person(n, a) {}

    void collectClue(Clue c) {
        notebook.push_back(c);
    }

    void showNotebook() {
        cout << "\n===== DETECTIVE NOTEBOOK =====\n";
        if (notebook.empty()) {
            cout << "No clues collected yet.\n";
        }
        else {
            cout << "Clues saved!" << endl;
            for (auto c : notebook) {
                c.showClue();
            }
        }
    }

    void interact() override {
        cout << "Detective " << name << " is investigating the case.\n";
    }
};

// SUSPECT CLASS 
class Suspect : public Person {
protected:
    string alibi;
    bool guilty;

public:
    Suspect(string n, int a, string al, bool g)
        : Person(n, a) {
        alibi = al;
        guilty = g;
    }

    virtual void interact() override {
        cout << name << ": " << alibi << endl;
    }

    bool isGuilty() {
        return guilty;
    }
};

// NERVOUS SUSPECT 
class NervousSuspect : public Suspect {
public:
    NervousSuspect(string n, int a, string al, bool g)
        : Suspect(n, a, al, g) {
    }

    void interact() override {
        cout << name << " looks nervous and says: " << alibi << endl;
    }
};

// CALM SUSPECT 
class CalmSuspect : public Suspect {
public:
    CalmSuspect(string n, int a, string al, bool g)
        : Suspect(n, a, al, g) {
    }

    void interact() override {
        cout << name << " calmly says: " << alibi << endl;
    }
};

// SIMPLE PER-USER FILE MANAGER CLASS 
class FileManager {
private:
    string userDatabaseFile;

    string getCurrentDateTime() {
        time_t now = time(0);
        struct tm tstruct = *localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tstruct);
        return string(buffer);
    }

public:
    FileManager(string username) {
        userDatabaseFile = username + "_database.txt";
    }

    void saveGameRecord(bool solved, int timeElapsed) {
        ofstream file(userDatabaseFile, ios::app);

        if (file.is_open()) {
            file << "Date: " << getCurrentDateTime() << endl;
            file << "Result: " << (solved ? "Case SOLVED" : "FAILED to Solve") << endl;
            file << "Time Taken: " << timeElapsed << " seconds" << endl;
            file << "-----------------------------------" << endl;
            file.close();
            cout << "\nGame saved to your personal database (" << userDatabaseFile << ").\n";
        }
        else {
            cout << "\nError: Could not save to your database.\n";
        }
    }

    void displayUserHistory() {
        ifstream file(userDatabaseFile);
        string line;

        cout << "\n===== YOUR DETECTIVE RECORD =====\n";

        if (!file.is_open()) {
            cout << "No past records found. This is your first case!\n";
            return;
        }

        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

// GAME CLASS 
class Game {
private:
    vector<Room> rooms;
    vector<Person*> suspects;
    Detective detective;
    Victim victim;
    Weapon murderWeapon;
    FileManager fileManager;
    time_t startTime;

public:
    Game(string detectiveName)
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
        cout << "\n===== TALKING TO SUSPECTS =====\n";
        for (auto s : suspects) {
            s->interact();
        }
    }

    void showWeapon() {
        cout << "\n===== MURDER WEAPON =====\n";
        murderWeapon.showWeapon();
    }

    void accuseSuspect() {
        cout << "\n===== FINAL ACCUSATION =====\n";
        for (int i = 0; i < suspects.size(); i++) {
            cout << i + 1 << ". " << suspects[i]->getName() << endl;
        }

        int choice;
        cout << "\nChoose suspect number: ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        choice--;

        if (choice < 0 || choice >= suspects.size()) {
            cout << "\nInvalid choice!\n";
            return;
        }

        Suspect* s = dynamic_cast<Suspect*>(suspects[choice]);
        bool solved = false;

        if (s && s->isGuilty()) {
            cout << "\nCorrect! You solved the murder mystery.\n";
            solved = true;
        }
        else {
            cout << "\nWrong accusation! The real killer escaped.\n";
        }

        time_t endTime = time(0);
        int timeElapsed = static_cast<int>(difftime(endTime, startTime));

        fileManager.saveGameRecord(solved, timeElapsed);
    }

    void startGame() {
        int choice;
        bool gameActive = true;

        do {
            cout << "\n========== MENU ==========\n";
            cout << "1. Explore Rooms\n";
            cout << "2. Talk To Suspects\n";
            cout << "3. View Murder Weapon\n";
            cout << "4. Show Detective Notebook\n";
            cout << "5. Make Final Accusation\n";
            cout << "6. View Your Past Records\n";
            cout << "7. Exit Game\n";

            cout << "\nEnter Choice: ";

            if (!(cin >> choice)) {
                // If the user types a letter instead of a number, reset the input system
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = 0;
            }

            switch (choice) {
            case 1: exploreRooms(); break;
            case 2: talkToSuspects(); break;
            case 3: showWeapon(); break;
            case 4: detective.showNotebook(); break;
            case 5: accuseSuspect(); gameActive = false; break;
            case 6: fileManager.displayUserHistory(); break;
            case 7: cout << "\nExiting Game...\n"; gameActive = false; break;
            default: cout << "\nInvalid Choice! Please enter a number from 1 to 7.\n";
            }
        } while (gameActive);
    }
    ~Game() {
        for (auto s : suspects) {
            delete s;
        }
    }
};
int main() {
    showTitle();
    string detectiveName = welcomeDetective();
    Game game(detectiveName);
    game.setupGame();
    game.startGame();
    return 0;
}