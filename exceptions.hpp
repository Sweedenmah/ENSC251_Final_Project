//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Implements assorted custom exception classes to use in various try...catch statements in our code. Inherits from std::exception.
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class InvalidProvince : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Invalid Province";
    }
};

class InvalidCountry : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Invalid Country";
    }
};

class MissingField : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Missing field in input file";
    }
};

class InvalidMember : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Invalid member variable for the created student";
    }
};

class BadToefl : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Invalid parameters for TOEFL score";
    }
};

#endif