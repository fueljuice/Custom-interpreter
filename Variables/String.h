#ifndef STRING_H
#define STRING_H

#include "Sequence.h"
class String : public Sequence
{
public:
	String(std::string var);
	String(const String& other);
	bool isPrintable() const noexcept;
	std::string toString() const noexcept;
	unsigned int seqLength() const noexcept;


private:
	std::string var_;
};
#endif // STRING_H