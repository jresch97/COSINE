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

#include "value.h"

#define COS_CLASS_CAST(cls) ((cos_class)cls)
#define COS_CLASS_NAME(cls) COS_CLASS_CAST(cls)->name

struct cos_class_spec_s {
        const char *name;
        cos_class   parent;
        struct {
                size_t         size;
                cos_class_ctor ctor;
                cos_class_dtor dtor;
        } cls;
        struct {
                size_t        size;
                cos_inst_ctor ctor;
                cos_inst_dtor dtor;
                cos_params    params;
        } inst;
};

struct cos_class_s {
        char     *name;
        size_t    n_objs;
        cos_class parent, next;
        struct {
                size_t         size;
                cos_class_ctor ctor;
                cos_class_dtor dtor;
        } cls;
        struct {
                size_t        size;
                cos_inst_ctor ctor;
                cos_inst_dtor dtor;
                cos_params    params;
                cos_values    vals;
        } inst;
};

void      cos_class_init();
void      cos_class_term();
int       cos_class_lookup(const char *name, cos_class *out);
cos_class cos_class_define(cos_class_spec *spec);

#endif
