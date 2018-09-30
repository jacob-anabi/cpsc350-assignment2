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
#include <fstream>
#include <cstdlib>
#include "Board.h"
#include "MapFileMismatchException.h"

// default constructor
Board::Board()
: rows(1), columns(1), populationDensity(1.0), generationNumber(0)
{
}

// variable constructor
Board::Board(unsigned int rows, unsigned int columns, double populationDensity)
: rows(rows), columns(columns), populationDensity(populationDensity), generationNumber(0)
{
    initBoard(rows, columns, populationDensity);
}

// copy constructor
Board::Board(const Board& board)
: rows(board.rows), columns(board.columns), populationDensity(board.populationDensity), generationNumber(0)
{
    initBoard(board.rows, board.columns, board.populationDensity);
}

// destructor
Board::~Board()
{
    for (int i = 0; i < rows; ++i) // deallocation of each array in the board
    {
        delete[] board[i];
        delete[] previousBoard[i];
        delete[] referenceBoard[i];
    }
    // deallocation of the boards
    delete[] board;
    delete[] previousBoard;
    delete[] referenceBoard;
}

// prints the board
void Board::printBoard()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}

// outputs the board to a file
void Board::outputBoard(std::ofstream& outputFile)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            outputFile << board[i][j];
        }
        outputFile << std::endl;
    }
}


// checks if a next generation is possible
bool Board::nextGenerationPossible()
{
    int matched = 0; // number of matching elements
    int empty = 0; // number of empty empty elements
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (board[i][j] == previousBoard[i][j])
            {
                ++matched;
            }
            if (board[i][j] == '-')
            {
                ++empty;
            }
        }
    }

    return !(((matched == (rows * columns)) && generationNumber > 0) || (empty == (rows * columns))); // return if the board stabilizes or is empty
}

// construct a board with a provided map file
void Board::fileConstruct(std::ifstream& mapFile)
{
    std::string line;
    int lineCount = 0;
    int columns = 1;
    int rows = 1;
    int rowNum = 0;
    int columnNum = 0;
    int aliveNum = 0;
    int deadNum = 0;

    while(getline(mapFile, line))
    {
        if (isNumeric(line) && (lineCount == 0)) // is the first line numeric and a row
        {
            rows = std::stoi(line);
        }
        else if (isNumeric(line) && (lineCount == 1)) // is the second line numeric and a column
        {
            columns = std::stoi(line);
            // initializing the board
            board = new char*[rows];
            previousBoard = new char*[rows];
            for (int i = 0; i < rows; ++i) // initializing the 2-D array
            {
                board[i] = new char[columns];
                previousBoard[i] = new char[columns];
            }
        }
        else if ((rows > 0) && (columns > 0) && (line.size() == columns) && (lineCount > 1 && lineCount <= (rows + 1))) // making sure the grid has the specified number of columns, and it's in the right place of the map file
        {
            for (char c : line)
            {
                if (c == ALIVE)
                {
                    ++aliveNum;
                    board[rowNum][columnNum] = ALIVE;
                    previousBoard[rowNum][columnNum] = ALIVE;
                }
                else if (c == DEAD)
                {
                    ++deadNum;
                    board[rowNum][columnNum] = DEAD;
                    previousBoard[rowNum][columnNum] = DEAD;
                }
                else // if the map file doesn't contain an ALIVE character or a DEAD character, then it is invalid
                {
                    throw MapFileMismatchException("File improperly formatted.");
                }
                ++columnNum;
            }
            columnNum = 0;
            ++rowNum;
        }
        else if ((line.size() != columns) && (lineCount > 1 && lineCount <= (rows + 1))) // improper amount of columns in the grid
        {
            throw MapFileMismatchException("Invalid grid of columns");
        }
        else if (lineCount > (rows + 1)) // ignoring everything below the provided grid
        {
            continue;
        }
        else if (rowNum > rows) // improper amount of rows im the grid
        {
            throw MapFileMismatchException("Invalid grid of rows.");
        }
        else
        {
            // initializing the board (avoiding segmentation fault (core dumped)
            board = new char *[rows];
            previousBoard = new char *[rows];
            for (int i = 0; i < rows; ++i) // initializing the 2-D array
            {
                board[i] = new char[columns];
                previousBoard[i] = new char[columns];
            }
            throw MapFileMismatchException("File improperly formatted.");
        }
        ++lineCount;
    }
    double populationDensity = (static_cast<double>(aliveNum)) / (deadNum);

    this->rows = rows;
    this->columns = columns;
    this->populationDensity = populationDensity;

    referenceBoard = new char*[rows + 2];
    // initializing the reference board
    for (int i = 0; i < (rows + 2); ++i)
    {
        referenceBoard[i] = new char[columns + 2];
        for (int j = 0; j < (columns + 2); ++j)
        {
            referenceBoard[i][j] = '-'; // initializing each element of the array
        }
    }

    updateRefBoard();
}

// calculates the next generation of the doughnut board
void Board::nextGeneration()
{
    int neighbors = 0; // number of neighbors each cell has
    copyBoardToPrev(); // setting the previous board to the original board before modification
    updateRefBoard(); // updating the reference board to use it for neighbor checking

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            // neighbor checking

            // three neighbors above cell
            if (referenceBoard[i][j] == 'X')
            {
                ++neighbors;
            }
            if (referenceBoard[i][j + 1] == 'X')
            {
                ++neighbors;
            }
            if (referenceBoard[i][j + 2] == 'X')
            {
                ++neighbors;
            }

            // two neighbors to left and right of the cell
            if (referenceBoard[i + 1][j] == 'X')
            {
                ++neighbors;
            }
            if (referenceBoard[i + 1][j + 2] == 'X')
            {
                ++neighbors;
            }

            // three neighbors below cell
            if (referenceBoard[i + 2][j] == 'X')
            {
                ++neighbors;
            }
            if (referenceBoard[i + 2][j + 1] == 'X')
            {
                ++neighbors;
            }
            if (referenceBoard[i + 2][j + 2] == 'X')
            {
                ++neighbors;
            }

            // updating the cell in the regular board
            if ((neighbors <= 1) || (neighbors >= 4))
            {
                board[i][j] = '-';
            }
            else if ((neighbors == 3) && (board[i][j] != 'X'))
            {
                board[i][j] = 'X';
            }
            neighbors = 0;
        }
    }
    ++generationNumber;
}

// getter for the generation number
int Board::getGenerationNumber()
{
    return generationNumber;
}

// copies an board's elements to another one
void Board::copyBoardToPrev()
{
    for (int i = 0; i < rows; ++i) // deallocation of the copyBoard
    {
        delete[] previousBoard[i];
    }
    // deallocation of the copy board
    delete[] previousBoard;

    previousBoard = new char*[rows];
    for (int i = 0; i < rows; ++i)
    {
        previousBoard[i] = new char[columns];
        for (int j = 0; j < columns; ++j)
        {
            previousBoard[i][j] = board[i][j];
        }
    }
}

// checks if a string is numeric
bool Board::isNumeric(std::string& message)
{
    if ((message.empty())) // if the string is empty
    {
        return false;
    }
    for (char c : message)
    {
        if (!(isdigit(c))) // if any character in the message is alphabetic, then the message isn't numeric
        {
            return false;
        }
    }
    return true;
}

// initializes the board with the appropriate information
void Board::initBoard(int rows, int columns, double populationDensity)
{
    int count = 0;
    double randomNum = 0.0;
    double currentDensity = 0.0;

    // initializing the board
    board = new char*[rows];
    previousBoard = new char*[rows];
    for (int i = 0; i < rows; ++i) // initializing the board and the previous board
    {
        board[i] = new char[columns];
        previousBoard[i] = new char[columns];
        for (int j = 0; j < columns; ++j)
        {
            randomNum = static_cast<double>(rand()) / (RAND_MAX);
            if ((randomNum <= populationDensity) && (currentDensity < populationDensity)) // filling in cells based on population density
            {
                board[i][j] = ALIVE;
                previousBoard[i][j] = ALIVE;
                ++count;
            }
            else
            {
                board[i][j] = DEAD;
                previousBoard[i][j] = DEAD;
            }
            currentDensity = (static_cast<double>(count) / (rows * columns));
        }
    }

     // This is only necessary if the above initialization doesn't fill in the required population density
    currentDensity = (static_cast<double>(count) / (rows * columns));
    while (currentDensity < populationDensity)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                if ((board[i][j] != ALIVE) && (currentDensity < populationDensity))
                {
                    board[i][j] = ALIVE;
                    previousBoard[i][j] = ALIVE;
                    ++count;
                }
                currentDensity = (static_cast<double>(count) / (rows * columns));
            }
        }
    }

    referenceBoard = new char*[rows + 2];
    // initializing the reference board
    for (int i = 0; i < (rows + 2); ++i)
    {
        referenceBoard[i] = new char[columns + 2];
        for (int j = 0; j < (columns + 2); ++j)
        {
            referenceBoard[i][j] = '-'; // initializing each element of the array
        }
    }
}