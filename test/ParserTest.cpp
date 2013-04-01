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

#include "ParserTest.hpp"

#include "include/PM_IP_IniElement.h"
#include "include/PM_IP_Parser.h"
#include "include/PM_IP_StaticFunctions.h"

#include <boost/lexical_cast.hpp>

void PhantomMenace::IniParser::Test::IniParserTest::printParsingDuration(PhantomMenace::IniParser::Parser & parser)
{
	std::cout << "Parsing duration: " << parser.getParsingDuration() << std::endl;
}

void PhantomMenace::IniParser::Test::IniParserTest::testSimpleElement()
{
	PhantomMenace::IniParser::Parser& p = PhantomMenace::IniParser::Parser::getInstance();
	p.parse(
			"# This is a comment\n"
			"[new grammar]\n"
			"newgrammar.attribute = Something\n"
			"newgrammar.logic = None\n"
			"# This is another comment\n"
	);

	const PhantomMenace::IniParser::IniElement& elem = p.getElements()[0];

	CPPUNIT_ASSERT(elem.getElementName() == "new grammar");
	CPPUNIT_ASSERT(elem["newgrammar.attribute"] == "Something");

	printParsingDuration(p);
}

void PhantomMenace::IniParser::Test::IniParserTest::testDoubleElement()
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
	);

	const Elements_t& elements =
			PhantomMenace::IniParser::Parser::getInstance().getElements();

	{
		const PhantomMenace::IniParser::IniElement& grammar = elements[0];
		CPPUNIT_ASSERT(grammar.getElementName() == "first grammar");
		CPPUNIT_ASSERT(grammar["g_one.logic"] == "False");
		CPPUNIT_ASSERT(grammar["g_one.sentiment"] == "Love");
	}

	{
		const PhantomMenace::IniParser::IniElement& grammar = elements[1];
		CPPUNIT_ASSERT(grammar.getElementName() == "second grammar");
		CPPUNIT_ASSERT(grammar["g_two.logic"] == "True");
		CPPUNIT_ASSERT(grammar["g_two.sentiment"] == "Hate");
	}

	printParsingDuration(PhantomMenace::IniParser::Parser::getInstance());
}

void PhantomMenace::IniParser::Test::IniParserTest::testMultipleElements()
{
	PhantomMenace::IniParser::Parser::getInstance().parse(
			"# This is a comment\n"
			"[first grammar]\n"
			"logic = False\n"
			"sentiment = Love\n"
			"# This is another comment\n"
			"[second grammar]\n"
			"logic = True\n"
			"sentiment = Hate\n"
			"\n\n\n"
			"[third grammar]\n"
			"logic = None\n"
			"sentiment = Friendship\n"
	);

	{
		const PhantomMenace::IniParser::IniElement& grammar =
				PhantomMenace::IniParser::Parser::getInstance().getElements()[0];
		CPPUNIT_ASSERT(grammar.getElementName() == "first grammar");
		CPPUNIT_ASSERT(grammar["logic"] == "False");
		CPPUNIT_ASSERT(grammar["sentiment"] == "Love");
	}

	{
		const PhantomMenace::IniParser::IniElement& grammar =
				PhantomMenace::IniParser::Parser::getInstance().getElements()[1];
		CPPUNIT_ASSERT(grammar.getElementName() == "second grammar");
		CPPUNIT_ASSERT(grammar["logic"] == "True");
		CPPUNIT_ASSERT(grammar["sentiment"] == "Hate");
	}

	{
		const PhantomMenace::IniParser::IniElement& grammar =
				PhantomMenace::IniParser::Parser::getInstance().getElements()[2];
		CPPUNIT_ASSERT(grammar.getElementName() == "third grammar");
		CPPUNIT_ASSERT(grammar["logic"] == "None");
		CPPUNIT_ASSERT(grammar["sentiment"] == "Friendship");
	}

	printParsingDuration(PhantomMenace::IniParser::Parser::getInstance());
}

void PhantomMenace::IniParser::Test::IniParserTest::testSpacesAround()
{
	PhantomMenace::IniParser::Parser& p = PhantomMenace::IniParser::Parser::getInstance();
	p.parse(
			"# This is a comment\n"
			"[new grammar]       \n"
			"newgrammar.attribute = Something\n"
			"newgrammar.logic = None\n"
			"# This is another comment\n"
	);

	const PhantomMenace::IniParser::IniElement& elem = p.getElements()[0];

	CPPUNIT_ASSERT(elem.getElementName() == "new grammar");
	CPPUNIT_ASSERT(elem["newgrammar.attribute"] == "Something");

	printParsingDuration(PhantomMenace::IniParser::Parser::getInstance());
}

void PhantomMenace::IniParser::Test::IniParserTest::testParseFromFile()
{
	PhantomMenace::IniParser::Parser::getInstance().parseFromFile("../test/parseFromFile.ini");

	const PhantomMenace::IniParser::IniElement& first_law =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[0];

	CPPUNIT_ASSERT(first_law.getElementName() == "first law");
	CPPUNIT_ASSERT(first_law["law.mandatory"] == "True");
	CPPUNIT_ASSERT(first_law["law.body"] == "Never trust others");
	CPPUNIT_ASSERT(boost::lexical_cast<int>(first_law["law.paragraphs"]) == 1);


	const PhantomMenace::IniParser::IniElement& second_law =
			PhantomMenace::IniParser::Parser::getInstance().getElements()[1];

	CPPUNIT_ASSERT(second_law.getElementName() == "second law");
	CPPUNIT_ASSERT(second_law["law.mandatory"] == "False");
	CPPUNIT_ASSERT(second_law["law.body"] == "Always believe in gods");
	CPPUNIT_ASSERT(boost::lexical_cast<int>(second_law["law.paragraphs"]) == 1);

	printParsingDuration(PhantomMenace::IniParser::Parser::getInstance());
}

void PhantomMenace::IniParser::Test::IniParserTest::testRepeatingAttribute()
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

	CPPUNIT_ASSERT(first_grammar.getElementName() == "first grammar");
	CPPUNIT_ASSERT(first_grammar.sizeOfAttributes() == 1);
	CPPUNIT_ASSERT(first_grammar["g_one.logic"] == "False");

	printParsingDuration(PhantomMenace::IniParser::Parser::getInstance());
}
