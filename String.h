#ifndef STRING_H
#define STRING_H

#include "Sequence.h"
class String : public Sequence
{
public:
	String(std::string val);
	bool isPrintable() const noexcept;
	std::string toString() const noexcept;


};
#endif // STRING_H