#include "parser.h"

Type* Parser::parseString(std::string str)
{
	Type* parsedObj = nullptr;
	// checks indentation
	if (!str.empty())
	{
		if (str[0] == ' ' || str[0] == '\t')
			throw IndentationException();

		// in a case of input of a legal var name,
		// check if its mapped
		if(isLegalVarName(str))
		{
			parsedObj = getVariableValue(str);
			if (parsedObj != nullptr)
				// if its mapped, return it
				return parsedObj;
			else
				// if it doesnt exist, tell user to define it first
				throw NameErrorException(str);
		}

		// in case of a prvalue as input
		parsedObj = getType(str);	

		// check if input is an assignment op
		if (parsedObj == nullptr)
		{
			if (makeAssignment(str))
			{
				parsedObj = new Void();
				parsedObj->setTemp(true);
			}
		}
	}

	return parsedObj;
}

Type* Parser::getType(std::string& str)
{
	int i;
	bool boolParam;
	Type* typeObj = nullptr;
	// cleaning indentation in the start
	Helper::trim(str);

	// if int
	if (Helper::isInteger(str))
	{
		typeObj = new Integer(std::stoi(str));
		typeObj->setTemp(true);
	}

	// if bool
	else if (Helper::isBoolean(str))
	{
		boolParam = true;
		if (str == "False")
			boolParam = false;
		typeObj = new Boolean(boolParam);
		typeObj->setTemp(true);
	}

	// if string
	else if (Helper::isString(str))
	{
		typeObj = new String(str);
		typeObj->setTemp(true);
	}

	if (typeObj == nullptr)
		throw SyntaxException();

	return typeObj;

}

bool Parser::isLegalVarName(const std::string& str)
{
	// if starts with digit
	if(str[0] >= '0' || str[0] <= '9')	return false;
	
	// regex match for every one or more word chararcter (a-z, A-Z underscore and digit) 
	if (!std::regex_match(str, std::regex("\\w+")))
		return false;

	return true;
}

bool Parser::makeAssignment(const std::string& str)
{
	int spaceLessEqualsIndex, equalsIndex;
	std::string leftObjName, rightObjName;
	std::string spacelessStr = str;
	Type* rightTypeObj = nullptr;
	// trimming spaces
	spacelessStr.erase(remove(spacelessStr.begin(),
		spacelessStr.end(), ' '), spacelessStr.end());

	// finds the index of the "="
	spaceLessEqualsIndex = spacelessStr.find('=');
	if (spaceLessEqualsIndex == spacelessStr.npos)
		return false;

	// equals sign cant be on the edges
	if (spaceLessEqualsIndex == 0 || spaceLessEqualsIndex == spacelessStr.length())
		return false;

	// if reached here there must be a "=" (since previously chgecked)
	equalsIndex = str.find('=');

	// extracting substrings
	leftObjName = str.substr(0, equalsIndex);
	rightObjName = str.substr(equalsIndex, str.length());

	if (!isLegalVarName(leftObjName))
		throw NameErrorException(leftObjName);
	if (!isLegalVarName(rightObjName))
		throw NameErrorException(rightObjName);

	// if the right obj is a variable and not an prvalue, deep copy
	if (variables_.find(rightObjName) != variables_.end())
	{
		rightTypeObj = variables_.at(rightObjName);
	}

	else
		rightTypeObj = getType(rightObjName);
	// if the key is already present, update it
	if (variables_.find(leftObjName) != variables_.end())
		variables_.at(leftObjName) = rightTypeObj;

	// if not, create new keyval pair of var and its value
	else
	{
		rightTypeObj = getType(rightObjName);
		variables_.insert({ leftObjName, rightTypeObj });
	}
	return true;
}

Type* Parser::getVariableValue(const std::string& key)
{
	if (variables_.find(key) != variables_.end())
		// if exist return it
		return variables_.at(key);

	return nullptr;
}

void Parser::varCleanup(const std::string& key)
{
	auto var = variables_.find(key);
	if (var != variables_.end())
		// if exsit delete it
		delete variables_.at(key);
}




