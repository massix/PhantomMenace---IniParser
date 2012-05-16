/*
 * main.cpp
 *
 *  Created on: Mar 25, 2012
 *      Author: massi
 */

#include "PM_IP_IniElement.h"
#include "PM_IP_Parser.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <exception>
#include <stdexcept>

int main (int argc, char *argv[])
{
	PhantomMenace::IniParser::Parser* p = PhantomMenace::IniParser::Parser::getInstancePtr();
	p->parse(
			"# This is a comment\n"
			"[new grammar]\n"
			"newgrammar.attribute = Something\n"
			"newgrammar.logic = None\n"
			"# This is another comment\n"
	);

	const PhantomMenace::IniParser::IniElement& elem = p->getElements()[0];

	std::cout << "Checking elementName... ";
	if (elem.getElementName() != "new grammar")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";


	std::cout << "Checking attribute newgrammar.attribute... ";
	if (elem["newgrammar.attribute"] != "Something")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	PhantomMenace::IniParser::Parser::resetInstance();
	exit(EXIT_SUCCESS);
}


