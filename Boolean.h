#ifndef BOOLEAN_H
#define BOOLEAN_H
#include "type.h"

class Boolean : public Type
{
public:
	Boolean(bool val);
	bool isPrintable() const noexcept;
	std::string toString() const noexcept;

};
#endif // BOOLEAN_H