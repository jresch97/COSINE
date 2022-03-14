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

#include "type.h"
#include "class.h"

#define COS_STRING (cos_string_class_get())

struct cos_string_class_s {
        struct cos_object_class_s cls;
};

struct cos_string_s {
        struct cos_object_s obj;
        size_t len;
        char  *c_str;
};

cos_string cos_new_string(const char *c_str);
cos_class  cos_string_class_get();
void       cos_string_class_init(cos_class cls);
void       cos_string_class_term(cos_class cls);
void       cos_string_init(cos_object obj, size_t n_params, cos_param *params);
void       cos_string_term(cos_object obj);

#endif
