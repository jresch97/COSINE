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

#ifndef COS_TYPE_H
#define COS_TYPE_H

enum COS_TYPES {
        COS_TYPE_VOID,
        COS_TYPE_CLASS,
        COS_TYPE_OBJECT,
        COS_TYPE_CHAR,
        COS_TYPE_SHORT,
        COS_TYPE_INT,
        COS_TYPE_LONG,
        COS_TYPE_BYTE,
        COS_TYPE_USHORT,
        COS_TYPE_UINT,
        COS_TYPE_ULONG,
        COS_TYPE_SIZE_T
};

const char *cos_type_str(int type);

typedef void (*COS_CLASS_CTOR)(COS_CLASS);
typedef void (*COS_CLASS_DTOR)(COS_CLASS);
typedef void (*COS_INST_CTOR) (COS_OBJECT, COS_VALUES);
typedef void (*COS_INST_DTOR) (COS_OBJECT);

typedef struct COS_CLASS_S        *COS_CLASS;
typedef struct COS_CLASS_INFO_S    COS_CLASS_INFO;
typedef struct COS_OBJECT_CLASS_S *COS_OBJECT_CLASS;
typedef struct COS_OBJECT_S       *COS_OBJECT;
typedef struct COS_PARAM_S        *COS_PARAM;
typedef struct COS_PARAMS_S       *COS_PARAMS;
typedef struct COS_VALUE_S         COS_VALUE;
typedef struct COS_VALUES_S       *COS_VALUES;

#endif
