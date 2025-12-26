#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "type.h"

class Sequence : public Type
{
public:
	virtual bool isPrintable() const noexcept = 0;
	virtual std::string toString() const noexcept = 0;;
	virtual unsigned int seqLength() const noexcept = 0;;

};
#endif // SEQUENCE_H