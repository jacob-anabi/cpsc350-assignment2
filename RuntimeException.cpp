/**
 * @author Jacob Anabi
 * @date 2018-09-29
 * @version 1.0
 * 2294644
 * CPSC 350
 * Assignment 2
 */

#include "RuntimeException.h"

// default constructor
RuntimeException::RuntimeException(const std::string& err)
: err(err)
{
}

RuntimeException::RuntimeException(const RuntimeException& runtimeException)
: err(runtimeException.err)
{
}

// destructor (is trivial)
RuntimeException::~RuntimeException()
= default;

// getter for the error message
std::string RuntimeException::getErr()
{
    return err;
}
