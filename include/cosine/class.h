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

#ifndef COS_CLASS_H
#define COS_CLASS_H

#include "type.h"

#define cos_arg(args, arg) (va_arg(args, arg))

typedef struct cos_class_spec_s {
        const char        *cls_name;
        size_t             cls_size;
        size_t             obj_size;
        cos_class          parent_cls;
        cos_class_init_fn  cls_init_fn;
        cos_class_term_fn  cls_term_fn;
        cos_object_init_fn obj_init_fn;
        cos_object_term_fn obj_term_fn;
} cos_class_spec;

struct cos_class_s {
        size_t             n_refs;
        char              *cls_name;
        size_t             cls_size;
        size_t             obj_size;
        cos_class          base_cls;
        cos_class          parent_cls;
        cos_class_init_fn  cls_init_fn;
        cos_class_term_fn  cls_term_fn;
        cos_object_init_fn obj_init_fn;
        cos_object_term_fn obj_term_fn;
};

cos_class cos_def_class(cos_class_spec *spec);
cos_class cos_ref_class(cos_class cls);
void      cos_deref_class(cos_class cls);

#endif
