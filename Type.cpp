#include "type.h"

bool Type::isTemp() const noexcept
{
	return false;
}

void Type::setTemp(bool state) noexcept
{
	isTemp_ = state;
}

