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
#include "class.h"

#define COS_OBJECT_NAME        "Object"
#define COS_OBJECT             (cos_object_class_get())
#define COS_OBJECT_CAST(obj)   ((cos_object)obj)
#define COS_OBJECT_N_REFS(obj) COS_OBJECT_CAST(obj)->n_refs
#define COS_OBJECT_CLASS(obj)  COS_OBJECT_CAST(obj)->cls

struct cos_object_class_s {
        struct cos_class_s cls;
};

struct cos_object_s {
        cos_class cls;
        size_t    n_refs;
};

cos_class cos_object_class_get();
void      cos_object_class_construct(cos_class cls);
void      cos_object_class_destruct(cos_class cls);
void      cos_object_construct(cos_object obj, cos_values vals);
void      cos_object_destruct(cos_object obj);

/* TODO: Move to cosine? */

void *cos_new(cos_class cls, ...);
void *cos_ref(void *obj);
void  cos_deref(void *obj);
void  cos_deref_many(size_t n, ...);
void  cos_super_class_construct(cos_class cls);
void  cos_super_class_destruct(cos_class cls);
void  cos_super_construct(cos_class cls, void *obj, ...);
void  cos_super_destruct(cos_class cls, void *obj);

#endif
