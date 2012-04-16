/*
 * PM_IP_Parser.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#include "PM_IP_Parser.h"
#include <boost/regex.hpp>
#include <cstdlib>
#include <stdexcept>

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

	parser = 0;
}

void Parser::clearInstance()
{
	if (parser)
	{
		parser->elements.clear();
	}
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

		// New line and comment
		if (aString.size() == 0); //< Do Nothing
		else if (aString.at(0) == '#'); //< Do nothing

		// A new token is found
		else if (aString.at(0) == '[')
		{
			IniElement elem;
			boost::cmatch cm;
			boost::regex re("^\\[(.*?)\\].*", boost::regex_constants::icase);
			if (boost::regex_match(aString.c_str(), cm, re))
				elem.elementName = cm[1];
			else
				elem.elementName = aString.substr(1, aString.size()-2);

			elements.push_back(elem);
			elements.back().clearAttributes();
		}

		// This must be an attribute
		else
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

void Parser::parseFromFile(const std::string& iFileName)
{
	FILE *file;

	file = fopen(iFileName.c_str(), "r");
	if (file == 0)
		throw std::runtime_error("Couldn't open file..");

	std::string aFileContent;

	// Read 4k per time
	char *block = new char[4096];
	size_t read;
	while (!feof(file))
	{
		read = fread(block, sizeof(char), 4096, file);
		aFileContent += block;
	}

	delete [] block;
	fclose(file);
	parse(aFileContent.c_str());
}

const Elements_t& Parser::getElements() const
{
	return elements;
}

const IniElement& Parser::getElement(const std::string& iElementName)
	const throw(std::runtime_error)
{
	Elements_t::const_iterator ite;

	for (ite = elements.begin(); ite != elements.end(); ++ite)
	{
		if ((*ite).getElementName() == iElementName)
			return (*ite);
	}

	throw std::runtime_error("Element not found!");
}

bool Parser::hasElement(const std::string& iElementName) const
{
	try
	{
		getElement(iElementName);
		return true;
	}
	catch (...)
	{
		return false;
	}

	return false;
}

} /* namespace IniParser */
} /* namespace PhantomMenace */
