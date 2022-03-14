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
 
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cosine/class.h"

cos_class cos_def_class(cos_class_spec *spec)
{
        cos_class cls;
        assert(spec);
        cls = malloc(spec->cls_size);
        if (!cls) return NULL;
        cls->n_refs = 0;
        cls->cls_name = malloc(strlen(spec->cls_name) + 1);
        strcpy(cls->cls_name, spec->cls_name);
        cls->cls_size = spec->cls_size;
        cls->obj_size = spec->obj_size;
        cls->n_init_params = spec->n_init_params;
        cls->parent_cls = spec->parent_cls;
        cls->cls_init_fn = spec->cls_init_fn;
        cls->cls_term_fn = spec->cls_term_fn;
        cls->obj_init_fn = spec->obj_init_fn;
        cls->obj_term_fn = spec->obj_term_fn;
        cls->init_params = spec->init_params;
        cls->cls_init_fn(cls);
        return cls;
}

cos_class cos_ref_class(cos_class cls)
{
        cls->n_refs++;
        return cls;
}

void cos_deref_class(cos_class cls)
{
        if (--cls->n_refs == 0) {
                cls->cls_term_fn(cls);
                free(cls->cls_name);
                free(cls->init_params);
                free(cls);
        }
}

void cos_super_class(cos_class cls)
{
        assert(cls);
        if (cls->parent_cls) cls->parent_cls->cls_init_fn(cls);
}
