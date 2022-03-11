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

struct cos_params_s {
        size_t     i, len;
        cos_param *data;
};

cos_param cos_param_alloc(const char *name, int type)
{
        cos_param param = malloc(sizeof(*param));
        param->name = malloc(strlen(name) + 1);
        strcpy(param->name, name);
        param->type = type;
        return param;
}

void cos_param_free(cos_param param)
{
        if (param) free(param->name);
        free(param);
}

const char *cos_param_name(cos_param param)
{
        return param->name;
}

int cos_param_type(cos_param param)
{
        return param->type;
}

cos_params cos_params_list(size_t n, ...)
{
        size_t i;
        int type;
        va_list args;
        cos_params params;
        const char *name;
        params = cos_params_alloc(n);
        va_start(args, n);
        for (i = 0; i < n; i++) {
                name = va_arg(args, const char *);
                type = va_arg(args, int);
                cos_params_store(params, cos_param_alloc(name, type));
        }
        va_end(args);
        return params;
}

cos_params cos_params_alloc(size_t len)
{
        cos_params params = malloc(sizeof(*params));
        params->i = 0;
        params->len = len;
        params->data = malloc(len * sizeof(*params->data));
        return params;
}

void cos_params_free(cos_params params)
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

size_t cos_params_len(cos_params params)
{
        return params->len;
}

cos_param cos_params_at(cos_params params, size_t i)
{
        assert(i < params->len);
        return params->data[i];
}

void cos_params_store(cos_params params, cos_param param)
{
        assert(params->i < params->len);
        params->data[params->i++] = param;
}
