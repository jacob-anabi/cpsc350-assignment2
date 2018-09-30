/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#include "DoughnutBoard.h"

// default constructor
DoughnutBoard::DoughnutBoard()
: Board()
{
}

// variable constructor
DoughnutBoard::DoughnutBoard(unsigned int rows, unsigned int columns, double populationDensity)
: Board(rows, columns, populationDensity)
{
}

// copy constructor
DoughnutBoard::DoughnutBoard(const DoughnutBoard& doughnutBoard)
: Board(doughnutBoard)
{
}

// destructor (is trivial)
DoughnutBoard::~DoughnutBoard()
= default;

// updates the reference board based on the regular board
void DoughnutBoard::updateRefBoard()
{
    // updating the inner portion (not perimeter) of the reference board
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            referenceBoard[i + 1][j + 1] = board[i][j];
        }
    }

    // updating the perimeter of the reference board

    // updating the horizontal portion of the perimeter
    for (int j = 1; j < (columns + 1); ++j)
    {
        referenceBoard[0][j] = board[rows - 1][j - 1]; // first row (reference) -> last row (original)
        referenceBoard[rows + 1][j] = board[0][j - 1]; // last row (reference) -> first row (original)
    }
    // updating the vertical portion of the perimeter
    for (int i = 1; i < (rows + 1); ++i)
    {
        referenceBoard[i][0] = board[i - 1][columns - 1]; // first column (reference) -> last column (original)
        referenceBoard[i][columns + 1] = board[i - 1][0]; // last column (reference) -> first column (original)
    }
    // updating the diagonals
    referenceBoard[0][0] = board[rows - 1][columns - 1]; // top left (reference) -> bottom right (original)
    referenceBoard[0][columns + 1] = board[rows - 1][0]; // top right (reference) -> bottom left (original)
    referenceBoard[rows + 1][0] = board[0][columns - 1]; // bottom left (reference) -> top right (original)
    referenceBoard[rows + 1][columns + 1] = board[0][0]; // bottom right (reference) -> top left (original)
}