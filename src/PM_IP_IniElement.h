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

#ifndef PM_IP_INIELEMENT_H_
#define PM_IP_INIELEMENT_H_

#include <map>
#include <string>
#include <exception>
#include <stdexcept>

typedef std::map<std::string, std::string> Attributes_t;
typedef std::pair<std::string, std::string> Attribute_t;

namespace PhantomMenace {
namespace IniParser {

class IniElement {
	friend class Parser;

public:
	IniElement(const std::string& elementName);
	virtual ~IniElement();

	const std::string& getElementName() const;
	const Attributes_t& getAttributes() const;
	const std::string& operator[] (const std::string& attributeName) const
		throw (std::logic_error);

	const std::string& getValueForAttribute (const std::string& attributeName)
		const throw (std::logic_error);

	IniElement& operator=(const IniElement& right);

	int sizeOfAttributes() const;
	bool hasAttribute(const std::string& attributeName) const;

private:
	IniElement() {}
	std::string elementName;
	Attributes_t attributes;

	bool pushAttribute(const std::string& atName, const std::string& atValue);
	void clearAttributes();
};

} /* namespace IniParser */
} /* namespace PhantomMenace */
#endif /* PM_IP_INIELEMENT_H_ */
