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

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "value.h"
#include "param.h"
#include "object.h"

COS_CLASS cos_obj_class_get()
{
        static COS_CLASS class = NULL;
        COS_CLASS_INFO info;
        if (class) return class;
        if (cos_class_lookup(COS_OBJECT_CLASS_NAME, &class)) return class;
        info.name = COS_OBJECT_CLASS_NAME;
        info.parent = NULL;
        info.class.size = sizeof(struct COS_OBJECT_CLASS_S);
        info.class.ctor = cos_obj_class_ctor;
        info.class.dtor = cos_obj_class_dtor;
        info.inst.size = sizeof(struct COS_OBJECT_S);
        info.inst.ctor = cos_obj_ctor;
        info.inst.dtor = cos_obj_dtor;
        info.inst.params = cos_params_alloc(0);
        return cos_class_define(&info);
}

void cos_obj_class_ctor(COS_CLASS class)
{
        /* Nothing to do. */
}

void cos_obj_class_dtor(COS_CLASS class)
{
        /* Nothing to do. */
}

void cos_obj_ctor(COS_OBJECT this, COS_VALUES values)
{
        this->n_refs = 1;
}

void cos_obj_dtor(COS_OBJECT this)
{
        /* Nothing to do. */
}

int cos_obj_n_refs(COS_OBJECT this)
{
        return this->n_refs;
}

COS_CLASS cos_obj_class(COS_OBJECT this)
{
        return this->class;
}

void *cos_new(COS_CLASS class, ...)
{
        int type;
        va_list args;
        size_t i, arg;
        COS_OBJECT obj;
        COS_VALUES vals;
        COS_PARAMS params;
        obj = malloc(class->inst.size);
        obj->class = class;
        vals = class->inst.vals;
        cos_values_reset(vals);
        params = class->inst.params;
        va_start(args, class);
        for (i = 0; i < cos_params_len(params); i++) {
                arg = va_arg(args, size_t);
                type = cos_param_type(cos_params_at(params, i));
                cos_values_store(vals, cos_box(type, &arg));
        }
        va_end(args);
        class->inst.ctor(obj, vals);
        return obj;
}

void *cos_ref(void *ptr)
{
        COS_OBJECT_CAST(ptr)->n_refs++;
        return ptr;
}

void cos_deref(void *ptr)
{
        COS_OBJECT obj = COS_OBJECT_CAST(ptr);
        if (--obj->n_refs == 0) {
                obj->class->inst.dtor(obj);
                free(obj);
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

void cos_super_class_ctor(COS_CLASS parent)
{
        if (parent) parent->class.ctor(parent);
}

void cos_super_class_dtor(COS_CLASS parent)
{
        if (parent) parent->class.dtor(parent);
}

void cos_super_ctor(COS_CLASS parent, void *ptr, ...)
{
        int type;
        va_list args;
        size_t i, arg;
        COS_VALUES vals;
        COS_PARAMS params;
        if (!parent) return;
        vals = parent->inst.vals;
        cos_values_reset(vals);
        params = parent->inst.params;
        va_start(args, ptr);
        for (i = 0; i < cos_params_len(params); i++) {
                arg = va_arg(args, size_t);
                type = cos_param_type(cos_params_at(params, i));
                cos_values_store(vals, cos_box(type, &arg));
        }
        va_end(args);
        parent->inst.ctor(COS_OBJECT_CAST(ptr), vals);
}

void cos_super_dtor(COS_CLASS parent, void *ptr)
{
        if (parent) parent->inst.dtor(COS_OBJECT_CAST(ptr));
}
