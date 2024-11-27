#include <iostream>
#include <fstream>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <windows.h>
#include <string>

using namespace std;

string currentUser = "";  

void showLoading(){}

void showIntro(){}


void loadingBeforeLogin() {
    int row, col;
    getmaxyx(stdscr, row, col);

    const char* messages[] = {
        "Preparing login...",
        "Checking security...",
        "Loading user data...",
        "Almost ready!"
    };

    for (int i = 0; i < 4; ++i) {
        clear();
        int centerX = (col - strlen(messages[i])) / 2;
        mvprintw(row / 2, centerX, "%s", messages[i]);
        refresh();
        Sleep(800);  
    }
}


void showWelcome() {
    int row, col;
    getmaxyx(stdscr, row, col);
    
    const char* welcomeMsg = "Welcome to the Game!";
    
    for (int i = 0; i < 3; ++i) {  
        clear();
        refresh();
        Sleep(500);
        mvprintw(row / 2, (col - strlen(welcomeMsg)) / 2, welcomeMsg);
        refresh();
        Sleep(500);
    }
}


bool login() {
    string username, password, storedUser, storedPass;
    bool success = false;

    clear();
    mvprintw(5, 10, "=== Login ===");
    mvprintw(7, 10, "Username: ");
    echo();  
    char uname[50];
    getstr(uname);
    username = uname;

    mvprintw(8, 10, "Password: ");
    echo();  
    char pass[50];
    getstr(pass);
    password = pass;

    ifstream userFile("users.txt");
    while (userFile >> storedUser >> storedPass) {
        if (username == storedUser && password == storedPass) {
            success = true;
            currentUser = username;
            break;
        }
    }
    userFile.close();

    if (success) {
        mvprintw(10, 10, "Login successful! Welcome, %s", username.c_str());
    } else {
        mvprintw(10, 10, "Login failed! Check your username and password.");
    }
    refresh();
    Sleep(2000);
    return success;
}


void registerUser() {
    string username, password;
    clear();
    mvprintw(5, 10, "=== Register ===");
    mvprintw(7, 10, "Enter username: ");
    echo();
    char uname[50];
    getstr(uname);
    username = uname;

    mvprintw(8, 10, "Enter password: ");
    echo();
    char pass[50];
    getstr(pass);
    password = pass;

    ofstream userFile("users.txt", ios::app); 
    userFile << username << " " << password << endl;
    userFile.close();

    mvprintw(10, 10, "Registration successful!");
    refresh();
    Sleep(2000);
}


void saveGame() {
    if (currentUser.empty()) {
        mvprintw(10, 10, "Please login first to save!");
        refresh();
        Sleep(2000);
        return;
    }

    ofstream saveFile(currentUser + "_save.txt");
    saveFile << "Game data for user: " << currentUser << endl;
    saveFile << "Progress: 50% Complete" << endl;  
    saveFile.close();

    mvprintw(10, 10, "Game saved successfully for %s!", currentUser.c_str());
    refresh();
    Sleep(2000);
}

void showMenu() {
    int choice;
    bool running = true;
    int row, col;

    getmaxyx(stdscr, row, col);

    while (running) {
        clear();
        mvprintw(row / 2 - 3, (col - 19) / 2, "===== Game Menu =====");
        mvprintw(row / 2 - 1, (col - 7) / 2, "1. Play");
        mvprintw(row / 2, (col - 7) / 2, "2. Save");
        mvprintw(row / 2 + 1, (col - 7) / 2, "3. Quit");

        refresh();
        choice = getch();

        switch (choice) {
            case '1':
                clear();
                mvprintw(row / 2, (col - 21) / 2, "Starting the game...");
                refresh();
                Sleep(1000);
                break;
            case '2':
                saveGame();  
                break;
            case '3':
                clear();
                mvprintw(row / 2, (col - 29) / 2, "Exiting the game. Thank you!");
                refresh();
                Sleep(1000);
                running = false;
                break;
            default:
                mvprintw(row / 2 + 3, (col - 26) / 2, "Invalid choice. Try again!");
                refresh();
                Sleep(1000);
                break;
        }
    }
}

int main() {
    initscr();
    noecho();
    curs_set(0);

    showLoading();
    showIntro();

    
    bool loggedIn = false;
    while (!loggedIn) {
        loadingBeforeLogin();  
        clear();
        mvprintw(5, 10, "1. Register");
        mvprintw(6, 10, "2. Login");
        refresh();

        int choice = getch();
        if (choice == '1') {
            registerUser();  
        } else if (choice == '2') {
        	loggedIn = login();
            if (loggedIn) showWelcome();
            
        }
    }

    showMenu();
    endwin();
    return 0;
}
