#include "Integer.h"

Integer::Integer(int var)
	: var_(var){}

Integer::Integer(const Integer& other)
	: var_(other.var_)
{
	this->setTemp(other.isTemp());
}
