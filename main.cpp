/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#include <iostream>
#include <string>
#include <limits>
#include "GoLSimulation.h"
#include "Board.h"
#include "ClassicBoard.h"
#include "DoughnutBoard.h"
#include "MirrorBoard.h"
#include "MapFileMismatchException.h"

int main(int argc, char** argv)
{
    srand(static_cast<unsigned int>(time(nullptr))); // generating a seed for rand() so each time the program is run, rand() will produce 'random' numbers

    GoLSimulation* goLSimulation;
    Board* board;
    std::string infoPref;
    std::string modePref;
    char outputPref;

    int rows = 0;
    int columns = 0;
    double populationDensity = 1.0;

    std::cout << "Hello, welcome to the Game of Life!" << std::endl;
    std::cout << "Before we begin, let's set your preferences." << std::endl;
    std::cout << "(type 'h' anytime during this set up stage, for a description of each option)" << std::endl;

    // information preferences
    std::cout << "Would you like to manually enter the board information ('1') or pass in a map file ('2')? ";
    std::cin >> infoPref;
    while ((infoPref != "1") && (infoPref != "2"))
    {
        if (infoPref == "h")
        {
            std::cout << "Help section for information preferences:" << "\n"
            << "('1'): Manually enter row number (r > 0), column number (c > 0), and population density (0 < p <= 1)" << "\n"
            << "('2'): Pass in a map file, with the first line being the row number (r > 0), the second line being the column number (c > 0), "
               "and the subsequent lines representing the board you want to use ('X' represents an alive occupied cell, whilst '-' represents an empty cell" << std::endl;
            infoPref = "";
        }
        else if (infoPref.empty())
        {
            std::cout << "Would you like to manually enter the board information ('1') or pass in a map file ('2')? ";
            std::cin >> infoPref;
        }
        else
        {
            std::cout << "Invalid option! Try again." << std::endl;
            std::cout << "Would you like to manually enter the board information ('1') or pass in a map file ('2')? ";
            std::cin >> infoPref;
        }
    }
    std::cout << "Awesome! You chose option " << infoPref << "." << std::endl;

    // output preferences
    std::cout << "Would you like automatic output ('a'), manual output ('m'), or file output ('f')? ";
    std::cin >> outputPref;
    while ((outputPref != 'a') && (outputPref != 'm') && (outputPref != 'f'))
    {
        if (outputPref == 'h')
        {
            std::cout << "Help section for output preferences" << "\n"
            << "('a'): Each generation is outputted automatically, with a 3 second delay between each output" << "\n"
            << "('m'): Each generation is outputted manually, through a press of the 'Enter' button" << "\n"
            << "('f'): Each generation is outputted to a file, by appending it to the file" << std::endl;
            outputPref = ' ';
        }
        else if (outputPref == ' ')
        {
            std::cout << "Would you like automatic output ('a'), manual output ('m'), or file output ('f')? ";
            std::cin >> outputPref;
        }
        else
        {
            std::cout << "Invalid option! Try again." << std::endl;
            std::cout << "Would you like automatic output ('a'), manual output ('m'), or file output ('f')? ";
            std::cin >> outputPref;
        }
    }
    std::cout << "Awesome! You chose option " << outputPref << "." << std::endl;

    // output preferences
    std::cout << "Would you like Classic Mode ('c'), Doughnut Mode ('d'), or Mirror Mode ('m')? ";
    std::cin >> modePref;
    while ((modePref != "c") && (modePref != "d") && (modePref != "m"))
    {
        if (modePref == "h")
        {
            std::cout << "Help section for mode preferences" << "\n"
                      << "('c'): All locations off the board are considered to be empty." << "\n"
                      << "('d'): The board is wrapped around itself horizontally and vertically, resulting\n"
                         "in a torus (doughnut) shape.  In this mode, any reference off the right-hand-side is \n"
                         "wrapped around to the left-most column of the same row and vice-versa.  Any reference \n"
                         "off the top wraps to the bottom in the same column." << "\n"
                      << "('m'): References off the board are bounced back as though the wall were a mirror. \n"
                         "This means the reflection of a cell could count as its own neighbor. For a corner cell, if it was \n"
                         "occupied, its reflection would count as 3 neighbors...1 for the vertical reflection, l for the \n"
                         "horizontal reflection, and 1 for the diagonal reflection." << std::endl;
            modePref = "";
        }
        else if (modePref.empty())
        {
            std::cout << "Would you like Classic Mode ('c'), Doughnut Mode ('d'), or Mirror Mode ('m')? ";
            std::cin >> modePref;
        }
        else
        {
            std::cout << "Invalid option! Try again." << std::endl;
            std::cout << "Would you like Classic Mode ('c'), Doughnut Mode ('d'), or Mirror Mode ('m')? ";
            std::cin >> modePref;
        }
    }
    std::cout << "Awesome! You chose option " << modePref << "." << std::endl;

    if (infoPref == "1")
    {
        // rows
        std::cout << "Enter a number of rows (r > 0, if r <= 0, r = 1): ";
        std::cin >> rows;
        while (!(std::cin)) // if they don't enter a positive int
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // meed to flush out the new line
            std::cout << "Enter a valid number of rows (r > 0, if r <= 0, r = 1): ";
            std::cin >> rows;
        }
        if (rows <= 0)
        {
            rows = 1;
        }

        // columns
        std::cout << "Enter a number of columns (c > 0, if c <= 0, c = 1): ";
        std::cin >> columns;
        while (!(std::cin)) // if they don't enter a positive int
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // meed to flush out the new line
            std::cout << "Enter a valid number of columns (c > 0, if c <= 0, c = 1): ";
            std::cin >> columns;
        }
        if (columns <= 0)
        {
            columns = 1;
        }

        // poulation density
        std::cout << "Enter a population density (0 < p <= 1, if p <= 0 or p > 1, p = 1): ";
        std::cin >> populationDensity;
        while (!(std::cin)) // if they don't enter a positive int
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // meed to flush out the new line
            std::cout << "Enter a valid population density (0 < p <= 1, if p <= 0 or p > 1, p = 1): ";
            std::cin >> populationDensity;
        }
        if ((populationDensity <= 0) || (populationDensity > 1))
        {
            populationDensity = 1;
        }

        // creating boards based on mode preference
        if (modePref == "c")
        {
            board = new ClassicBoard(static_cast<unsigned int>(rows), static_cast<unsigned int>(columns), populationDensity);
        }
        else if (modePref == "d")
        {
            board = new DoughnutBoard(static_cast<unsigned int>(rows), static_cast<unsigned int>(columns), populationDensity);
        }
        else if (modePref == "m")
        {
            board = new MirrorBoard(static_cast<unsigned int>(rows), static_cast<unsigned int>(columns), populationDensity);
        }
        else
        {
            board = new DoughnutBoard();
        }

        goLSimulation = new GoLSimulation(board, outputPref);
        goLSimulation->start();
    }
    else if (infoPref == "2")
    {
        std::string inFileName;
        std::ifstream inFile;

        std::cout << "Enter the file name: ";
        std::cin >> inFileName;

        inFile.open(inFileName);

        while (!(inFile)) // if the map file is invalid
        {
            inFile.close();
            inFile.clear();
            std::cout << "Invalid file name! Try again." << std::endl;
            std::cout << "Enter the file name: ";
            std::cin >> inFileName;
            inFile.open(inFileName);
        }

        // creating boards based on mode preference
        if (modePref == "c")
        {
            board = new ClassicBoard();
        }
        else if (modePref == "d")
        {
            board = new DoughnutBoard();

        }
        else if (modePref == "m")
        {
            board = new MirrorBoard();
        }
        else
        {
            board = new DoughnutBoard();
        }

        try
        {
            board->fileConstruct(inFile);
        }
        catch (MapFileMismatchException& err)
        {
            std::cout << err.getErr() << std::endl;
            std::cout << "Ending program" << std::endl;
            delete board;
            return 1;
        }
        inFile.close();

        goLSimulation = new GoLSimulation(board, outputPref);
        goLSimulation->start();
    }
    else
    {
        board = new DoughnutBoard();
        goLSimulation = new GoLSimulation(board, outputPref);
        goLSimulation->start();
    }
    delete board;
    delete goLSimulation;
    return 0;
}