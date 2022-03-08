/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of COSINE.
 * 
 * COSINE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Founentsion, either version 3 of the
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

#include "htx.h"

struct COS_CLASS_S {
        char *name;
        COS_CLASS parent;
        COS_METHOD ctor, dtor;
        COS_METHODS methods;
};

struct COS_PARAM_S {
        char *name;
        int type;
};

struct COS_METHOD_S {
        char *name;
        int type, vis;
        COS_PARAMS params;
};

static COS_CLASS cos_empty_class_alloc(const char *name, COS_CLASS parent)
{
        COS_CLASS class = malloc(sizeof(*class));
        if (!class) return NULL;
        class->name = malloc(strlen(name) + 1);
        if (!class->name) {
                free(class);
                return NULL;
        }
        strcpy(class->name, name);
        class->parent = parent;
        class->ctor = class->dtor = NULL;
        class->methods = cos_methods_alloc(0);
        return class;
}

static COS_CLASS cos_empty_base_class_alloc(const char *name)
{
        return cos_empty_class_alloc(name, NULL);
}

static COS_PARAM cos_param_alloc(const char *name, int type)
{
        COS_PARAM param = malloc(sizeof(*param));
        if (!param) return NULL;
        param->name = malloc(strlen(name) + 1);
        if (!param->name) {
                free(param);
                return NULL;
        }
        strcpy(param->name, name);
        param->type = type;
        return param;
}

static COS_METHOD cos_ctor_alloc(COS_CLASS class, int vis, COS_PARAMS params)
{
        COS_METHOD ctor = malloc(sizeof(*ctor));
        if (!ctor) return NULL;
        ctor->name = malloc(strlen(class->name) + 1);
        if (!ctor->name) {
                free(ctor);
                return NULL;
        }
        strcpy(ctor->name, class->name);
        ctor->type = COS_TYPE_VOID;
        ctor->vis = vis;
        ctor->params = params;
        return ctor;
}

static COS_METHOD cos_parse_ctor(COS_CLASS class, va_list args)
{
        const char *name;
        int vis, type;
        COS_PARAMS params;
        params = cos_params_alloc(0);
        while (1) {
                switch (va_arg(args, int)) {
                        case COS_DEF_VIS:
                                vis = va_arg(args, int);
                                break;
                        case COS_DEF_CODE:
                                va_arg(args, void *);
                                break;
                        case COS_DEF_PARAM:
                                type = va_arg(args, int);
                                name = va_arg(args, const char *);
                                cos_params_append(params, cos_param_alloc(name, type));
                                break;
                        case COS_END_CTOR:
                                cos_params_shrink(params);
                                return cos_ctor_alloc(class, vis, params);
                        default:
                                assert(0 && "Invalid constructor definition.");
                }
        }
        return NULL;
}

static COS_CLASS cos_parse(const char *name, va_list args)
{
        COS_CLASS class;
        assert(name);
        while (1) {
                switch (va_arg(args, int)) {
                        case COS_DEF_EMPTY:
                                return cos_empty_base_class_alloc(name);
                        case COS_DEF_CLASS:
                                return cos_empty_class_alloc(name,
                                       cos_class(va_arg(args, const char *)));
                        case COS_BEG_CLASS:
                                class = cos_empty_base_class_alloc(name);
                                break;
                        case COS_DEF_PARENT:
                                class->parent = va_arg(args, COS_CLASS);
                                break;
                        case COS_BEG_CTOR:
                                class->ctor = cos_parse_ctor(class, args);
                                break;
                        case COS_END_CLASS:
                                return class;
                        default:
                                return class;
                                assert(0 && "Invalid class definition.");
                }
        }
        return NULL;
}

int cos_init()
{
        return 1;
}

void cos_term()
{

}

COS_CLASS cos_class(const char *name)
{
        assert(name);
        return NULL;
}

COS_CLASS cos_def_class(const char *name, ...)
{
        COS_CLASS class;
        va_list args;
        assert(name);
        va_start(args, name);
        class = cos_parse(name, args);
        va_end(args);
        return class;
}

const char *cos_name_of_class(COS_CLASS class)
{
        assert(class);
        return class->name;
}

COS_CLASS cos_parent_of_class(COS_CLASS class)
{
        assert(class);
        return class->parent;
}

COS_METHOD cos_ctor_of_class(COS_CLASS class)
{
        assert(class);
        return class->ctor;
}

COS_METHOD cos_dtor_of_class(COS_CLASS class)
{
        assert(class);
        return class->dtor;
}

COS_METHODS cos_methods_of_class(COS_CLASS class)
{
        assert(class);
        return class->methods;
}

const char *cos_name_of_method(COS_METHOD method)
{
        assert(method);
        return method->name;
}

int cos_type_of_method(COS_METHOD method)
{
        assert(method);
        return method->type;
}

COS_PARAMS cos_params_of_method(COS_METHOD method)
{
        assert(method);
        return method->params;
}

const char *cos_name_of_param(COS_PARAM param)
{
        assert(param);
        return param->name;
}

int cos_type_of_param(COS_PARAM param)
{
        assert(param);
        return param->type;
}