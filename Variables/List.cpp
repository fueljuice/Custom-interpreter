#include "List.h"


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

unsigned int List::seqLength() const noexcept
{
	return typeVector.size();
}

List::List(std::vector<Type*> v)
	: typeVector(v)
	{}

bool List::isPrintable() const noexcept
{
	return true;
}