#include "type.h"

Type::Type()
	: isTemp_(false){}

bool Type::isTemp() const noexcept
{
	return isTemp_;
}

void Type::setTemp(bool state) noexcept
{
	isTemp_ = state;
}

