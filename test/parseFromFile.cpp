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

#include <boost/lexical_cast.hpp>

int main(int argc, char *argv[])
{
	PhantomMenace::IniParser::Parser::getInstance().parseFromFile("../../test/parseFromFile.ini");

	const PhantomMenace::IniParser::IniElement& first_law =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[0];

	std::cout << "Checking first law element name.. ";
	if (first_law.getElementName() != "first law")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking first law attribute law.mandatory.. ";
	if (first_law["law.mandatory"] != "True")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking first law attribute law.body.. ";
	if (first_law["law.body"] != "Never trust others")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking first law paragraphs.. ";
	if (boost::lexical_cast<int>(first_law["law.paragraphs"]) != 1)
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	const PhantomMenace::IniParser::IniElement& second_law =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[1];

	std::cout << "Checking second law element name.. ";
	if (second_law.getElementName() != "second law")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking second law attribute law.mandatory.. ";
	if (second_law["law.mandatory"] != "False")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking second law attribute law.body.. ";
	if (second_law["law.body"] != "Always believe in gods")
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	std::cout << "Checking second law paragraphs.. ";
	if (boost::lexical_cast<int>(second_law["law.paragraphs"]) != 1)
		exit(EXIT_FAILURE);
	std::cout << "good!\n";

	PhantomMenace::IniParser::Parser::resetInstance();

	exit(EXIT_SUCCESS);
}


