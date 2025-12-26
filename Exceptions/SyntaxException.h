#ifndef SYNTAX_EXCEPTION_H
#define SYNTAX_EXCEPTION_H

#include "InterperterException.h"
class SyntaxException : public InterperterException
{

public:
	virtual const char* what() const noexcept;

};

#endif // SYNTAX_EXCEPTION_H