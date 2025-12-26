#ifndef BUILTINS_H
#define BUILTINS_H

#include "type.h"
#include "Helper.h"
#include "Integer.h"
#include "String.h"
#include "Boolean.h"
#include "List.h"
#include "Void.h"
#include "NameErrorException.h"
#include <unordered_map>

class BuiltIns
{
public:
	// returns a temp String class that holds <type '[name type]'>
	static String* typeFunc(Type* t);

	// returns a temp Integer class with the length of the sequence child class parameter
	static Integer* lenFunc(Sequence* s);

	// deletes by value a type object from a map it gets
	static Void* delFunc(std::unordered_map<std::string, Type*>& m, Type* t);

	// currently unimplemented
	static Void* appendFunc(List* t);


};

#endif