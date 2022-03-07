/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of COSINE.
 * 
 * COSINE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Founentsion, either version 3 of the
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

#include <assert.h>

#include "types.h"
#include "object.h"

typedef struct COS_VALUE_S {
        int type;
        union {
                void          *ptr;
                char           s_char;
                short          s_short;
                int            s_int;
                long           s_long;
                unsigned char  u_char;
                unsigned short u_short;
                unsigned int   u_int;
                unsigned long  u_long;
                float          s_float;
                double         d_float;
                size_t         size;
        } data;
} COS_VALUE;

COS_VALUE cos_box_void()
{
        COS_VALUE value;
        value.type = COS_TYPE_VOID;
        value.data.size = 0;
        return value;
}

COS_VALUE cos_box_ptr(void *ptr)
{
        COS_VALUE value;
        value.type = COS_TYPE_POINTER;
        value.data.ptr = ptr;
        return value;
}

void *cos_unbox_ptr(COS_VALUE value)
{
        assert(value.type == COS_TYPE_POINTER);
        return value.data.ptr;
}

COS_VALUE cos_box_char(char s_char)
{
        COS_VALUE value;
        value.type = COS_TYPE_CHAR;
        value.data.s_char = s_char;
        return value;
}

char cos_unbox_char(COS_VALUE value)
{
        assert(value.type == COS_TYPE_CHAR);
        return value.data.s_char;
}

COS_VALUE cos_box_short(char s_short)
{
        COS_VALUE value;
        value.type = COS_TYPE_SHORT;
        value.data.s_short = s_short;
        return value;
}

short cos_unbox_short(COS_VALUE value)
{
        assert(value.type == COS_TYPE_SHORT);
        return value.data.s_short;
}

COS_VALUE cos_box_int(int s_int)
{
        COS_VALUE value;
        value.type = COS_TYPE_INT;
        value.data.s_int = s_int;
        return value;
}

int cos_unbox_int(COS_VALUE value)
{
        assert(value.type == COS_TYPE_INT);
        return value.data.s_int;
}

COS_VALUE cos_box_long(long s_long)
{
        COS_VALUE value;
        value.type = COS_TYPE_LONG;
        value.data.s_long = s_long;
        return value;
}

long cos_unbox_long(COS_VALUE value)
{
        assert(value.type == COS_TYPE_LONG);
        return value.data.s_long;
}

COS_VALUE cos_box_unsigned_char(unsigned char u_char)
{
        COS_VALUE value;
        value.type = COS_TYPE_UNSIGNED_CHAR;
        value.data.u_char = u_char;
        return value;
}

unsigned char cos_unbox_unsigned_char(COS_VALUE value)
{
        assert(value.type == COS_TYPE_UNSIGNED_CHAR);
        return value.data.u_char;
}

COS_VALUE cos_box_unsigned_short(unsigned short u_short)
{
        COS_VALUE value;
        value.type = COS_TYPE_UNSIGNED_SHORT;
        value.data.u_short = u_short;
        return value;
}

unsigned short cos_unbox_unsigned_short(COS_VALUE value)
{
        assert(value.type == COS_TYPE_UNSIGNED_SHORT);
        return value.data.u_short;
}

COS_VALUE cos_box_unsigned_int(unsigned int u_int)
{
        COS_VALUE value;
        value.type = COS_TYPE_UNSIGNED_INT;
        value.data.u_int = u_int;
        return value;
}

unsigned int cos_unbox_unsigned_int(COS_VALUE value)
{
        assert(value.type == COS_TYPE_UNSIGNED_INT);
        return value.data.u_int;
}

COS_VALUE cos_box_unsigned_long(unsigned long u_long)
{
        COS_VALUE value;
        value.type = COS_TYPE_UNSIGNED_LONG;
        value.data.u_long = u_long;
        return value;
}

unsigned long cos_unbox_unsigned_long(COS_VALUE value)
{
        assert(value.type == COS_TYPE_UNSIGNED_LONG);
        return value.data.u_long;
}

COS_VALUE cos_box_float(double s_float)
{
        COS_VALUE value;
        value.type = COS_TYPE_FLOAT;
        value.data.s_float = s_float;
        return value;
}

float cos_unbox_float(COS_VALUE value)
{
        assert(value.type == COS_TYPE_FLOAT);
        return value.data.s_float;
}

COS_VALUE cos_box_double(double d_float)
{
        COS_VALUE value;
        value.type = COS_TYPE_DOUBLE;
        value.data.d_float = d_float;
        return value;
}

double cos_unbox_double(COS_VALUE value)
{
        assert(value.type == COS_TYPE_DOUBLE);
        return value.data.d_float;
}

COS_VALUE cos_box_size(size_t size)
{
        COS_VALUE value;
        value.type = COS_TYPE_SIZE;
        value.data.size = size;
        return value;
}

size_t cos_unbox_size(COS_VALUE value)
{
        assert(value.type == COS_TYPE_SIZE);
        return value.data.size;
}

#endif
