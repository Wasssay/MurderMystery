#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>
#include <limits>
#include "Game.h"

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

int main() {
    showTitle();
    string detectiveName = welcomeDetective();

    Game game(detectiveName);
    game.setupGame();
    game.startGame();

    return 0;
}