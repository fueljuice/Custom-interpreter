#ifndef TYPE_ERROR_EXCEPTION_H
#define TYPE_ERROR_EXCEPTION_H

#include "InterperterException.h"
#include <string>
class TypeErrorException : public InterperterException
{
public:
	TypeErrorException(std::string name);

	virtual const char* what() const noexcept;

private:
	std::string name_;
	std::string expMsg;
};
#endif // TYPE_ERROR_EXCEPTION_H