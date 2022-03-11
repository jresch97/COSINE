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
        COS_TYPE_VOID = 0,
        COS_TYPE_CLASS,
        COS_TYPE_OBJECT,
        COS_TYPE_STRING,
        COS_TYPE_CHAR,
        COS_TYPE_SHORT,
        COS_TYPE_INT,
        COS_TYPE_LONG,
        COS_TYPE_BYTE,
        COS_TYPE_USHORT,
        COS_TYPE_UINT,
        COS_TYPE_ULONG,
        COS_TYPE_SIZE_T,
        COS_TYPE_END
};

const char *cos_type_name(int type);

typedef struct cos_class_s        *cos_class;
typedef struct cos_class_spec_s    cos_class_spec;
typedef struct cos_object_class_s *cos_object_class;
typedef struct cos_object_s       *cos_object;
typedef struct cos_param_s        *cos_param;
typedef struct cos_params_s       *cos_params;
typedef struct cos_value_s         cos_value;
typedef struct cos_values_s       *cos_values;

typedef void (*cos_class_ctor)(cos_class);
typedef void (*cos_class_dtor)(cos_class);
typedef void (*cos_inst_ctor)(cos_object, cos_values);
typedef void (*cos_inst_dtor)(cos_object);

#endif
