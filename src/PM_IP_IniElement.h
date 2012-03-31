/*
 * PM_IP_IniElement.h
 *
 *  Created on: Mar 24, 2012
 *      Author: massi
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
