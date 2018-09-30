/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <fstream>

class Board
{
public:

    /**
     * default constructor
     */
    Board();

    /**
     * variable constructor
     * @param row - number of rows in the board
     * @param column - number of columns in the board
     * @param populationDensity - the population density for the Game of Life
     */
    Board(unsigned int rows, unsigned int columns, double populationDensity);

    /**
     * copy constructor
     * @param board - the board to copy over
     */
    Board(const Board& board);

    /**
     * destructor
     */
    virtual ~Board();

    /**
     * prints the board
     */
    void printBoard();

    /**
     * outputs the board to a file
     * @param outputFile - the file to output the board to
     */
    void outputBoard(std::ofstream& outputFile);

    /**
     * checks if a next generation is possible
     * @return a boolean value that returns true if a next generation is possible, false otherwise
     */
    bool nextGenerationPossible();

    /**
     * construct a board with a provided map file
     * @param mapFile - the provided map file to look over
     */
    void fileConstruct(std::ifstream& mapFile);

    /**
     * calculates the next generation of the board
     * @return boolean value representing if the next generation is possible
     * NOTE: pure virtual function
     */
    void nextGeneration();

    /**
     * getter for the generation number
     * @return the generation number
     */
    int getGenerationNumber();

protected:
    char** board; // the board to be displayed to the user
    char** previousBoard; // the previous board that will be used to check for stabilization
    char** referenceBoard; // the board to reference when calculating the next generation
    double populationDensity; // the initial population density on the board
    unsigned int rows; // number of rows in the board
    unsigned int columns; // number of columns in the board
    unsigned int generationNumber; // the generation that the board is on

    const char ALIVE = 'X'; // variable to represent an ALIVE cell
    const char DEAD = '-'; // variable to represent a DEAD cell

    /**
     * copies the original board's elements to the previous one
     */
    void copyBoardToPrev();

    /**
     * updates the reference board based on the regular board
     */
    virtual void updateRefBoard() = 0;

private:
    /**
     * checks if a string is numeric
     * @param message - the message to check
     * @return - boolean value that represents if the message is numeric (true for yes, false otherwise)
     */
    bool isNumeric(std::string& message);

    /**
     * initializes the board with the appropriate information
     * @param rows - number of rows of the board
     * @param columns - number of columns of the board
     * @param populationDensity - the population density of the board
     */
    void initBoard(int rows, int columns, double populationDensity);
};

#endif // BOARD_H