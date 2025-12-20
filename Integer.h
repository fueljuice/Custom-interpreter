#ifndef INTEGER_H
#define INTEGER_H

#include "type.h"
class Integer : public Type
{
public:
	Integer(int val);
	Integer(const Integer& i);
	bool isPrintable() const noexcept;
	std::string toString() const noexcept;

private:
	int val;
};

#endif // INTEGER_H