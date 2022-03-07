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

#ifndef COS_METHOD_H
#define COS_METHOD_H

#include "value.h"
#include "param.h"

/* Signature Types */

enum COS_CODE_TYPES {
        COS_CODE_CTOR,
        COS_CODE_DTOR,
        COS_CODE_VOID,
        COS_CODE_VALUE
        COS_CODE_VOID_EMPTY,
        COS_CODE_VALUE_EMPTY,
};

/* Signatures */

typedef void      (*COS_CTOR_CODE)(COS_OBJECT, COS_VALUES);  /* Constructor */
typedef void      (*COS_DTOR_CODE)(COS_OBJECT);              /* Destructor */
typedef void      (*COS_VOID_CODE)(COS_OBJECT, COS_VALUES);  /* Void w/ Params */
typedef COS_VALUE (*COS_VALUE_CODE)(COS_OBJECT, COS_VALUES); /* Value w/ Params */
typedef void      (*COS_VOID_EMPTY_CODE)(COS_OBJECT);        /* Void w/out Params */
typedef COS_VALUE (*COS_VALUE_EMPTY_CODE)(COS_OBJECT);       /* Value w/out Params */

/* Code Variant */

typedef struct COS_CODE_S {
        int type;
        union {
                COS_CTOR_CODE  ctor;
                COS_DTOR_CODE  dtor;
                COS_VOID_CODE  void_r;
                COS_VALUE_CODE value_r;
        } data;
} COS_CODE;

/* Opaque */

typedef struct COS_METHOD_S *COS_METHOD;

/* Method Interface */

const char *cos_name_of_method(COS_METHOD method);
const char *cos_signature_of_method(COS_METHOD method);

#endif
