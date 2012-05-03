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
