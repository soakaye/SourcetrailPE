#include "ReferenceKind.h"

namespace
{

const ReferenceKind REFERENCE_KINDS[] = {
	ReferenceKind::UNDEFINED,
	ReferenceKind::TYPE_USAGE,
	ReferenceKind::USAGE,
	ReferenceKind::CALL,
	ReferenceKind::INHERITANCE,
	ReferenceKind::OVERRIDE,
	ReferenceKind::TYPE_ARGUMENT,
	ReferenceKind::TEMPLATE_SPECIALIZATION,
	ReferenceKind::INCLUDE,
	ReferenceKind::IMPORT,
	ReferenceKind::MACRO_USAGE,
	ReferenceKind::ANNOTATION_USAGE
};

}

template <>
ReferenceKind intToEnum(int value)
{
	return lookupEnum(value, REFERENCE_KINDS, ReferenceKind::UNDEFINED);
}
