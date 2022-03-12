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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "value.h"
#include "param.h"
#include "object.h"

static cos_class g_cos_object_class = NULL;

cos_class cos_object_class_get()
{
        cos_class cls;
        cos_class_spec spec;
        if (g_cos_object_class) return g_cos_object_class;
        if (cos_class_lookup(COS_OBJECT_NAME, &cls)) return cls;
        spec.name        = COS_OBJECT_NAME;
        spec.parent      = NULL;
        spec.cls.size    = sizeof(struct cos_object_class_s);
        spec.cls.ctor    = cos_object_class_construct;
        spec.cls.dtor    = cos_object_class_destruct;
        spec.inst.size   = sizeof(struct cos_object_s);
        spec.inst.ctor   = cos_object_construct;
        spec.inst.dtor   = cos_object_destruct;
        spec.inst.params = cos_params_alloc(0); /*cos_params_list(0);*/
        return cos_class_define(&spec);
}

void cos_object_class_construct(cos_class cls)
{
        if (!g_cos_object_class) g_cos_object_class = cls;
}

void cos_object_class_destruct(cos_class cls)
{
        if (g_cos_object_class == cls) g_cos_object_class = NULL;
}

void cos_object_construct(cos_object obj, cos_values vals)
{
        COS_OBJECT_N_REFS(obj) = 1;
}

void cos_object_destruct(cos_object obj)
{
        /* Nothing to do. */
}

/* TODO: Move to cosine? */

static void cos_store_args(va_list args, cos_params params, cos_values vals)
{
        int type;
        cos_param param;
        size_t i, arg, n_params;
        cos_values_reset(vals);
        n_params = cos_params_len(params);
        for (i = 0; i < n_params; i++) {
                param = cos_params_at(params, i);
                arg   = va_arg(args, size_t);
                type  = cos_param_type(param);
                cos_values_store(vals, cos_box(type, &arg));
        }
}

void *cos_new(cos_class cls, ...)
{
        va_list args;
        cos_object obj;
        cos_values vals;
        obj = malloc(cls->inst.size);
        obj->cls = cls;
        vals = cls->inst.vals;
        va_start(args, cls);
        cos_store_args(args, cls->inst.params, vals);
        va_end(args);
        cls->inst.ctor(obj, vals);
        return obj;
}

void *cos_ref(void *obj)
{
        COS_OBJECT_CAST(obj)->n_refs++;
        return obj;
}

void cos_deref(void *obj)
{
        cos_object inst = COS_OBJECT_CAST(obj);
        if (--inst->n_refs == 0) {
                inst->cls->inst.dtor(inst);
                free(inst);
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

void cos_super_class_construct(cos_class parent, void *cls)
{
        parent->cls.ctor(COS_CLASS_CAST(cls));
}

void cos_super_class_destruct(cos_class parent, void *cls)
{
        parent->cls.dtor(COS_CLASS_CAST(cls));
}

void cos_super_construct(cos_class parent, void *obj, ...)
{
        va_list args;
        cos_values vals;
        vals = parent->inst.vals;
        va_start(args, obj);
        cos_store_args(args, parent->inst.params, vals);
        va_end(args);
        parent->inst.ctor(COS_OBJECT_CAST(obj), vals);
}

void cos_super_destruct(cos_class parent, void *obj)
{
        parent->inst.dtor(COS_OBJECT_CAST(obj));
}
