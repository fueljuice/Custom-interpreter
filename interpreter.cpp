#include "type.h"
#include "InterperterException.h"
#include "SyntaxException.h"
#include "IndentationException.h"
#include "parser.h"
#include <iostream>

#define WELCOME "Welcome to Python Interperter version 1.0 by "
#define YOUR_NAME "Zohar Frosh"

///
/// דברים שלמדתי מהפרויקט
/// downcasting
/// std::map
/// exception handling / class creating
/// 
/// 
///
/// 
int main(int argc,char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);
	
	while (input_string != "quit()")
	{
		try
		{
			// prasing command
			Type* parsedType = Parser::parseString(input_string);

			// printing parsed value to console
			if (parsedType->isPrintable())
				std::cout << parsedType->toString() << std::endl;

			// deleting if its an prvalue
			if (parsedType->isTemp())
				delete parsedType;
		}

		catch (SyntaxException& ex)
		{
			std::cout << ex.what() << std::endl;
		}

		catch (IndentationException& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		catch (NameErrorException& ex)
		{
			std::cout << ex.what() << std::endl;
		}



		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}

	return 0;
}


