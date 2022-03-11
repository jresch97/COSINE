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

#include "int.h"
#include "param.h"
#include "value.h"

static cos_class g_cos_int_class = NULL;

cos_class cos_int_class_get()
{
        cos_class cls;
        cos_class_spec spec;
        if (g_cos_int_class) return g_cos_int_class;
        if (cos_class_lookup(COS_INT_NAME, &cls)) return cls;
        spec.name        = COS_INT_NAME;
        spec.parent      = COS_OBJECT;
        spec.cls.size    = sizeof(struct cos_int_class_s);
        spec.cls.ctor    = cos_int_class_construct;
        spec.cls.dtor    = cos_int_class_destruct;
        spec.inst.size   = sizeof(struct cos_int_s);
        spec.inst.ctor   = cos_int_construct;
        spec.inst.dtor   = cos_int_destruct;
        spec.inst.params = cos_params_list(1, "value", COS_TYPE_INT);
        return cos_class_define(&spec);
}

void cos_int_class_construct(cos_class cls)
{
        g_cos_int_class = cls;
        cos_super_class_construct(COS_OBJECT);
}

void cos_int_class_destruct(cos_class cls)
{
        g_cos_int_class = NULL;
        cos_super_class_destruct(COS_OBJECT);
}

void cos_int_construct(cos_object obj, cos_values vals)
{
        cos_super_construct(COS_OBJECT, obj);
        COS_INT_VAL(obj) = cos_unbox_int(cos_values_at(vals, 0));
}

void cos_int_destruct(cos_object obj)
{
        /* Nothing to do. */
}

cos_int cos_int_sum(size_t n, ...)
{
        size_t i;
        int sum = 0;
        va_list args;
        va_start(args, n);
        for (i = 0; i < n; i++) {
                sum += COS_INT_VAL(va_arg(args, cos_int));
        }
        va_end(args);
        return COS_INT_CAST(cos_new(COS_INT, sum));
}