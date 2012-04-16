/*
 * PM_IP_Parser.h
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
 */

#ifndef PM_IP_PARSER_H_
#define PM_IP_PARSER_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "PM_IP_IniElement.h"

typedef std::vector<PhantomMenace::IniParser::IniElement> Elements_t;

namespace PhantomMenace {
namespace IniParser {

class Parser {
public:
	static Parser& getInstance();
	static Parser* getInstancePtr();
	static void resetInstance();
	static void clearInstance();

	void parse(const char *raw);
	void parseFromFile(const std::string& iFileName);

	const Elements_t& getElements() const;
	const IniElement& getElement(const std::string& iElementName)
		const throw(std::runtime_error);

	bool hasElement(const std::string& iElementName) const;

	void log() const;

private:
	Parser& operator=(const Parser& right) {return *this;}
	Parser() {};
	virtual ~Parser() {};

	static Parser* instance;

	Elements_t elements;
};

} /* namespace IniParser */
} /* namespace PhantomMenace */
#endif /* PM_IP_PARSER_H_ */
