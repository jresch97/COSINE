#ifndef COS_PARAM_H
#define COS_PARAM_H

#include "type.h"

struct COS_PARAM_S {
        char *name;
        int   type;
};

COS_PARAM   cos_param_alloc(const char *name, int type);
void        cos_param_free(COS_PARAM param);
const char *cos_param_name(COS_PARAM param);
int         cos_param_type(COS_PARAM param);

COS_PARAMS cos_params_alloc(size_t len);
size_t     cos_params_len(COS_PARAMS params);
size_t     cos_params_len(COS_PARAMS params);
COS_PARAM  cos_params_at(COS_PARAMS params, size_t i);
void       cos_params_append(COS_PARAMS params, COS_PARAM param);

#endif
