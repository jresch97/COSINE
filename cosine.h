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

#ifndef COS_COSINE_H
#define COS_COSINE_H

#include "dax.h"

enum COS_TYPES {
        COS_TYPE_VOID,
        COS_TYPE_OBJECT,
        COS_TYPE_CHAR,
        COS_TYPE_SHORT,
        COS_TYPE_INT,
        COS_TYPE_LONG,
        COS_TYPE_UNSIGNED_CHAR,
        COS_TYPE_UNSIGNED_SHORT,
        COS_TYPE_UNSIGNED_INT,
        COS_TYPE_UNSIGNED_LONG,
        COS_TYPE_FLOAT,
        COS_TYPE_DOUBLE,
        COS_TYPE_SIZE_T
};

enum COS_VIS_TYPES {
        COS_VIS_PRIVATE,
        COS_VIS_PROTECTED,
        COS_VIS_PUBLIC
};

enum COS_DEF_TYPES {
        COS_DEF_EMPTY,
        COS_DEF_CLASS,
        COS_BEG_CLASS,
        COS_END_CLASS,
        COS_DEF_PARENT,
        COS_BEG_CTOR,
        COS_END_CTOR,
        COS_BEG_DTOR,
        COS_END_DTOR,
        COS_BEG_FIELD,
        COS_END_FIELD,
        COS_BEG_METHOD,
        COS_END_METHOD,
        COS_DEF_PARAM,
        COS_DEF_VIS,
        COS_DEF_CODE,
        COS_DEF_TYPE,
        COS_DEF_NAME
};

typedef struct COS_CLASS_S   *COS_CLASS;
typedef struct COS_METHOD_S  *COS_METHOD;
typedef struct COS_METHODS_S *COS_METHODS;
typedef struct COS_PARAM_S   *COS_PARAM;
typedef struct COS_PARAMS_S  *COS_PARAMS;

DAX(COS_PARAMS_S, cos_params_, COS_PARAM, 2)
DAX(COS_METHODS_S, cos_methods_, COS_METHOD, 2)

int cos_init();
void cos_term();
COS_CLASS cos_class(const char *name);
COS_CLASS cos_def_class(const char *name, ...);
const char *cos_name_of_class(COS_CLASS class);
COS_CLASS cos_parent_of_class(COS_CLASS class);
COS_METHOD cos_ctor_of_class(COS_CLASS class);
COS_METHOD cos_dtor_of_class(COS_CLASS class);
COS_METHODS cos_methods_of_class(COS_CLASS class);
COS_METHOD cos_method_of_class(const char *name, COS_CLASS class);
const char *cos_name_of_method(COS_METHOD method);
int cos_type_of_method(COS_METHOD method);
COS_PARAMS cos_params_of_method(COS_METHOD method);
const char *cos_name_of_param(COS_PARAM param);
int cos_type_of_param(COS_PARAM param);

#endif
