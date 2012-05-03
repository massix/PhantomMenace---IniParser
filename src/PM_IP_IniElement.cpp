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

#include "PM_IP_IniElement.h"
#include <exception>
#include <stdexcept>

namespace PhantomMenace {
namespace IniParser {

IniElement::IniElement(const std::string& elementName) :
		elementName(elementName)
{
}

const std::string& IniElement::getElementName() const
{
	return elementName;
}

const Attributes_t& IniElement::getAttributes() const
{
	return attributes;
}

const std::string& IniElement::operator[](const std::string& attributeName)
	const throw(std::logic_error)
{

	if (hasAttribute(attributeName))
		return attributes.at(attributeName);

	else
		throw std::logic_error("Attribute not found");
}

const std::string& IniElement::getValueForAttribute(
		const std::string& attributeName) const throw (std::logic_error)
{
	return (*this)[attributeName];
}

bool IniElement::pushAttribute(const std::string& atName, const std::string& atValue)
{
	return (attributes.insert(Attribute_t(atName, atValue)).second);
}

void IniElement::clearAttributes()
{
	attributes.clear();
}

IniElement& IniElement::operator=(const IniElement& right)
{
	this->elementName = right.elementName;
	this->attributes = right.attributes;
	return *this;
}

int IniElement::sizeOfAttributes() const
{
	return attributes.size();
}

bool IniElement::hasAttribute(const std::string& attributeName) const
{
	try
	{
		attributes.at(attributeName);
	}
	catch(...)
	{
		return false;
	}

	return true;
}

IniElement::~IniElement()
{
}

} /* namespace IniParser */
} /* namespace PhantomMenace */
