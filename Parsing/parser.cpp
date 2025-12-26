#include "parser.h"

std::unordered_map<std::string, Type*> Parser::variables_;

Type* Parser::parseString(std::string str)
{
	Type* parsedObj = nullptr;
	
	if (str.empty())
		return nullptr;

	// handle indentation
	if (str[0] == ' ' || str[0] == '\t')
		throw IndentationException();

	// check literal values
	parsedObj = getType(str);
	if (parsedObj != nullptr)
		return parsedObj;
	
	// check assignment operations
	if (makeAssignment(str))
	{
		parsedObj = new Void();
		parsedObj->setTemp(true);
		return parsedObj;
	}
	// check builtin function calls
	parsedObj = callBuiltIns(str);
	if (parsedObj != nullptr)
		return parsedObj;

	// check for a variable
	if (isLegalVarName(str))
	{
		parsedObj = getVariableValue(str);
		if (parsedObj != nullptr)
			return parsedObj;
		throw NameErrorException(str);
	}

	throw SyntaxException();

}

Type* Parser::getType(const std::string& str)
{
	bool boolParam;
	Type* typeObj = nullptr;
	std::string trimmed = str;
	std::vector<Type*> v;
	

	// cleaning spaces in the start and end
	Helper::trim(trimmed);
	// if int
	if (Helper::isInteger(trimmed))
	{
		typeObj = new Integer(std::stoi(trimmed));
		typeObj->setTemp(true);
	}

	// if bool
	else if (Helper::isBoolean(trimmed))
	{
		boolParam = true;
		if (trimmed == "False")
			boolParam = false;
		typeObj = new Boolean(boolParam);
		typeObj->setTemp(true);
	}

	// if string
	else if (Helper::isString(trimmed))
	{
		typeObj = new String(trimmed);
		typeObj->setTemp(true);
	}

	else
	{
		// if list
		v = isList(trimmed);
		if (!v.empty())
		{
			typeObj = new List(v);
			typeObj->setTemp(true);
		}
	}

	return typeObj;

}

bool Parser::isLegalVarName(const std::string& str)
{	
	std::string t = str;
	Helper::trim(t);
	if (t.empty()) return 
		false;

	// cant start with digit
	if (std::isdigit((unsigned char)t[0])) 
		return false;

	// must start with letter or _ then continue with \w*
	if (!std::regex_match(t, std::regex("[A-Za-z_]\\w*")))
		return false;

	// reserved names
	if (t == "True" || t == "False") return false;

	return true;
}

bool Parser::makeAssignment(const std::string& str)
{
	size_t equalsIndex;
	std::string destName, srcName, trimmedStr = str;
	Type* srcObj = nullptr;
	Type* src = nullptr;

	// trimming spaces
	Helper::trim(trimmedStr);

	// finds the index of the "="
	equalsIndex = trimmedStr.find('=');
	if (equalsIndex == trimmedStr.npos)
		return false;

	// equals sign cant be on the edges
	if (equalsIndex == 0 || equalsIndex == trimmedStr.length() - 1)
		return false;


	// cant have more than 1 equals sign
	if (trimmedStr.find('=', equalsIndex + 1) != std::string::npos)
		return false;


	// extracting substrings
	destName = trimmedStr.substr(0, equalsIndex);
	srcName = trimmedStr.substr(equalsIndex + 1, trimmedStr.length());


	Helper::trim(destName);
	Helper::trim(srcName);


	if (!isLegalVarName(destName))
		throw NameErrorException(destName);

	// if the right obj is a variable and not an prvalue, deep copy
	if(isLegalVarName(srcName))
	{
		// already exists
		auto itSrc = variables_.find(srcName);
		if (itSrc == variables_.end())
			throw NameErrorException(srcName);

		// if same object dont do anything
		if (srcName == destName)
			return true;

		src = itSrc->second;

		// if list keep pointer
		if (dynamic_cast<List*>(src))
			srcObj = src;
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
	else
	{
		// if its not a legal name then it might be a prvalue

		srcObj = getType(srcName);
		if (srcObj == nullptr)
			// if the srcName is not a type nor a knowkn variable its considered bad var name
			throw SyntaxException();

	}

	// if the key is already present, update it
	auto itDest = variables_.find(destName);
	if (itDest != variables_.end())
	{
		// if the destination is a list and another variable is pointing to the same list
		// dont delete the variable 
		int count = 0;
		if (dynamic_cast<List*>(itDest->second))
		{
			for (const auto& key : variables_)
			{
				if (key.second == itDest->second)
					count++;
				if (count == 2)
					break;
			}
		}
		if (count != 2)
			delete itDest->second;
		srcObj->setTemp(false);
		itDest->second = srcObj;

	}

	// if not, create new keyval pair of var name and its value
	else
	{
		srcObj->setTemp(false);
		variables_.insert({ destName, srcObj });
	}
	return true;
}

Type* Parser::getVariableValue(const std::string& key)
{
	auto itKey = variables_.find(key);
	if (itKey != variables_.end())
		// if exist return it
		return itKey->second;

	return nullptr;
}

void Parser::varCleanup(const std::string& key)
{
	auto var = variables_.find(key);
	if (var != variables_.end())
	{
		delete var->second;
		variables_.erase(var);
	}
}
Type* Parser::callBuiltIns(const std::string& s)
{
	std::string trimmed = s, arg;
	size_t open, close;
	Helper::trim(trimmed);
	Type* argObj = nullptr;

	if (trimmed.empty())
		return nullptr;

	// del syntax
	if (trimmed.substr(0, 4) == "del ")
	{
		arg = trimmed.substr(4, trimmed.length() - 4);
		Helper::trim(arg);

		// MUST exist to be deleted
		if (variables_.find(arg) == variables_.end())
			throw NameErrorException(arg);

		argObj = variables_.at(arg);
		return BuiltIns::delFunc(variables_, argObj);
	}


	// extract arg name from bracket
	open = trimmed.find('(');
	close = trimmed.rfind(')');
	if (open == std::string::npos || close == std::string::npos || close <= open)
		return nullptr;

	arg = trimmed.substr(open + 1, close - open - 1);
	Helper::trim(arg);

	// extract arg obj from its name
	if(!isLegalVarName(arg))
		argObj = getType(arg);

	else if (variables_.find(arg) != variables_.end())
		argObj = variables_.at(arg);


	// type() syntax
	if (trimmed.substr(0, 5) == "type(" && trimmed[trimmed.length() - 1] == ')')
		return BuiltIns::typeFunc(argObj);

	// len() syntax
	if (trimmed.substr(0, 4) == "len(" && trimmed[trimmed.length() - 1] == ')')
	{
		if (argObj == nullptr)
			throw TypeErrorException(arg);
		// must be Sequence type to apply to len()
		Sequence* castedTypeObj = dynamic_cast<Sequence*>(argObj);
		if (castedTypeObj == nullptr)
			throw TypeErrorException(arg); // dix
		return BuiltIns::lenFunc(dynamic_cast<Sequence*>(argObj));
	}

	// .append() syntax
	//dotIndex = trimmed.find('.');
	//quoteIndex = trimmed.find('"');
	//if (dotIndex != std::string::npos)
	//{
	//	// no quotes before the dot
	//	if (quoteIndex == std::string::npos || dotIndex < quoteIndex)
	//	{
	//		// must have .append(---)
	//		if (trimmed.substr(dotIndex + 1, 7) == "append(" && trimmed[trimmed.length() - 1] == ')')
	//			return BuiltIns::appendFunc(dynamic_cast<List*>(argObj));
	//	}
	//}

	return nullptr;
}
// returns a vector full of the lists Type objects if valid syntax. currently doesnt nested lists
std::vector<Type*> Parser::isList(const std::string& s)
{
	std::string trimmed = s, spaceLess = s;
	std::string expr;
	Helper::trim(trimmed);
	size_t curIndex = 1, commaIndex = 0, qouteIndex = 0, closeQouteIndex = 0, k = 0;
	bool isInString = false;
	std::vector<Type*> v;

	// helper for removing items
	auto fail = [&]() -> std::vector<Type*>
		{
			for (auto* t : v)
				delete t;
			return {};
		};

	if (trimmed[0] != '[' || trimmed[trimmed.length() - 1] != ']') 
		return fail();

	// empty list
	spaceLess.erase(std::remove(spaceLess.begin(), spaceLess.end(), ' '), spaceLess.end());
	if (spaceLess.length() == 2)
	{
		// TODO: fix accepting empty list
		// v.push_back(new Void()); 
		return fail();
	}
	while (true)
	{

		// finding comma
		commaIndex = trimmed.find(',', curIndex);
		if (commaIndex == std::string::npos)
			break;

		// finding if comma inside qoute
		qouteIndex = trimmed.find('"', curIndex);
		if (qouteIndex != std::string::npos)
		{
			isInString = (qouteIndex < commaIndex);
		}


		// if in string parse from the start qoute to the end qoute

		if (isInString)
		{
			// [1, a"abc"]
			// no junk before the quotes
			for (k = qouteIndex - 1; k > 2 && trimmed[k] == ' '; k--);
			if (trimmed[k] != ',' && k > 1)
				return fail();

			// finding close quotes
			closeQouteIndex = trimmed.find('"', qouteIndex + 1);

			// checking theres no junk strings after the qoutes or missing closing qoutes
			for (k = closeQouteIndex + 1; k < trimmed.size() - 1 && trimmed[k] == ' '; k++);

			if (closeQouteIndex == std::string::npos || (k < trimmed.size() - 1 && trimmed[k] != ','))
				return fail();
			expr = trimmed.substr(qouteIndex, closeQouteIndex - qouteIndex + 1);

			// cycling
			curIndex = trimmed.find(',', closeQouteIndex) + 1;
			isInString = false;
			// if no more exprresions left, make the end check get the current expr
			if (curIndex == std::string::npos + 1)
			{
				curIndex = qouteIndex;
				break;
			}



		}
		else
		{
			// substringing every expr
			expr = trimmed.substr(curIndex, commaIndex - curIndex);
			Helper::trim(expr);

			// cycling
			curIndex = commaIndex + 1;
		}

		// pushing it into a vector
		v.push_back(getType(expr));
		if (v.back() == nullptr)
			return fail();


	}

	// handling last expr
	expr = trimmed.substr(curIndex, trimmed.length() - curIndex - 1);

	Helper::trim(expr);

	// if an empty arr return true
	if (expr == "" && commaIndex == 0)
		return v;

	v.push_back(getType(expr));
	if (v.back() == nullptr)
		return fail();

	return v;
}


