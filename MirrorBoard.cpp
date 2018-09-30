/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#include "MirrorBoard.h"

// default constructor
MirrorBoard::MirrorBoard()
: Board()
{
}

// variable constructor
MirrorBoard::MirrorBoard(unsigned int rows, unsigned int columns, double populationDensity)
: Board(rows, columns, populationDensity)
{
}

// copy constructor
MirrorBoard::MirrorBoard(const MirrorBoard& mirrorBoard)
: Board(mirrorBoard)
{
}

// destructor (is trivial)
MirrorBoard::~MirrorBoard()
= default;

// updates the reference board based on the regular board
void MirrorBoard::updateRefBoard()
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
        referenceBoard[0][j] = board[0][j - 1]; // first row (reference) -> first row (original)
        referenceBoard[rows + 1][j] = board[rows - 1][j - 1]; // last row (reference) -> last row (original)
    }
    // updating the vertical portion of the perimeter
    for (int i = 1; i < (rows + 1); ++i)
    {
        referenceBoard[i][0] = board[i - 1][0]; // first column (reference) -> first column (original)
        referenceBoard[i][columns + 1] = board[i - 1][columns - 1]; // last column (reference) -> last column (original)
    }
    // updating the diagonals
    referenceBoard[0][0] = board[0][0]; // top left (reference) -> top left (original)
    referenceBoard[0][columns + 1] = board[0][columns - 1]; // top right (reference) -> top right (original)
    referenceBoard[rows + 1][0] = board[rows - 1][0]; // bottom left (reference) -> bottom left (original)
    referenceBoard[rows + 1][columns + 1] = board[rows - 1][columns - 1]; // bottom right (reference) -> bottom right (original)
}
