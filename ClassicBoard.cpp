/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#include "ClassicBoard.h"

// default constructor
ClassicBoard::ClassicBoard()
: Board()
{
}

// variable constructor
ClassicBoard::ClassicBoard(unsigned int rows, unsigned int columns, double populationDensity)
: Board(rows, columns, populationDensity)
{
}

// copy constructor
ClassicBoard::ClassicBoard(const ClassicBoard& classicBoard)
: Board(classicBoard)
{
}

// destructor (is trivial)
ClassicBoard::~ClassicBoard()
= default;

// updates the reference board based on the regular board
void ClassicBoard::updateRefBoard()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            referenceBoard[i + 1][j + 1] = board[i][j];
        }
    }
}