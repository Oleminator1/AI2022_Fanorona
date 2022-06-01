//
// Created by Oliver on 18.05.2022.
// Updated by Oliver on 01.06.2022.
// Based on: https://github.com/gauravahuja/Fanorona_AI/blob/master/Fanorona/Board.h
#ifndef AI2022_FANORONA_WORLDBOARD_H
#define AI2022_FANORONA_WORLDBOARD_H

struct _Point2D {
    int x;
    int y;
};

struct _WorldBoard {
    int Rows;               // = 5
    int Columns;            // = 9
    int Matrix[5][9];       // Stores the positions of various stones
    int Chance;
};


// Initializes the Board:
void InitializeBoard(_WorldBoard &Board);

// Stores the initial positions of the BL and WH stones in the matrix
void Populate(_WorldBoard &Board);

// Gets the 2D Matrix:
void GetMatrix(_WorldBoard Board, int NewMatrix[5][9]);

// Prints the Matrix:
void PrintMatrix(_WorldBoard Board);

//Shows the Board on the Screen
void Show(_WorldBoard Board);

//Returns the Colour of Stone at (x, y)
int GetStoneColour(_WorldBoard Board, int x, int y);

//Returns the true if Stone exists at (x, y)
bool StoneExists(_WorldBoard Board, int x, int y);

//Populates the SDL Surface with images of Stones
void PopulateGUI(_WorldBoard Board, SDL_Surface *Screen);

//Returns the row and column for given mouse position
_Point2D GetSelectedPosition(_WorldBoard Board, _Point2D MousePos);

//Unselects all stones on the board
void UnselectALL(_WorldBoard &Board);

//Gets the Position selected stone
_Point2D GetSelectedStone(_WorldBoard Board, int &Colour);

//return BLACK, White of Empty for winner
int CheckWinner(_WorldBoard Board);

//returns if the row or col is on the board or not
bool IsOn(_WorldBoard Board, int xx, int yy);

//Copies OldBoard to New Board
void Copy(_WorldBoard OldBoard, _WorldBoard &NewBoard);
#endif //AI2022_FANORONA_WORLDBOARD_H



