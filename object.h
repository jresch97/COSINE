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

#ifndef COS_OBJECT_H
#define COS_OBJECT_H

#include "type.h"

#define COS_OBJECT_CLASS      (cos_obj_class_get())
#define COS_OBJECT_CLASS_NAME "Object"

struct COS_OBJECT_CLASS_S {
        struct COS_CLASS_S class;
};

COS_CLASS cos_obj_class_get();
void      cos_obj_class_ctor(COS_CLASS class);
void      cos_obj_class_dtor(COS_CLASS class);

#define COS_OBJECT_CAST(obj) ((COS_OBJECT)obj)

struct COS_OBJECT_S {
        size_t    n_refs;
        COS_CLASS class;
};

void      cos_obj_ctor(COS_OBJECT this, COS_VALUES values);
void      cos_obj_dtor(COS_OBJECT this);
int       cos_obj_n_refs(COS_OBJECT this);
COS_CLASS cos_obj_class(COS_OBJECT this);

COS_OBJECT cos_new(COS_CLASS class, ...);
COS_OBJECT cos_ref(COS_OBJECT obj);
void       cos_deref(COS_OBJECT obj);
void       cos_deref_many(COS_OBJECT obj, ...);

#endif
