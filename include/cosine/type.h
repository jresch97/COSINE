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

#ifndef COS_TYPE_H
#define COS_TYPE_H

#include <stddef.h>

enum COS_TYPES {
        COS_VOID_TYPE = 0,
        COS_CLASS_TYPE,
        COS_OBJECT_TYPE,
        COS_STRING_TYPE,
        COS_CHAR_TYPE,
        COS_SHORT_TYPE,
        COS_INT_TYPE,
        COS_LONG_TYPE,
        COS_BYTE_TYPE,
        COS_USHORT_TYPE,
        COS_UINT_TYPE,
        COS_ULONG_TYPE,
        COS_SIZE_T_TYPE
};

typedef struct cos_param_s         cos_param;
typedef struct cos_class_s        *cos_class;
typedef struct cos_object_class_s *cos_object_class;
typedef struct cos_object_s       *cos_object;
typedef struct cos_string_class_s *cos_string_class;
typedef struct cos_string_s       *cos_string;

typedef void (*cos_class_init_fn)(cos_class);
typedef void (*cos_class_term_fn)(cos_class);
typedef void (*cos_object_init_fn)(cos_object, size_t, cos_param *);
typedef void (*cos_object_term_fn)(cos_object);

#endif
