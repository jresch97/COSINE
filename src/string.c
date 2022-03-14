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
        int c;
        size_t h = 5381;
        const char *c_str;
        c_str = ((cos_string)obj)->c_str;
        while ((c = *c_str++)) h = ((h << 5) + h) + c;
        return h;
}

static int _cos_string_equals(cos_object obj, cos_object other)
{
        return strcmp(((cos_string)obj)->c_str,
                      ((cos_string)other)->c_str) == 0;
}

static cos_string _cos_string_to_string(cos_object obj)
{
        return cos_ref(obj);
}

cos_string cos_new_string(const char *c_str)
{
        return cos_new(COS_STRING, c_str);
}

cos_class cos_string_class_get()
{
        cos_class_spec spec;
        if (g_cls) return g_cls;
        spec.cls_name = "COS_STRING";
        spec.parent_cls = COS_OBJECT;
        spec.cls_size = sizeof(struct cos_string_class_s);
        spec.obj_size = sizeof(struct cos_string_s);
        spec.cls_init_fn = cos_string_class_init;
        spec.cls_term_fn = cos_string_class_term;
        spec.obj_init_fn = cos_string_init;
        spec.obj_term_fn = cos_string_term;
        return cos_def_class(&spec);
}

void cos_string_class_init(cos_class cls)
{
        cos_object_class objcls;
        if (!g_cls) g_cls = cls;
        objcls = (cos_object_class)cls;
        objcls->hash = _cos_string_hash;
        objcls->equals = _cos_string_equals;
        objcls->to_string = _cos_string_to_string;
}

void cos_string_class_term(cos_class cls)
{
        if (g_cls == cls) g_cls = NULL;
}

void cos_string_init(cos_object obj, cos_args args)
{
        cos_string str;
        const char *c_str;
        cos_super(obj);
        str = (cos_string)obj;
        c_str = cos_arg(args, const char *);
        str->len = strlen(c_str);
        str->c_str = malloc(str->len + 1);
        strcpy(str->c_str, c_str);
}

void cos_string_term(cos_object obj)
{
        free(((cos_string)obj)->c_str);
}
