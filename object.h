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

#define COS_OBJECT_NAME            "Object"
#define COS_OBJECT                 (cos_object_class_get())
#define COS_OBJECT_CAST(obj)       ((cos_object)obj)
#define COS_OBJECT_CLASS_CAST(cls) ((cos_object_class)cls)

typedef size_t (*cos_object_hash_fn)(cos_object);
typedef int    (*cos_object_equals_fn)(cos_object, cos_object);

struct cos_object_class_s {
        struct cos_class_s   cls;
        cos_object_hash_fn   hash;
        cos_object_equals_fn equals;
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
size_t    cos_object_hash(cos_object obj);
int       cos_object_equals(cos_object obj, cos_object other);

/* TODO: Move to cosine? */

cos_class cos_class_of(void *obj);
void     *cos_new(cos_class cls, ...);
void     *cos_ref(void *obj);
void      cos_deref(void *obj);
void      cos_deref_many(size_t n, ...);
void      cos_super_class_construct(cos_class parent, void *cls);
void      cos_super_class_destruct(cos_class parent, void *cls);
void      cos_super_construct(cos_class cls, void *obj, ...);
void      cos_super_destruct(cos_class cls, void *obj);

#endif
