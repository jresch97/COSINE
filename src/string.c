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

static int _cos_string_equals(cos_object obj1, cos_object obj2)
{
        cos_string str1, str2;
        str1 = (cos_string)obj1;
        str2 = (cos_string)obj2;
        return strcmp(str1->c_str, str2->c_str) == 0;
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
        cos_object_class_init(cls);
        objcls = (cos_object_class)cls;
        objcls->hash = _cos_string_hash;
        objcls->equals = _cos_string_equals;
        objcls->to_string = _cos_string_to_string;
}

void cos_string_class_term(cos_class cls)
{
        cos_object_class_term(cls);
        if (g_cls == cls) g_cls = NULL;
}

void cos_string_init(cos_object obj, cos_args args)
{
        cos_string str;
        const char *c_str;
        cos_super(COS_OBJECT, obj);
        str = (cos_string)obj;
        c_str = cos_arg(args, const char *);
        str->len = strlen(c_str);
        str->c_str = malloc(str->len + 1);
        strcpy(str->c_str, c_str);
}

void cos_string_term(cos_object obj)
{
        free(((cos_string)obj)->c_str);
        cos_object_term(obj);
}

cos_string cos_string_join(cos_string str1, cos_string str2)
{
        char *c_str;
        cos_string str;
        c_str = malloc(str1->len + str2->len + 1);
        strcpy(c_str, str1->c_str);
        strcpy(c_str + str1->len, str2->c_str);
        str = cos_new_string(c_str);
        free(c_str);
        return str;
}

cos_string cos_string_join_many(size_t n, ...)
{
        size_t i, j, len;
        char *c_str;
        va_list args;
        cos_string str, *strs;
        len = 1;
        strs = malloc(n * sizeof(*strs));
        va_start(args, n);
        for (i = 0; i < n; i++) {
                strs[i] = va_arg(args, cos_string);
                len += strs[i]->len;
        }
        va_end(args);
        c_str = malloc(len);
        for (i = 0, j = 0; i < n; i++) {
                strcpy(c_str + j, strs[i]->c_str);
                j += strs[i]->len;
        }
        str = cos_new_string(c_str);
        free(c_str);
        free(strs);
        return str;
}