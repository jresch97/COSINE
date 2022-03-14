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
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "cosine.h"
#include "cosine/object.h"
#include "cosine/string.h"

static cos_class g_cls = NULL;

static size_t _cos_object_hash(cos_object obj)
{
        return (size_t)obj;
}

static int _cos_object_equals(cos_object obj, cos_object other)
{
        return obj == other;
}

static cos_string _cos_object_to_string(cos_object obj)
{
        return cos_new_string(obj->cls->cls_name);
}

cos_object cos_new_object()
{
        return cos_new(COS_OBJECT);
}

cos_class cos_object_class_get()
{
        cos_class_spec spec;
        if (g_cls) return g_cls;
        spec.cls_name = "COS_OBJECT";
        spec.parent_cls = NULL;
        spec.cls_size = sizeof(struct cos_object_class_s);
        spec.obj_size = sizeof(struct cos_object_s);
        spec.cls_init_fn = cos_object_class_init;
        spec.cls_term_fn = cos_object_class_term;
        spec.obj_init_fn = cos_object_init;
        spec.obj_term_fn = cos_object_term;
        return cos_def_class(&spec);
}

void cos_object_class_init(cos_class cls)
{
        cos_object_class obj_cls;
        if (!g_cls) g_cls = cls;
        obj_cls = (cos_object_class)cls;
        obj_cls->hash = _cos_object_hash;
        obj_cls->equals = _cos_object_equals;
        obj_cls->to_string = _cos_object_to_string;
}

void cos_object_class_term(cos_class cls)
{
        if (g_cls == cls) g_cls = NULL;
}

void cos_object_init(cos_object obj, cos_args args)
{
        obj->n_refs = 1;
}

void cos_object_term(cos_object obj)
{

}

size_t cos_object_hash(cos_object obj)
{
        return ((cos_object_class)obj->cls)->hash(obj);
}

int cos_object_equals(cos_object obj, cos_object other)
{
        return ((cos_object_class)obj->cls)->equals(obj, other);
}

cos_string cos_object_to_string(cos_object obj)
{
        return ((cos_object_class)obj->cls)->to_string(obj);
}

