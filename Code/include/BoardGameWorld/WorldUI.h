//
// Created by Oliver on 18.05.2022.
// Updated by Oliver on 01.06.2022.
// Based on: https://stackoverflow.com/questions/16852978/navigating-console-menu

#include <cstdlib>
#include <iostream>

using namespace std;

#ifndef AI2022_FANORONA_WORLDUI_H
#define AI2022_FANORONA_WORLDUI_H

#endif //AI2022_FANORONA_WORLDUI_H

void menu();
void mainMenu();
int choice1 = 0;
int choice2 = 3;

void menu(){
    do {
        choice2 = 0;
        mainMenu();

        switch(choice1) {
            case 1:
                //open WorldBoard.h
                break;
            case 2:
                //open WorldBoard.h
                break;
            case 3:
                break;
        }
    } while(choice1 != 3);
}

void mainMenu(){
    cout << "Welcome to Fanorona:\n";
        cout << "Choose your Playing Style:\n";
        cout << "1 - Player VS. Player\n";
        cout << "2 - Player VS. Computer\n";
        cout << "3 - Quit Game";
}

int main(int argc, char *argv[]){
    menu();
    return 0;
}
