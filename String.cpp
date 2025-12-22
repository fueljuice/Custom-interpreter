#include "String.h"

String::String(std::string var)
	: var_(var){}

String::String(const String& other)
	:	var_(other.var_)
{
	this->setTemp(other.isTemp());
}