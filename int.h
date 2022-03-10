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

#ifndef COS_INT_H
#define COS_INT_H

#include "object.h"

typedef struct COS_INT_CLASS_S *COS_INT_CLASS;
typedef struct COS_INT_S       *COS_INT;

#define COS_INT_CLASS      (cos_int_class_get())
#define COS_INT_CLASS_NAME "Integer"

struct COS_INT_CLASS_S {
        struct COS_CLASS_S class;
};

COS_CLASS cos_int_class_get();
void      cos_int_class_ctor(COS_CLASS class);
void      cos_int_class_dtor(COS_CLASS class);
COS_INT   cos_int_sum(size_t n, ...);

#define COS_INT_CAST(obj) ((COS_INT)obj)

struct COS_INT_S {
        struct COS_OBJECT_S obj;
        int                 val;
};

void cos_int_ctor(COS_OBJECT this, COS_VALUES values);
void cos_int_dtor(COS_OBJECT this);
int  cos_int_val(COS_INT this);
void cos_int_print(COS_INT this);

#endif
