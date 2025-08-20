//Ghulam Mustafa
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

const string USER_DIR = "users/";

string simpleHash(const string& password) {
    string hashed = password;
    reverse(hashed.begin(), hashed.end());
    return hashed;
}

bool isValidInput(const string& username, const string& password, string& message) {
    if (username.empty() || password.empty()) {
        message = "Username and password cannot be empty.";
        return false;
    }
    if (username.length() < 3 || password.length() < 6) {
        message = "Username must be at least 3 characters, password at least 6 characters.";
        return false;
    }
    return true;
}

string getUserFilePath(const string& username) {
    return USER_DIR + username + ".txt";
}

string registerUser(const string& username, const string& password) {
    string msg;
    if (!isValidInput(username, password, msg)) {
        return "Registration failed: " + msg;
    }

    fs::create_directory(USER_DIR);

    string filePath = getUserFilePath(username);
    if (fs::exists(filePath)) {
        return "Registration failed: Username already exists.";
    }

    ofstream outFile(filePath);
    outFile << simpleHash(password);
    outFile.close();

    return "Registration successful!";
}

string loginUser(const string& username, const string& password) {
    string filePath = getUserFilePath(username);
    if (!fs::exists(filePath)) {
        return "Login failed: Username not found.";
    }

    ifstream inFile(filePath);
    string storedHash;
    getline(inFile, storedHash);
    inFile.close();

    if (storedHash == simpleHash(password)) {
        return "Login successful!";
    } else {
        return "Login failed: Incorrect password.";
    }
}

int main() {
    string action, username, password;

    while (true) {
        cout << "\nChoose action:  ";
        cout << "\n  1.Register ";
        cout << "\n  2.Login ";
        cout << "\n  3.Exit: ";
        cin >> action;

        if (action == "exit") break;

        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (action == "register") {
            cout << registerUser(username, password) << endl;
        } else if (action == "login") {
            cout << loginUser(username, password) << endl;
        } else {
            cout << "Invalid action." << endl;
        }
    }

    return 0;
}