#pragma once

#include <vector>

enum Direction
{
    UpperRight = 1,
    Right = 2,
    LowerRight = 3,
    Bottom = 4,
    LowerLeft = 5,
    Left = 6,
    UpperLeft = 7,
    Top = 8,
    Invalid = -1
};

struct Position
{
    int row;
    int col;
};

struct Movement
{
    Position from;
    Position to;
    bool isCapturing;
    bool attackType;
};
struct Move
{
    int player;
    std::vector<Movement> movements;
};