#ifndef REFERENCE_KIND_H
#define REFERENCE_KIND_H

#include "utilityEnum.h"

// These values need to be the same as ReferenceKind in Java code (see ReferenceKind.java)
enum class ReferenceKind
{
	UNDEFINED = 0,
	TYPE_USAGE = 1,
	USAGE = 2,
	CALL = 3,
	INHERITANCE = 4,
	OVERRIDE = 5,
	TYPE_ARGUMENT = 6,
	TEMPLATE_SPECIALIZATION = 7,
	INCLUDE = 8,
	IMPORT = 9,
	MACRO_USAGE = 10,
	ANNOTATION_USAGE = 11
};

template <>
ReferenceKind intToEnum(int value);

#endif	  // REFERENCE_KIND_H
