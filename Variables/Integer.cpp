#include "Integer.h"

Integer::Integer(int var)
	: var_(var){}

Integer::Integer(const Integer& other)
	: var_(other.var_)
{
	this->setTemp(other.isTemp());
}


bool Integer::isPrintable() const noexcept
{
	return true;
}

std::string Integer::toString() const noexcept
{
	return std::to_string(var_);
}
