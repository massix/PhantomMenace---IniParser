/*
 * doubleElement.cpp
 *
 *  Created on: Mar 31, 2012
 *      Author: massi
 */

#include "PM_IP_IniElement.h"
#include "PM_IP_Parser.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <exception>
#include <stdexcept>

int main(int argc, char *argv[])
{
	PhantomMenace::IniParser::Parser::getInstance().parse(
			"# This is a comment\n"
			"[first grammar]\n"
			"   \n"
			"# Only the first one should be pushed..\n"
			"g_one.logic = False\n"
			"g_one.logic = True\n"
	);

	const PhantomMenace::IniParser::IniElement& first_grammar =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[0];

	std::cout << "Checking first grammar element name.. ";
	if (first_grammar.getElementName() != "first grammar")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking size of attributes.. ";
	if (first_grammar.sizeOfAttributes() != 1)
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking first grammar attribute g_one.logic.. ";
	if (first_grammar["g_one.logic"] != "False")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	PhantomMenace::IniParser::Parser::resetInstance();

	exit(EXIT_SUCCESS);
}


