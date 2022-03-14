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

#include <stdarg.h>
#include <stddef.h>

#define cos_arg(args, arg) (va_arg(args, arg))

typedef va_list cos_args;

typedef struct cos_class_s        *cos_class;
typedef struct cos_object_class_s *cos_object_class;
typedef struct cos_object_s       *cos_object;
typedef struct cos_string_class_s *cos_string_class;
typedef struct cos_string_s       *cos_string;

typedef void (*cos_class_init_fn)(cos_class);
typedef void (*cos_class_term_fn)(cos_class);
typedef void (*cos_object_init_fn)(cos_object, cos_args args);
typedef void (*cos_object_term_fn)(cos_object);

#endif
