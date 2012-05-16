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
			"g_one.logic = False\n"
			"g_one.sentiment = Love\n"
			"# This is another comment\n"
			"[second grammar]\n"
			"g_two.logic = True\n"
			"g_two.sentiment = Hate\n"
			"\n\n\n"
			"[third grammar]\n"
			"g_three.logic = None\n"
			"g_three.sentiment = Friendship\n"
	);

	const PhantomMenace::IniParser::IniElement& first_grammar =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[0];

	std::cout << "Checking first grammar element name.. ";
	if (first_grammar.getElementName() != "first grammar")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking first grammar attribute g_one.logic.. ";
	if (first_grammar["g_one.logic"] != "False")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking first grammar attribute g_one.sentiment.. ";
	if (first_grammar["g_one.sentiment"] != "Love")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	const PhantomMenace::IniParser::IniElement& second_grammar =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[1];

	std::cout << "Checking second grammar element name.. ";
	if (second_grammar.getElementName() != "second grammar")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking second grammar attribute g_two.logic.. ";
	if (second_grammar["g_two.logic"] != "True")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking second grammar attribute g_two.sentiment.. ";
	if (second_grammar["g_two.sentiment"] != "Hate")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	const PhantomMenace::IniParser::IniElement& third_grammar =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[2];

	std::cout << "Checking third grammar element name.. ";
	if (third_grammar.getElementName() != "third grammar")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking third grammar attribute g_three.logic.. ";
	if (third_grammar["g_three.logic"] != "None")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking third grammar attribute g_three.sentiment.. ";
	if (third_grammar["g_three.sentiment"] != "Friendship")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";


	PhantomMenace::IniParser::Parser::resetInstance();

	exit(EXIT_SUCCESS);
}


