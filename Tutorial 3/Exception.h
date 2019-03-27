#pragma once

#include <string>

///
///Inherit from this class to implement your own exceptions.
///
class Exception
{
	std::string message;

public:
	Exception(const std::string s) : message(s) {};

	virtual const std::string& what() const throw() { return message; }
};

