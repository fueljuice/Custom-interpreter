#include "List.h"

//bool List::isPrintable() const noexcept
//{
//
//}

std::string List::toString() const noexcept
{
	int i;
	std::string tostring = "[";
	for (i = 0; i < typeVector.size() - 1; i++)
	{
		tostring += typeVector[i]->toString();
		tostring += ", ";
	}
	tostring += typeVector[i]->toString();
	tostring += "]";
	return tostring;
}