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

#include <assert.h>
#include <stdlib.h>

#include "value.h"

COS_VALUE cos_box_void()
{
        COS_VALUE val;
        val.type      = COS_TYPE_VOID;
        val.data.size = 0;
        return val;
}

void cos_unbox_void(COS_VALUE val)
{
        assert(val.type == COS_TYPE_VOID);
}

COS_VALUE cos_box_class(COS_CLASS class)
{
        COS_VALUE val;
        val.type       = COS_TYPE_CLASS;
        val.data.class = class;
        return val;
}

COS_CLASS cos_unbox_class(COS_VALUE val)
{
        assert(val.type == COS_TYPE_CLASS);
        return val.data.class;
}

COS_VALUE cos_box_object(COS_OBJECT obj)
{
        COS_VALUE val;
        val.type     = COS_TYPE_OBJECT;
        val.data.obj = obj;
        return val;
}

COS_OBJECT cos_unbox_object(COS_VALUE val)
{
        assert(val.type == COS_TYPE_OBJECT);
        return val.data.obj;
}

COS_VALUE cos_box_char(char s_char)
{
        COS_VALUE val;
        val.type        = COS_TYPE_CHAR;
        val.data.s_char = s_char;
        return val;
}

char cos_unbox_char(COS_VALUE val)
{
        assert(val.type == COS_TYPE_CHAR);
        return val.data.s_char;
}

COS_VALUE cos_box_short(short s_short)
{
        COS_VALUE val;
        val.type       = COS_TYPE_SHORT;
        val.data.s_short = s_short;
        return val;
}

short cos_unbox_short(COS_VALUE val)
{
        assert(val.type == COS_TYPE_SHORT);
        return val.data.s_short;
}

COS_VALUE cos_box_int(int s_int)
{
        COS_VALUE val;
        val.type       = COS_TYPE_INT;
        val.data.s_int = s_int;
        return val;
}

int cos_unbox_int(COS_VALUE val)
{
        assert(val.type == COS_TYPE_INT);
        return val.data.s_int;
}

struct COS_VALUES_S {
        size_t     i, len;
        COS_VALUE *data;
};

COS_VALUES cos_values_alloc(size_t len)
{
        COS_VALUES vals = malloc(sizeof(*vals));
        vals->i = 0;
        vals->len = len;
        vals->data = malloc(len * sizeof(*vals->data));
        return vals;
}

void cos_values_free(COS_VALUES vals)
{
        if (vals) free(vals->data);
        free(vals);
}

size_t cos_values_len(COS_VALUES vals)
{
        return vals->len;
}

COS_VALUE cos_values_at(COS_VALUES vals, size_t i)
{
        assert(i < vals->len);
        return vals->data[i];
}

void cos_values_store(COS_VALUES vals, COS_VALUE value)
{
        assert(vals->i < vals->len);
        vals->data[vals->i++] = value;
}

void cos_values_reset(COS_VALUES vals)
{
        vals->i = 0;
}
