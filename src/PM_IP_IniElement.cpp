/*
 * PM_IP_IniElement.cpp
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
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
