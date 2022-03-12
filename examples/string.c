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

static cos_class g_cos_string_class = NULL;

cos_class cos_string_class_get()
{
        cos_class cls;
        cos_class_spec spec;
        if (g_cos_string_class) return g_cos_string_class;
        if (cos_class_lookup(COS_STRING_NAME, &cls)) return cls;
        spec.name        = COS_STRING_NAME;
        spec.parent      = COS_OBJECT;
        spec.cls.size    = sizeof(struct cos_string_class_s);
        spec.cls.ctor    = cos_string_class_construct;
        spec.cls.dtor    = cos_string_class_destruct;
        spec.inst.size   = sizeof(struct cos_string_s);
        spec.inst.ctor   = cos_string_construct;
        spec.inst.dtor   = cos_string_destruct;
        spec.inst.params = cos_params_list(1, "string", COS_TYPE_STRING);
        return cos_class_define(&spec);
}

void cos_string_class_construct(cos_class cls)
{
        if (!g_cos_string_class) g_cos_string_class = cls;
        cos_super_class_construct(COS_OBJECT, cls);
}

void cos_string_class_destruct(cos_class cls)
{
        cos_super_class_destruct(COS_OBJECT, cls);
        if (g_cos_string_class == cls) g_cos_string_class = NULL;
}

void cos_string_construct(cos_object obj, cos_values vals)
{
        cos_super_construct(COS_OBJECT, obj);
        COS_STRING_C_STR(obj) = cos_unbox_string(cos_values_at(vals, 0));
        COS_STRING_LEN(obj) = strlen(COS_STRING_C_STR(obj));
}

void cos_string_destruct(cos_object obj)
{
        cos_super_destruct(COS_OBJECT, obj);
}