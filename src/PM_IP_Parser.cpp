/*
 * PM_IP_Parser.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#include "PM_IP_Parser.h"
#include <boost/regex.hpp>

PhantomMenace::IniParser::Parser *parser = 0;

namespace PhantomMenace {
namespace IniParser {

Parser& Parser::getInstance()
{
	if (!parser)
		parser = new Parser();

	return *parser;
}

Parser* Parser::getInstancePtr()
{
	if (!parser)
		parser = new Parser();

	return parser;
}

void Parser::resetInstance()
{
	if (parser)
		delete parser;
}

void Parser::log() const
{
	std::cout << "==============\n"
			  << "= PARSER LOG =\n"
			  << "==============\n";
}

void Parser::parse(const char *raw)
{
	if (raw == 0)
		return;

	// Read it line by line
	int lastIndex = 0;
	char rc = raw[lastIndex];

	while (rc != '\0')
	{
		std::string aString;
		aString.clear();

		while (rc != '\n')
		{
			aString += rc;
			rc = raw[++lastIndex];
		}

		// Manage the string
		// A new token is found
		if (aString.at(0) == '[')
		{
			IniElement elem(aString.substr(1, aString.size()-2));
			elements.push_back(elem);
			elements.back().clearAttributes();
		}

		// This must be an attribute (since it's not a comment)
		else if (aString.at(0) != '#')
		{
			try {
				boost::cmatch cm;
				boost::regex re("(.*?) = (.*?)$", boost::regex_constants::icase);

				if (boost::regex_match(aString.c_str(), cm, re))
				{
					elements.back().pushAttribute(cm[1], cm[2]);
				}
			}
			catch (boost::regex_error& e)
			{
				std::cerr << "GOT EXCEPTION " << e.what() << std::endl;
			}
		}

		rc = raw[++lastIndex];
	}
}

const Elements_t& Parser::getElements() const
{
	return elements;
}

} /* namespace IniParser */
} /* namespace PhantomMenace */
