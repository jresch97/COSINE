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

struct COS_VALUE_S {
        int type;
        union {
                COS_CLASS      class;
                COS_OBJECT     obj;
                const char    *c_str;
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

COS_VALUE   cos_box(int type, void *ptr);
COS_VALUE   cos_box_void();
void        cos_unbox_void(COS_VALUE val);
COS_VALUE   cos_box_class(COS_CLASS class);
COS_CLASS   cos_unbox_class(COS_VALUE val);
COS_VALUE   cos_box_object(COS_OBJECT obj);
COS_OBJECT  cos_unbox_object(COS_VALUE val);
COS_VALUE   cos_box_c_str(const char *c_str);
const char *cos_unbox_c_str(COS_VALUE val);
COS_VALUE   cos_box_char(char s_char);
char        cos_unbox_char(COS_VALUE val);
COS_VALUE   cos_box_short(short s_short);
short       cos_unbox_short(COS_VALUE val);
COS_VALUE   cos_box_int(int s_int);
int         cos_unbox_int(COS_VALUE val);

COS_VALUES cos_values_alloc(size_t len);
void       cos_values_free(COS_VALUES vals);
size_t     cos_values_len(COS_VALUES vals);
size_t     cos_values_len(COS_VALUES vals);
COS_VALUE  cos_values_at(COS_VALUES vals, size_t i);
void       cos_values_store(COS_VALUES vals, COS_VALUE val);
void       cos_values_reset(COS_VALUES vals);

#endif
