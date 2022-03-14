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

#include "cosine.h"

static void cos_call_obj_init(cos_object obj, va_list args)
{
        size_t i;
        cos_param *p = obj->cls->init_params;
        for (i = 0; i < obj->cls->n_init_params; i++) {
                switch (p[i].type) {
                        case COS_CLASS_TYPE:  p[i].data.cls    = va_arg(args, cos_class);
                        case COS_OBJECT_TYPE: p[i].data.obj    = va_arg(args, cos_object);
                        case COS_STRING_TYPE: p[i].data.str    = va_arg(args, const char *);
                        case COS_CHAR_TYPE:   p[i].data.schar  = va_arg(args, int);
                        case COS_SHORT_TYPE:  p[i].data.sshort = va_arg(args, int);
                        case COS_INT_TYPE:    p[i].data.sint   = va_arg(args, int);
                        case COS_LONG_TYPE:   p[i].data.slong  = va_arg(args, long);
                        case COS_BYTE_TYPE:   p[i].data.uchar  = va_arg(args, unsigned int);
                        case COS_USHORT_TYPE: p[i].data.ushort = va_arg(args, unsigned int);
                        case COS_UINT_TYPE:   p[i].data.uint   = va_arg(args, unsigned int);
                        case COS_ULONG_TYPE:  p[i].data.ulong  = va_arg(args, unsigned long);
                        case COS_SIZE_T_TYPE: p[i].data.size   = va_arg(args, size_t);
                }
        }
        obj->cls->obj_init_fn(obj, obj->cls->n_init_params, p);
}

void *cos_new(cos_class cls, ...)
{
        va_list args;
        cos_object obj = malloc(cls->obj_size);
        if (!obj) return NULL;
        obj->cls = cos_ref_class(cls);
        va_start(args, cls);
        cos_call_obj_init(obj, args); 
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
        assert(obj);
        if (--((cos_object)obj)->n_refs == 0) {
                ((cos_object)obj)->cls->obj_term_fn((cos_object)obj);
                cos_deref_class(((cos_object)obj)->cls);
                free(obj);
        }
}

void cos_deref_many(size_t n, ...)
{
        size_t i;
        va_list args;
        assert(n > 0);
        va_start(args, n);
        for (i = 0; i < n; i++) cos_deref(va_arg(args, void *));
        va_end(args);
}

void cos_super(void *obj, ...)
{
        va_list args;
        assert(obj);
        va_start(args, obj);
        cos_call_obj_init(((cos_object)obj), args); 
        va_end(args);
}

cos_class cos_class_of(void *obj)
{
        assert(obj);
        return ((cos_object)obj)->cls;
}
