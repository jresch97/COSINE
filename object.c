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

#include "value.h"
#include "param.h"
#include "object.h"

/* TODO: Keep buffer of COS_VALUES in COS_CLASS to avoid allocations. */

COS_CLASS cos_obj_class_get()
{
        COS_CLASS class;
        COS_CLASS_INFO info;
        if (cos_class_lookup(COS_OBJECT_CLASS_NAME, &class)) return class;
        info.name = COS_OBJECT_CLASS_NAME;
        info.parent = NULL;
        info.class.size = sizeof(struct COS_OBJECT_CLASS_S);
        info.class.ctor = cos_obj_class_ctor;
        info.class.dtor = cos_obj_class_dtor;
        info.inst.size = sizeof(struct COS_OBJECT_S);
        info.inst.ctor = cos_obj_ctor;
        info.inst.dtor = cos_obj_dtor;
        info.inst.params = cos_params_alloc(1);
        cos_params_store(info.inst.params,
                cos_param_alloc("class", COS_TYPE_CLASS));
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

COS_OBJECT cos_new(COS_CLASS class, ...)
{
        size_t i, n_params;
        va_list args;
        COS_OBJECT obj;
        COS_VALUES vals;
        COS_PARAMS params;
        COS_PARAM param;
        obj = malloc(class->inst.size);
        obj->class = class;
        params = class->inst.params;
        n_params = cos_params_len(params);
        vals = class->inst.vals;
        cos_values_reset(vals);
        va_start(args, class);
        for (i = 0; i < n_params; i++) {
                param = cos_params_at(params, i);
                switch (cos_param_type(param)) {
                        case COS_TYPE_CLASS:
                                cos_values_store(vals,
                                        cos_box_class(va_arg(args, COS_CLASS)));
                                break;
                        case COS_TYPE_INT:
                                cos_values_store(vals,
                                        cos_box_int(va_arg(args, int)));
                                break;
                }
        }
        va_end(args);
        class->inst.ctor(obj, vals);
        return obj;
}

COS_OBJECT cos_ref(COS_OBJECT obj)
{
        obj->n_refs++;
        return obj;
}

void cos_deref(COS_OBJECT obj)
{
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
        for (i = 0; i < n; i++) cos_deref(va_arg(args, COS_OBJECT));
        va_end(args);
}

void cos_super(COS_OBJECT obj, ...)
{
        size_t i, n_params;
        va_list args;
        COS_CLASS class, parent;
        COS_PARAMS params;
        COS_PARAM param;
        COS_VALUES vals;
        class = obj->class;
        parent = class->parent;
        if (parent) {
                params = parent->inst.params;
                n_params = cos_params_len(params);
                vals = parent->inst.vals;
                cos_values_reset(vals);
                va_start(args, obj);
                for (i = 0; i < n_params; i++) {
                        param = cos_params_at(params, i);
                        switch (cos_param_type(param)) {
                                case COS_TYPE_CLASS:
                                        cos_values_store(vals, cos_box_class(
                                                va_arg(args, COS_CLASS)));
                                        break;
                                case COS_TYPE_INT:
                                        cos_values_store(vals, cos_box_int(
                                                va_arg(args, int)));
                                        break;
                        }
                }
                va_end(args);
        }
        parent->inst.ctor(obj, vals);
}
