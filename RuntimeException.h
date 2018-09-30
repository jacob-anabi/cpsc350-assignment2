/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H

#include <string>

class RuntimeException
{
public:
    /**
     * default constructor
     * @param err - the error message
     */
    explicit RuntimeException(const std::string& err);

    /**
     * copy constructor
     * @param runtimeException - the RuntimeException to copy over
     */
    RuntimeException(const RuntimeException& runtimeException);

    /**
     * destructor
     * NOTE: trivial
     */
    virtual ~RuntimeException();

    /**
     * getter for the error message
     * @return - the error message
     */
    std::string getErr();

protected:
    std::string err;
};


#endif // RUNTIMEEXCEPTION_H
