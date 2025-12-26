#ifndef LIST_H
#define LIST_H

#include "sequence.h"

#include <vector>

class List : public Sequence
{
public:
	List(std::vector<Type*> v);
	bool isPrintable() const noexcept;
	std::string toString() const noexcept;
	unsigned int seqLength() const noexcept;

private:
	std::vector<Type*> typeVector;
};

#endif // LIST_H