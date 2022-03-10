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

COS_CLASS cos_int_class_get()
{
        COS_CLASS class;
        COS_CLASS_INFO info;
        if (cos_class_lookup(COS_INT_CLASS_NAME, &class)) return class;
        info.name = COS_INT_CLASS_NAME;
        info.parent = COS_OBJECT_CLASS;
        info.class.size = sizeof(struct COS_INT_CLASS_S);
        info.class.ctor = cos_int_class_ctor;
        info.class.dtor = cos_int_class_dtor;
        info.inst.size = sizeof(struct COS_INT_S);
        info.inst.ctor = cos_int_ctor;
        info.inst.dtor = cos_int_dtor;
        info.inst.params = cos_params_alloc(1);
        cos_params_store(info.inst.params,
                cos_param_alloc("value", COS_TYPE_INT));
        return cos_class_define(&info);
}

void cos_int_class_ctor(COS_CLASS class)
{
        cos_obj_class_ctor(class);
}

void cos_int_class_dtor(COS_CLASS class)
{
        cos_obj_class_dtor(class);
}

COS_INT cos_int_sum(size_t n, ...)
{
        int sum;
        size_t i;
        va_list args;
        sum = 0;
        va_start(args, n);
        for (i = 0; i < n; i++) sum += va_arg(args, COS_INT)->val;
        va_end(args);
        return COS_INT_CAST(cos_new(COS_INT_CLASS, sum));
}

void cos_int_ctor(COS_OBJECT this, COS_VALUES vals)
{
        cos_super(this);
        COS_INT_CAST(this)->val = cos_unbox_int(cos_values_at(vals, 0));
}

void cos_int_dtor(COS_OBJECT this)
{
        /* Nothing to do. */
}

int cos_int_val(COS_INT this)
{
        return this->val;
}

void cos_int_print(COS_INT this)
{
        printf("%d\n", this->val);
}
