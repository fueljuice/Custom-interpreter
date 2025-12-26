#ifndef BOOLEAN_H
#define BOOLEAN_H
#include "type.h"

class Boolean : public Type
{
public:
	Boolean(bool var);
	Boolean(const Boolean& other);
	bool isPrintable() const noexcept;
	std::string toString() const noexcept;

private:
	bool var_;
};
#endif // BOOLEAN_H