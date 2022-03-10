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
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "param.h"

COS_PARAM cos_param_alloc(const char *name, int type)
{
        COS_PARAM param = malloc(sizeof(*param));
        param->name = malloc(strlen(name) + 1);
        strcpy(param->name, name);
        param->type = type;
        return param;
}

void cos_param_free(COS_PARAM param)
{
        if (param) free(param->name);
        free(param);
}

const char *cos_param_name(COS_PARAM param)
{
        return param->name;
}

int cos_param_type(COS_PARAM param)
{
        return param->type;
}

struct COS_PARAMS_S {
        size_t     i, len;
        COS_PARAM *data;
};

COS_PARAMS cos_params(size_t len, ...)
{
        size_t i;
        va_list args;
        COS_PARAMS params;
        const char *name;
        int type;
        params = cos_params_alloc(len);
        va_start(args, len);
        for (i = 0; i < len; i++) {
                name = va_arg(args, const char *);
                type = va_arg(args, int);
                cos_params_store(params, cos_param_alloc(name, type));
        }
        va_end(args);
        return params;
}

COS_PARAMS cos_params_alloc(size_t len)
{
        COS_PARAMS params = malloc(sizeof(*params));
        params->i = 0;
        params->len = len;
        params->data = malloc(len * sizeof(*params->data));
        return params;
}

void cos_params_free(COS_PARAMS params)
{
        size_t i;
        if (params) {
                for (i = 0; i < params->len; i++) {
                        cos_param_free(params->data[i]);
                }
                free(params->data);
        }
        free(params);
}

size_t cos_params_len(COS_PARAMS params)
{
        return params->len;
}

COS_PARAM cos_params_at(COS_PARAMS params, size_t i)
{
        assert(i < params->len);
        return params->data[i];
}

void cos_params_store(COS_PARAMS params, COS_PARAM param)
{
        assert(params->i < params->len);
        params->data[params->i++] = param;
}
