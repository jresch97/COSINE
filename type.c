/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of COSINE.
 * 
 * COSINE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * COSINE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with COSINE. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <assert.h>
#include <stdlib.h>

#include "type.h"

const char *cos_type_str(int type)
{
        switch (type) {
                case COS_TYPE_VOID:   return "void";
                case COS_TYPE_CLASS:  return "Class";
                case COS_TYPE_OBJECT: return "Object";
                case COS_TYPE_C_STR:  return "const char *";
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
        return NULL;
}
