#include "NameErrorException.h"


NameErrorException::NameErrorException(std::string name)
	:name_(name) , expMsg("NameError : name '" + name_ + "' is not defined") { }

const char* NameErrorException::what() const noexcept
{
	return expMsg.c_str();
}

