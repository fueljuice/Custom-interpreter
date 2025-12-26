#include "TypeErrorException.h"

TypeErrorException::TypeErrorException(std::string name)
	:name_(name), expMsg("TypeError") {
}

const char* TypeErrorException::what() const noexcept
{
	return expMsg.c_str();
}