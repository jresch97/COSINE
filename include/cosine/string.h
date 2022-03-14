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

#include "class.h"
#include "object.h"

#define COS_STRING (cos_string_class_get())

struct cos_string_class_s {
        struct cos_object_class_s class;
};

struct cos_string_s {
        struct cos_object_s object;
};

cos_object cos_new_object();

cos_class  cos_get_object_class();
void       cos_init_object_class(cos_class class);
void       cos_term_object_class(cos_class class);
void       cos_init_object(cos_object object, cos_values values);
void       cos_term_object(cos_object object);

int        cos_object_equals(cos_object object, cos_object other);
size_t     cos_object_hash(cos_object object);
cos_string cos_object_to_string(cos_object object);

#endif
