/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "Board.h"
#include "ClassicBoard.h"
#include "DoughnutBoard.h"
#include "MirrorBoard.h"


class GoLSimulation
{
public:

    /**
     * default constructor
     */
    GoLSimulation();

    /**
     * variable constructor
     * @param board - the board to use in the simulation
     * @param outputMethod - the method the user wants for output ('a' = automatic, 'm' = manual, 'f' = file)
     */
    GoLSimulation(Board* board, char outputMethod);

    /**
     * copy constructor
     * @param simulation - the simulation to copy over
     */
    GoLSimulation(const GoLSimulation& goLSimulation);

    /**
     * destructor
     */
    ~GoLSimulation();

    /**
     * starts the simulation
     */
    void start();

    /**
     * sleeps the program for a specified number of seconds
     * @param seconds - the amount of seconds to sleep for
     */
    void sleep(unsigned int seconds);

private:
    Board* board;
    char outputMethod;
};


#endif // SIMULATION_H
