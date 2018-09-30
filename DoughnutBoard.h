/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#ifndef DOUGHNUTBOARD_H
#define DOUGHNUTBOARD_H

#include "Board.h"

class DoughnutBoard : public Board
{
public:

    /**
     * default constructor
     */
    DoughnutBoard();

    /**
     * variable constructor
     * @param rows - number of rows in the doughnut board
     * @param columns - number of columns in the doughnut board
     * @param populationDensity - the population density for the Game of Life
     */
    DoughnutBoard(unsigned int rows, unsigned int columns, double populationDensity);

    /**
     * copy constructor
     * @param doughnutBoard - the doughnut board to copy over
     */
    DoughnutBoard(const DoughnutBoard& doughnutBoard);

    /**
     * destructor
     */
    ~DoughnutBoard() override;

    /**
     * updates the reference board based on the regular board
     */
    void updateRefBoard() override;
};


#endif //_DOUGHNUTBOARD_H
