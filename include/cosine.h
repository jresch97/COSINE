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

#ifndef COS_COSINE_H
#define COS_COSINE_H

#include "cosine/type.h"
#include "cosine/class.h"
#include "cosine/object.h"
#include "cosine/string.h"

void     *cos_new(cos_class cls, ...);
void     *cos_ref(void *obj);
void      cos_deref(void *obj);
void      cos_deref_many(size_t n, ...);
void      cos_super(void *obj, ...);
cos_class cos_class_of(void *obj);
cos_class cos_def_class(cos_class_spec *spec);
cos_class cos_ref_class(cos_class cls);
void      cos_deref_class(cos_class cls);

#endif
