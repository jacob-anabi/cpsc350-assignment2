/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#include "MapFileMismatchException.h"

// default constructor
MapFileMismatchException::MapFileMismatchException(const std::string& err)
: RuntimeException(err)
{
}

// copy constructor
MapFileMismatchException::MapFileMismatchException(const MapFileMismatchException& mapFileMismatchException)
: RuntimeException(mapFileMismatchException)
{
}

// destructor (is trivial)
MapFileMismatchException::~MapFileMismatchException()
= default;

// getter for the error message
std::string MapFileMismatchException::getErr()
{
    return err;
}