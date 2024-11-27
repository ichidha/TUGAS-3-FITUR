#include <iostream>
#include <ncurses/ncurses.h>   
#include <unistd.h>    
#include <windows.h>   

using namespace std;

void showLoading() {
    int i = 0;
    int row, col;
    getmaxyx(stdscr, row, col);

    while (i < 3) {  
        clear();
        int centerX = (col - 7) / 2;  
        mvprintw(row / 2, centerX, "Loading");
        
        for (int j = 0; j < 5; ++j) {
            mvprintw(row / 2, centerX + 7 + j, "."); 
            refresh();
            Sleep(300);
        }
        i++;
    }
    
    int completeX = (col - 29) / 2; 
    mvprintw((row / 2) + 2, completeX, "Loading Complete! Press any key...");
    refresh();
    getch();  
}

void showIntro() {
    const char* lines[] = {
        "              _                           ",
        "__      _____| | ___ ___  _ __ ___   ___ ",
        "\\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\",
        " \\ V  V /  __/ | (_| (_) | | | | | |  __/",
        "  \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|"
    };
    int row, col;
    getmaxyx(stdscr, row, col);

    for (int i = 0; i < 5; ++i) {  
        int centerX = (col - strlen(lines[i])) / 2;
        mvprintw((row / 2 - 2) + i, centerX, "%s", lines[i]);
        refresh();
        Sleep(500);  
    }
    getch();  
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
                clear();
                mvprintw(row / 2, (col - 14) / 2, "Game saved!");
                refresh();
                Sleep(1000);
                break;
            case '3':
                clear();
                mvprintw(row / 2, (col - 29) / 2, "Exiting the game. Goodbye!");
                refresh();
                Sleep(1000);
                running = false;
                break;
            default:
                mvprintw(row / 2 + 3, (col - 26) / 2, "Invalid choice. Try again.");
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
    showMenu();     
    endwin(); 
    return 0;
}
