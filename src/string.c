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
#include <string.h>

#include "cosine.h"
#include "cosine/string.h"

static cos_class g_cls = NULL;

static size_t _cos_string_hash(cos_object obj)
{
        return (size_t)obj;
}

static int _cos_string_equals(cos_object obj, cos_object other)
{
        return strcmp(((cos_string)obj)->c_str,
                      ((cos_string)other)->c_str) == 0;
}

static cos_string _cos_string_to_string(cos_object obj)
{
        return (cos_string)obj;
}

cos_string cos_new_string(const char *c_str)
{
        return cos_new(COS_STRING, c_str);
}

cos_class cos_string_class_get()
{
        cos_class_spec spec;
        if (g_cls) return g_cls;
        spec.cls_name = "String";
        spec.parent_cls = NULL;
        spec.cls_size = sizeof(struct cos_string_class_s);
        spec.obj_size = sizeof(struct cos_string_s);
        spec.cls_init_fn = cos_string_class_init;
        spec.cls_term_fn = cos_string_class_term;
        spec.obj_init_fn = cos_string_init;
        spec.obj_term_fn = cos_string_term;
        spec.n_init_params = 1;
        spec.init_params = malloc(spec.n_init_params * sizeof(*spec.init_params));
        spec.init_params[0].type = COS_STRING_TYPE;
        return cos_def_class(&spec);
}

void cos_string_class_init(cos_class cls)
{
        assert(cls);
        if (!g_cls) g_cls = cls;
        ((cos_object_class)cls)->hash = _cos_string_hash;
        ((cos_object_class)cls)->equals = _cos_string_equals;
        ((cos_object_class)cls)->to_string = _cos_string_to_string;
}

void cos_string_class_term(cos_class cls)
{
        assert(cls);
        if (g_cls == cls) g_cls = NULL;
}

void cos_string_init(cos_object obj, size_t n_params, cos_param *params)
{
        assert(n_params == 1);
        assert(params);
        cos_super(obj);
        ((cos_string)obj)->len = strlen(params[0].data.str);
        ((cos_string)obj)->c_str = malloc(((cos_string)obj)->len + 1);
        strcpy(((cos_string)obj)->c_str, params[0].data.str);
}

void cos_string_term(cos_object obj)
{
        free(((cos_string)obj)->c_str);
}
