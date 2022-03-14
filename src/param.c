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

cos_value cos_box(int type, void *ptr)
{
        switch (type) {
                case COS_TYPE_VOID:   return cos_box_void();
                case COS_TYPE_CLASS:  return cos_box_class(*((cos_class *)ptr));
                case COS_TYPE_OBJECT: return cos_box_object(*((cos_object *)ptr));
                case COS_TYPE_STRING: return cos_box_string(*((const char **)ptr));
                case COS_TYPE_INT:    return cos_box_int(*((int *)ptr));
                default: assert(0 && "Unknown type.");
        }
        return cos_box_void();
}

cos_value cos_box_void()
{
        cos_value val;
        val.type      = COS_TYPE_VOID;
        val.data.size = 0;
        return val;
}

void cos_unbox_void(cos_value val)
{
        assert(val.type == COS_TYPE_VOID);
}

cos_value cos_box_class(cos_class cls)
{
        cos_value val;
        val.type     = COS_TYPE_CLASS;
        val.data.cls = cls;
        return val;
}

cos_class cos_unbox_class(cos_value val)
{
        assert(val.type == COS_TYPE_CLASS);
        return val.data.cls;
}

cos_value cos_box_object(cos_object obj)
{
        cos_value val;
        val.type     = COS_TYPE_OBJECT;
        val.data.obj = obj;
        return val;
}

cos_object cos_unbox_object(cos_value val)
{
        assert(val.type == COS_TYPE_OBJECT);
        return val.data.obj;
}

cos_value cos_box_string(const char *str)
{
        cos_value val;
        val.type     = COS_TYPE_STRING;
        val.data.str = str;
        return val;
}

const char *cos_unbox_string(cos_value val)
{
        assert(val.type == COS_TYPE_STRING);
        return val.data.str;
}

cos_value cos_box_char(char s_char)
{
        cos_value val;
        val.type        = COS_TYPE_CHAR;
        val.data.s_char = s_char;
        return val;
}

char cos_unbox_char(cos_value val)
{
        assert(val.type == COS_TYPE_CHAR);
        return val.data.s_char;
}

cos_value cos_box_short(short s_short)
{
        cos_value val;
        val.type       = COS_TYPE_SHORT;
        val.data.s_short = s_short;
        return val;
}

short cos_unbox_short(cos_value val)
{
        assert(val.type == COS_TYPE_SHORT);
        return val.data.s_short;
}

cos_value cos_box_int(int s_int)
{
        cos_value val;
        val.type       = COS_TYPE_INT;
        val.data.s_int = s_int;
        return val;
}

int cos_unbox_int(cos_value val)
{
        assert(val.type == COS_TYPE_INT);
        return val.data.s_int;
}

struct cos_values_s {
        size_t     i, len;
        cos_value *data;
};

cos_values cos_values_alloc(size_t len)
{
        cos_values vals = malloc(sizeof(*vals));
        vals->i = 0;
        vals->len = len;
        vals->data = malloc(len * sizeof(*vals->data));
        return vals;
}

void cos_values_free(cos_values vals)
{
        if (vals) free(vals->data);
        free(vals);
}

size_t cos_values_len(cos_values vals)
{
        return vals->len;
}

cos_value cos_values_at(cos_values vals, size_t i)
{
        assert(i < vals->len);
        return vals->data[i];
}

void cos_values_store(cos_values vals, cos_value value)
{
        assert(vals->i < vals->len);
        vals->data[vals->i++] = value;
}

void cos_values_reset(cos_values vals)
{
        vals->i = 0;
}
