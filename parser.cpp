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
	std::vector<Type*> v;
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

	v = isList(str);
	if (!v.empty())
	{
		typeObj = new List(v);
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
	int trimmedStrEqualsIndex, equalsIndex;
	std::string destName, srcName;
	std::string trimmedStr = str;
	Type* srcObj = nullptr;

	// trimming spaces
	Helper::trim(trimmedStr);

	// finds the index of the "="
	trimmedStrEqualsIndex = trimmedStr.find('=');
	if (trimmedStrEqualsIndex == trimmedStr.npos) 
		return false;

	// equals sign cant be on the edges
	if (trimmedStrEqualsIndex == 0 || trimmedStrEqualsIndex == trimmedStr.length() - 1)
		return false;

	// cant have more than 1 equals sign
	if (trimmedStr.find('=', trimmedStrEqualsIndex + 1) != std::string::npos) 
		return false;

	// if reached here there must be a "=" (since previously chgecked)
	equalsIndex = str.find('=');

	// extracting substrings
	destName = str.substr(0, equalsIndex);
	srcName = str.substr(equalsIndex + 1, str.length());
	Helper::trim(destName);
	Helper::trim(srcName);

	if (!isLegalVarName(destName))
		throw NameErrorException(destName);

	// if the right obj is a variable and not an prvalue, deep copy
	if(!isLegalVarName(srcName))
	{
		if (variables_.find(srcName) != variables_.end())
		{
			Type* src = variables_.at(srcName);
			if (dynamic_cast<List*>(src))
			{
				// if list keep pointer
				srcObj = src;
			}
			else
			{
				// if non list, deep copy (call copy ctor)
				if (auto* pi = dynamic_cast<Integer*>(src))
					srcObj = new Integer(*pi);

				else if (auto* pb = dynamic_cast<Boolean*>(src))
					srcObj = new Boolean(*pb);

				else if (auto* ps = dynamic_cast<String*>(src))
					srcObj = new String(*ps);
			}
		}

		// if name is legal but not on the map then error exception
		else
			throw NameErrorException(srcName);
	}

	// if its not a legal name then it might be a prvalue
	else
	{
		srcObj = getType(srcName);
		if (srcObj == nullptr)
			// if the srcName is not a type nor a knowkn variable its considered bad var name
			throw SyntaxException();

	}

	// if the key is already present, update it
	if (variables_.find(destName) != variables_.end())
	{
		varCleanup(destName);
		srcObj->setTemp(false);
		variables_.at(destName) = srcObj;

	}

	// if not, create new keyval pair of var and its value
	else
	{
		variables_.insert({ destName, srcObj });
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
	{
		// if exsit delete it
		if(variables_.at(key) != nullptr)
			delete variables_.at(key);
	}
}

std::vector<Type*> Parser::isList(const std::string& s)
{
	return std::vector<Type*>();
}



