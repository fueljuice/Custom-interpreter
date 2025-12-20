#ifndef PARSER_H
#define PARSER_H

#include "IndentationException.h"
#include "SyntaxException.h"
#include "NameErrorException.h"
#include "type.h"
#include "Helper.h"
#include "Integer.h"
#include "String.h"
#include "Boolean.h"
#include "Void.h"


#include <algorithm>
#include <unordered_map>
#include <string>
#include <regex>
#include <unordered_map>
#include <iostream>
#include <sstream>

class Parser
{
public:
	static Type* parseString(std::string str);
	static Type* getType(std::string& str);


private:
	// checks wethear a name of a variable is legal
	static bool isLegalVarName(const std::string& str);

	// returns true if assigns a variable to a value
	static bool makeAssignment(const std::string& str);

	// returns the value of a variable with his name as parameter
	static Type* getVariableValue(const std::string& key);
	
	// cleans the value stored in a variable
	static void varCleanup(const std::string& key);


	static std::unordered_map<std::string, Type*> variables_;
};

#endif //PARSER_H
