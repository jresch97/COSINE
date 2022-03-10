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

#ifndef COS_STRING_H
#define COS_STRING_H

#include "object.h"

typedef struct COS_STRING_CLASS_S *COS_STRING_CLASS;
typedef struct COS_STRING_S       *COS_STRING;

#define COS_STRING_CLASS      (cos_str_class_get())
#define COS_STRING_CLASS_NAME "String"

struct COS_STRING_CLASS_S {
        struct COS_CLASS_S class;
};

COS_CLASS cos_str_class_get();
void      cos_str_class_ctor(COS_CLASS class);
void      cos_str_class_dtor(COS_CLASS class);

#define COS_STRING_CAST(obj) ((COS_STRING)obj)

struct COS_STRING_S {
        struct COS_OBJECT_S obj;
        size_t              len;
        const char         *c_str;
};

void        cos_str_ctor(COS_OBJECT this, COS_VALUES values);
void        cos_str_dtor(COS_OBJECT this);
const char *cos_str_c_str(COS_STRING this);
size_t      cos_str_len(COS_STRING this);
void        cos_str_print(COS_STRING this);

#endif
