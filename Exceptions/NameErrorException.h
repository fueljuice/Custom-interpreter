#ifndef NAME_ERROR_EXCEPTION_H
#define NAME_ERROR_EXCEPTION_H

#include "InterperterException.h"
#include <string>
class NameErrorException : public InterperterException
{
public:
	NameErrorException(std::string name);

	virtual const char* what() const noexcept;

private:
	std::string name_;
	std::string expMsg;
};
#endif // NAME_ERROR_EXCEPTION_H