#include "Void.h"

std::string Void::toString() const noexcept
{
	return "void";
}

bool Void::isPrintable() const noexcept
{
	return false;
}