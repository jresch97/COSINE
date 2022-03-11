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

#include <cosine.h>

#define COS_INT_NAME       "Integer"
#define COS_INT            (cos_int_class_get())
#define COS_INT_CAST(obj)  ((cos_int)obj)
#define COS_INT_VAL(obj)   COS_INT_CAST(obj)->val

typedef struct cos_int_class_s *cos_int_class;
typedef struct cos_int_s       *cos_int;

struct cos_int_class_s {
        struct cos_class_s cls;
};

struct cos_int_s {
        struct cos_object_s obj;
        int                 val;
};

cos_class cos_int_class_get();
void      cos_int_class_construct(cos_class cls);
void      cos_int_class_destruct(cos_class cls);
void      cos_int_construct(cos_object obj, cos_values values);
void      cos_int_destruct(cos_object obj);
cos_int   cos_int_sum(size_t n, ...);

#endif
