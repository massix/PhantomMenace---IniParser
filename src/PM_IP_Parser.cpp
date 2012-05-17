/* Copyright (c) 2012, Massimo Gengarelli <massimo.gengarelli@gmail.com>
 *
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "PM_IP_Parser.h"
#include <boost/regex.hpp>
#include <cstdlib>
#include <stdexcept>

#include <cstdio>

#include <fstream>
#include <sstream>
#include <iterator>

namespace PhantomMenace {
namespace IniParser {


Parser::Parser()
{

}

Parser& Parser::getInstance()
{
	static Parser _instance;
	return _instance;
}

Parser* Parser::getInstancePtr()
{
	return &(getInstance());
}

void Parser::resetInstance()
{
	getInstance().elements.clear();
}

void Parser::clearInstance()
{
	resetInstance();
}

void Parser::parse(const char *raw)
{
	resetInstance();

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
	std::ifstream aFileStream(iFileName.c_str());

	if (aFileStream)
	{
		std::string aFileContent((std::istreambuf_iterator<char>(aFileStream)),
				(std::istreambuf_iterator<char>()));

		parse (aFileContent.c_str());

		aFileStream.close();
	}
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
