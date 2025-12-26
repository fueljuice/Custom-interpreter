#include "String.h"

String::String(std::string var)
	: var_(var){}

String::String(const String& other)
	:	var_(other.var_)
{
	this->setTemp(other.isTemp());
}

std::string String::toString() const noexcept
{
	return var_;
}

bool String::isPrintable() const noexcept
{
	return true;
}

unsigned int String::seqLength() const noexcept
{
	return var_.length();
}