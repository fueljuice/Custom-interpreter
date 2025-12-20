#ifndef TYPE_H
#define TYPE_H

#include <string>
class Type
{
public:
	// setter/getter for the isTemp field
	bool isTemp() const noexcept;
	void setTemp(bool state) noexcept;

	// pure virtual functions for printablity and the print itself
	virtual bool isPrintable() const noexcept = 0;
	virtual std::string toString() const noexcept = 0;

private:
	bool isTemp_ = false;
};





#endif //TYPE_H
