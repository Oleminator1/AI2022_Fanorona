//
// Created by Olive on 01.06.2022.
//
#include "WorldUI.h"

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
}