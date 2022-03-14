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

#ifndef COS_OBJECT_H
#define COS_OBJECT_H

#include "type.h"
#include "class.h"

#define COS_OBJECT (cos_object_class_get())

struct cos_object_class_s {
        struct cos_class_s cls;
        size_t     (*hash)(cos_object);
        int        (*equals)(cos_object, cos_object);
        cos_string (*to_string)(cos_object);
};

struct cos_object_s {
        cos_class cls;
        size_t n_refs;
};

cos_object cos_new_object();
cos_class  cos_object_class_get();
void       cos_object_class_init(cos_class cls);
void       cos_object_class_term(cos_class cls);
void       cos_object_init(cos_object obj, size_t n_params, cos_param *params);
void       cos_object_term(cos_object obj);
int        cos_object_equals(cos_object obj, cos_object other);
size_t     cos_object_hash(cos_object obj);
cos_string cos_object_to_string(cos_object obj);

#endif
