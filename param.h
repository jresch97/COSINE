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

struct cos_param_s {
        char *name;
        int   type;
};

cos_param   cos_param_alloc(const char *name, int type);
void        cos_param_free(cos_param param);
const char *cos_param_name(cos_param param);
int         cos_param_type(cos_param param);
cos_params  cos_params_list(size_t n, ...);
cos_params  cos_params_alloc(size_t len);
void        cos_params_free(cos_params params);
size_t      cos_params_len(cos_params params);
size_t      cos_params_len(cos_params params);
cos_param   cos_params_at(cos_params params, size_t i);
void        cos_params_store(cos_params params, cos_param param);
void        cos_params_reset(cos_params params);

#endif
