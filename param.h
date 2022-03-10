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

COS_PARAMS cos_params(size_t len, ...);
COS_PARAMS cos_params_alloc(size_t len);
void       cos_params_free(COS_PARAMS params);
size_t     cos_params_len(COS_PARAMS params);
size_t     cos_params_len(COS_PARAMS params);
COS_PARAM  cos_params_at(COS_PARAMS params, size_t i);
void       cos_params_store(COS_PARAMS params, COS_PARAM param);
void       cos_params_reset(COS_PARAMS params);

#endif
