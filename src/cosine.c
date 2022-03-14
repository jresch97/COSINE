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
#include <stdlib.h>
#include <string.h>

#include "cosine.h"

void *cos_new(cos_class cls, ...)
{
        va_list args;
        cos_object obj = malloc(cls->obj_size);
        if (!obj) return NULL;
        obj->cls = cos_ref_class(cls);
        va_start(args, cls);
        cls->obj_init_fn(obj, args);
        va_end(args);
        return obj;
}

void *cos_ref(void *obj)
{
        ((cos_object)obj)->n_refs++;
        return obj;
}

void cos_deref(void *obj)
{
        cos_object tmp;
        tmp = (cos_object)obj;
        if (tmp && --tmp->n_refs == 0) {
                tmp->cls->obj_term_fn(tmp);
                cos_deref_class(tmp->cls);
                free(tmp);
        }
}

void cos_deref_many(size_t n, ...)
{
        size_t i;
        va_list args;
        va_start(args, n);
        for (i = 0; i < n; i++) cos_deref(va_arg(args, void *));
        va_end(args);
}

void cos_super(void *obj, ...)
{
        va_list args;
        cos_class parent_cls;
        assert(obj);
        parent_cls = ((cos_object)obj)->cls->parent_cls;
        assert(parent_cls);
        va_start(args, obj);
        parent_cls->obj_init_fn(obj, args);
        va_end(args);
}

cos_class cos_class_of(void *obj)
{
        assert(obj);
        return ((cos_object)obj)->cls;
}

cos_class cos_def_class(cos_class_spec *spec)
{
        cos_class cls;
        assert(spec);
        cls = malloc(spec->cls_size);
        if (!cls) return NULL;
        cls->n_refs = 0;
        cls->cls_name = malloc(strlen(spec->cls_name) + 1);
        if (!cls->cls_name) {
                free(cls);
                return NULL;
        }
        strcpy(cls->cls_name, spec->cls_name);
        cls->cls_size = spec->cls_size;
        cls->obj_size = spec->obj_size;
        cls->parent_cls = spec->parent_cls;
        cls->cls_init_fn = spec->cls_init_fn;
        cls->cls_term_fn = spec->cls_term_fn;
        cls->obj_init_fn = spec->obj_init_fn;
        cls->obj_term_fn = spec->obj_term_fn;
        cls->cls_init_fn(cls);
        return cls;
}

cos_class cos_ref_class(cos_class cls)
{
        cls->n_refs++;
        return cls;
}

void cos_deref_class(cos_class cls)
{
        if (cls && --cls->n_refs == 0) {
                cls->cls_term_fn(cls);
                free(cls->cls_name);
                free(cls);
        }
}
