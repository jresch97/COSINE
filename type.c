#include <assert.h>

#include "type.h"

const char *cos_type_str(int type)
{
        switch (type) {
                case COS_TYPE_VOID:   return "void";
                case COS_TYPE_CLASS:  return "Class";
                case COS_TYPE_OBJECT: return "Object";
                case COS_TYPE_CHAR:   return "char";
                case COS_TYPE_SHORT:  return "short";
                case COS_TYPE_INT:    return "int";
                case COS_TYPE_LONG:   return "long";
                case COS_TYPE_BYTE:   return "byte";
                case COS_TYPE_USHORT: return "ushort";
                case COS_TYPE_UINT:   return "uint";
                case COS_TYPE_ULONG:  return "ulong";
                case COS_TYPE_SIZE_T: return "size_t";
                default: assert(0 && "Unknown type.");
        }
}
