#include "BuiltIns.h"


String* BuiltIns::typeFunc(Type* t)
{
	std::string s;
	std::string typeName;
	String* sObj = nullptr;

	if (t == nullptr)
		return nullptr;
	// check what type
	if (dynamic_cast<List*>(t) != nullptr)		
		typeName = "list";
	else if (dynamic_cast<Integer*>(t) != nullptr)
		typeName = "int";
	else if (dynamic_cast<Boolean*>(t) != nullptr)
		typeName = "bool";
	else if (dynamic_cast<String*>(t) != nullptr)
		typeName = "string";

	s = "<type '" + typeName + "'>";
	sObj = new String(s);
	sObj->setTemp(true);
	return sObj;
}

Integer* BuiltIns::lenFunc(Sequence* seq)
{
	Integer* iObj = nullptr;

	if (seq == nullptr)
		return nullptr;
	// make an Integer class with length-2 as parameter ( -2 so no include the quotes)
	iObj = new Integer(seq->seqLength() - 2);
	iObj->setTemp(true);
		
	return iObj;
}

Void* BuiltIns::delFunc(std::unordered_map<std::string, Type*>& m, Type* t)
{
	Type* typeObj = nullptr;
	Void* vObj = nullptr;
	if (t == nullptr)
		return nullptr;
	// sreach for element
	for (const auto& key : m)
	{
		if (key.second == t)
		{

			typeObj = key.second;
			m.erase(key.first);
			break;
		}
	}
	// must exist
	if (typeObj == nullptr)
		return nullptr;

	delete typeObj;
	vObj = new Void();
	vObj->setTemp(true);
	return vObj;

}

Void* BuiltIns::appendFunc(List* t)
{
	return nullptr;
}
