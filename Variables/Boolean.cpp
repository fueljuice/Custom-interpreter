#include "Boolean.h"

Boolean::Boolean(bool val)
	: var_(val){}

Boolean::Boolean(const Boolean& other)
	: var_(other.var_)
{
	this->setTemp(other.isTemp());
}

bool Boolean::isPrintable() const noexcept
{
	return true;
}

std::string Boolean::toString() const noexcept
{
	if (var_)
		return "True";
	return "False";
}
