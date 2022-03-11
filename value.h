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

#ifndef COS_VALUE_H
#define COS_VALUE_H

#include <stddef.h>

#include "type.h"

struct cos_value_s {
        int type;
        union {
                cos_class      cls;
                cos_object     obj;
                const char    *str;
                char           s_char;
                short          s_short;
                int            s_int;
                long           s_long;
                unsigned char  u_char;
                unsigned short u_short;
                unsigned int   u_int;
                unsigned long  u_long;
                size_t         size;
        } data;
};

cos_value   cos_box(int type, void *ptr);
cos_value   cos_box_void();
void        cos_unbox_void(cos_value val);
cos_value   cos_box_class(cos_class cls);
cos_class   cos_unbox_class(cos_value val);
cos_value   cos_box_object(cos_object obj);
cos_object  cos_unbox_object(cos_value val);
cos_value   cos_box_string(const char *str);
const char *cos_unbox_string(cos_value val);
cos_value   cos_box_char(char s_char);
char        cos_unbox_char(cos_value val);
cos_value   cos_box_short(short s_short);
short       cos_unbox_short(cos_value val);
cos_value   cos_box_int(int s_int);
int         cos_unbox_int(cos_value val);
cos_values  cos_values_alloc(size_t len);
void        cos_values_free(cos_values vals);
size_t      cos_values_len(cos_values vals);
size_t      cos_values_len(cos_values vals);
cos_value   cos_values_at(cos_values vals, size_t i);
void        cos_values_store(cos_values vals, cos_value val);
void        cos_values_reset(cos_values vals);
 
#endif
