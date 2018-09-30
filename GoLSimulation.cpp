/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <ctime>
#include "GoLSimulation.h"
#include "Board.h"
#include "ClassicBoard.h"
#include "DoughnutBoard.h"
#include "MirrorBoard.h"

// default constructor (a doughnut board is default because doughnuts are delicious
GoLSimulation::GoLSimulation()
: board(new DoughnutBoard()), outputMethod('a')
{
}

// variable constructor
GoLSimulation::GoLSimulation(Board* board, char outputMethod)
: board(board), outputMethod(outputMethod)
{
}

// copy constructor
GoLSimulation::GoLSimulation(const GoLSimulation& goLSimulation)
: board(goLSimulation.board), outputMethod(goLSimulation.outputMethod)
{
}

// destructor
GoLSimulation::~GoLSimulation()
{
    delete board;
}

// starts the simulation
void GoLSimulation::start()
{
    switch (outputMethod)
    {
        case 'a': // automatic output method
        {
            std::cout << "Generation number: " << board->getGenerationNumber() << std::endl;
            board->printBoard();
            std::cout << std::endl;
            while (board->nextGenerationPossible())
            {
                sleep(3); // sleeps for 3 seconds
                board->nextGeneration();
                std::cout << "Generation number: " << board->getGenerationNumber() << std::endl;
                board->printBoard();
                std::cout << std::endl;
            }
            std::cout << "Simulation is empty or has stabilized." << std::endl;
            break;
        }
        case 'm': // manual output method
        {
            std::cout << "Generation number: " << board->getGenerationNumber() << std::endl;
            board->printBoard();
            std::cout << std::endl;
            while (board->nextGenerationPossible())
            {
                std::cout << "Press enter for next generation: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // enter to continue (only looks for a newline character)
                board->nextGeneration();
                std::cout << "Generation number: " << board->getGenerationNumber() << std::endl;
                board->printBoard();
                std::cout << std::endl;
            }
            std::cout << "Simulation is empty or has stabilized." << std::endl;
            break;
        }
        case 'f': // file output method
        {
            std::string outFileName;
            std::ofstream outFile;
            std::cout << "Enter a file to output the board generations to: ";
            std::cin >> outFileName;
            std::cout << std::endl;
            outFile.open(outFileName, std::ios::app);

            while (!(outFile.is_open())) // if the file can't be accessed
            {
                outFile.close();
                outFile.clear();
                std::cout << "Error opening file. Enter a file to output the board generations to: ";
                std::cin >> outFileName;
                std::cout << std::endl;
                outFile.open(outFileName, std::ios::app);
            }

            outFile << "Generation number: " << board->getGenerationNumber() << std::endl;
            board->outputBoard(outFile);
            while (board->nextGenerationPossible())
            {
                board->nextGeneration();
                outFile << "Generation number: " << board->getGenerationNumber() << std::endl;
                board->outputBoard(outFile);
            }
            outFile << "Simulation is empty or has stabilized." << std::endl;
            outFile.close();
            break;
        }
        default:
            std::cout << "Invalid output method" << std::endl;
    }
}

// sleeps the program for a specified number of seconds (allows cross platform sleep function)
void GoLSimulation::sleep(unsigned int seconds)
{
    clock_t t;
    t = clock() + (seconds * CLOCKS_PER_SEC);
    while (clock() < t)
    {
    }
}