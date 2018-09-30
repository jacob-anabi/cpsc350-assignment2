/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#ifndef MIRRORBOARD_H
#define MIRRORBOARD_H

#include "Board.h"

class MirrorBoard : public Board
{
public:

    /**
     * default constructor
     */
    MirrorBoard();

    /**
     * variable constructor
     * @param rows - number of rows in the mirror board
     * @param columns - number of columns in the mirror board
     * @param populationDensity - the population density for the Game of Life
     */
    MirrorBoard(unsigned int rows, unsigned int columns, double populationDensity);

    /**
     * copy constructor
     * @param mirrorBoard - the mirror board to copy over
     */
    MirrorBoard(const MirrorBoard& mirrorBoard);

    /**
     * destructor
     * NOTE: trivial
     */
    ~MirrorBoard() override;

    /**
     * updates the reference board based on the regular board
     */
    void updateRefBoard() override;
};


#endif // MIRRORBOARD_H
