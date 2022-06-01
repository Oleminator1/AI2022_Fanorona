//
// Created by Oliver on 18.05.2022.
// Updated by Oliver on 01.06.2022.
// Based on: https://stackoverflow.com/questions/16852978/navigating-console-menu

#include <cstdlib>
#include <iostream>
#include "WorldBoard.h"
using namespace std;

#ifndef AI2022_FANORONA_WORLDUI_H
#define AI2022_FANORONA_WORLDUI_H

#endif //AI2022_FANORONA_WORLDUI_H

void menu();
void mainMenu();

int GetInput(){
    int choice;
    cin >> choice;
    return choice;
}
void mainMenu(){
    cout << "Welcome to Fanorona:\n";
    cout << "Choose your Playing Style:\n";
    cout << "1 - Player VS. Player\n";
    cout << "2 - Player VS. Computer\n";
    cout << "3 - Computer Vs. Computer\n";
    cout << "4 - Quit Game\n";
}

void menu(){
    int choice = 0;

    do {
        system("cls");
        mainMenu();
        choice = GetInput();
        switch(choice) {
            case 1:
                //open WorldBoard.h
                wboard();
                break;
            case 2:
                //Open WorldBoard.h
                wboard();
                //Open AI Vs. Player
                break;
            case 3:
                //Open WorldBoard.h
                wboard();
                //open AI Vs. AI
                break;
            case 4:
                break;
        }
    } while(choice != 4);
    system("Pause");
}

