#include "Boolean.h"
#include "List.h"


Boolean::Boolean(bool val)
	: var_(val){}

Boolean::Boolean(const Boolean& other)
	: var_(other.var_)
{
	this->setTemp(other.isTemp());
}

List::List(std::vector<Type*> v)
	: typeVector(v){}


bool Boolean::isPrintable() const noexcept
{
	return true;
}

std::string Boolean::toString() const noexcept
{
	return std::string();
}
