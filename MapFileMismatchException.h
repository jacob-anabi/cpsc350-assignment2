/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#ifndef MAPFILEMISMATCHEXCEPTION_H
#define MAPFILEMISMATCHEXCEPTION_H

#include "RuntimeException.h"

class MapFileMismatchException : RuntimeException
{
public:
    /**
     * default constructor
     * @param err - the error message
     */
    explicit MapFileMismatchException(const std::string& err);

    /**
     * copy constructor
     * @param mapFileMismatchException - the MapFileMismatchException to copy over
     */
    MapFileMismatchException(const MapFileMismatchException& mapFileMismatchException);

    /**
     * destructor
     * NOTE: trivial
     */
    ~MapFileMismatchException() override;

    /**
     * getter for the error message
     * @return - the value returned by the base class' getErr method
     */
    std::string getErr();
};


#endif // MAPFILEMISMATCHEXCEPTION_H
