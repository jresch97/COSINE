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

#include "string.h"
#include "param.h"
#include "value.h"

COS_CLASS cos_str_class_get()
{
        static COS_CLASS class;
        COS_CLASS_INFO info;
        if (class) return class;
        if (cos_class_lookup(COS_STRING_CLASS_NAME, &class)) return class;
        info.name = COS_STRING_CLASS_NAME;
        info.parent = COS_OBJECT_CLASS;
        info.class.size = sizeof(struct COS_STRING_CLASS_S);
        info.class.ctor = cos_str_class_ctor;
        info.class.dtor = cos_str_class_dtor;
        info.inst.size = sizeof(struct COS_STRING_S);
        info.inst.ctor = cos_str_ctor;
        info.inst.dtor = cos_str_dtor;
        info.inst.params = cos_params_alloc(1);
        cos_params_store(info.inst.params,
                cos_param_alloc("c_str", COS_TYPE_C_STR));
        return cos_class_define(&info);
}

void cos_str_class_ctor(COS_CLASS class)
{
        cos_obj_class_ctor(class);
}

void cos_str_class_dtor(COS_CLASS class)
{
        cos_obj_class_dtor(class);
}

void cos_str_ctor(COS_OBJECT this, COS_VALUES vals)
{
        cos_super(this);
        COS_STRING_CAST(this)->c_str = cos_unbox_c_str(cos_values_at(vals, 0));
        COS_STRING_CAST(this)->len = strlen(COS_STRING_CAST(this)->c_str);
}

void cos_str_dtor(COS_OBJECT this)
{
        /* Nothing to do. */
}

const char *cos_str_c_str(COS_STRING this)
{
        return this->c_str;
}

size_t cos_str_len(COS_STRING this)
{
        return this->len;
}

void cos_str_print(COS_STRING this)
{
        printf("%s\n", this->c_str);
}
