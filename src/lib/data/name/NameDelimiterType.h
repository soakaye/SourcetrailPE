#ifndef NAME_DELIMITER_TYPE_H
#define NAME_DELIMITER_TYPE_H

#include <string>

enum class NameDelimiterType
{
	UNKNOWN,
	FILE,
	CXX,
	JAVA
};

std::string nameDelimiterTypeToString(NameDelimiterType delimiter);
NameDelimiterType stringToNameDelimiterType(const std::string& s);

NameDelimiterType detectDelimiterType(const std::string& name);

#endif	  // NAME_DELIMITER_TYPE_H
