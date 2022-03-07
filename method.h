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

typedef void      (*COS_CONSTRUCTOR_CODE)(COS_OBJECT, COS_VALUES);
typedef void      (*COS_DESTRUCTOR_CODE)(COS_OBJECT);
typedef COS_VALUE (*COS_METHOD_CODE)(COS_OBJECT, COS_VALUES);

typedef struct COS_METHOD_S *COS_METHOD;

const char *cos_name_of_method(COS_METHOD method);
const char *cos_signature_of_method(COS_METHOD method);

#endif
