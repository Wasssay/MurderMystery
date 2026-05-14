#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

class FileManager {
private:
    std::string userDatabaseFile;

    std::string getCurrentDateTime() {
        time_t now = time(0);
        struct tm tstruct = *localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tstruct);
        return std::string(buffer);
    }

public:
    FileManager(std::string username) {
        userDatabaseFile = username + "_database.txt";
    }

    void saveGameRecord(bool solved, int timeElapsed) {
        std::ofstream file(userDatabaseFile, std::ios::app);
        if (file.is_open()) {
            file << "Date: " << getCurrentDateTime() << "\n";
            file << "Result: " << (solved ? "Case SOLVED" : "FAILED to Solve") << "\n";
            file << "Time Taken: " << timeElapsed << " seconds\n";
            file << "-----------------------------------\n";
            file.close();
            std::cout << "\nGame saved to your personal database (" << userDatabaseFile << ").\n";
        }
        else {
            std::cout << "\nError: Could not save to your database.\n";
        }
    }

    void displayUserHistory() {
        std::ifstream file(userDatabaseFile);
        std::string line;
        std::cout << "\n===== YOUR DETECTIVE RECORD =====\n";
        if (!file.is_open()) {
            std::cout << "No past records found. This is your first case!\n";
            return;
        }
        while (getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
    }
};
