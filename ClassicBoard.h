/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#ifndef CLASSICBOARD_H
#define CLASSICBOARD_H

#include "Board.h"

class ClassicBoard : public Board
{
public:

    /**
     * default constructor
     */
    ClassicBoard();

    /**
     * variable constructor
     * @param row - number of rows in the classic board
     * @param column - number of columns in the classic board
     * @param populationDensity - the population density for the Game of Life
     */
    ClassicBoard(unsigned int rows, unsigned int columns, double populationDensity);

    /**
     * copy constructor
     * @param classicBoard - the classic board to copy over
     */
    ClassicBoard(const ClassicBoard& classicBoard);

    /**
     * destructor
     * NOTE: trivial
     */
    ~ClassicBoard() override;

    /**
     * updates the reference board based on the regular board
     */
    void updateRefBoard() override;
};

#endif // CLASSICBOARD_H