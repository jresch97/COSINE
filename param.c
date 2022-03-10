#include <stdlib.h>

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

size_t cos_params_len(COS_PARAMS params)
{
        COS_PARAMS params = malloc(sizeof(*params));
        params->i = 0;
        params->len = len;
        params->data = malloc(len * sizeof(*params->data));
        return params;
}

size_t cos_params_len(COS_PARAMS params)
{
        return params->len;
}

COS_PARAM cos_params_at(COS_PARAMS params, size_t i)
{
        return params->data[i];
}

void cos_params_append(COS_PARAMS params, COS_PARAM param)
{
        params->data[params->i++] = param;
}
