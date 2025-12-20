#ifndef VOID_H
#define VOID_H
#include "type.h"

class Void : public Type
{
public:
	Void();
	bool isPrintable() const noexcept;
	std::string toString() const noexcept;
};
#endif // VOID_H