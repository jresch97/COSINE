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

#define COS_CLASS_CAST(class) ((COS_CLASS)class)

struct COS_CLASS_INFO_S {
        const char *name;
        COS_CLASS   parent;
        struct {
                size_t         size;
                COS_CLASS_CTOR ctor;
                COS_CLASS_DTOR dtor;
        } class;
        struct {
                size_t        size;
                COS_INST_CTOR ctor;
                COS_INST_DTOR dtor;
                COS_PARAMS    params;
        } inst;
};

struct COS_CLASS_S {
        char     *name;
        COS_CLASS parent, next;
        size_t    n_inst;
        struct {
                size_t size;
                COS_CLASS_CTOR ctor;
                COS_CLASS_DTOR dtor;
        } class;
        struct {
                size_t        size;
                COS_INST_CTOR ctor;
                COS_INST_DTOR dtor;
                COS_PARAMS    params;
        } inst;
};

int       cos_class_init();
void      cos_class_term();
COS_CLASS cos_class(const char *name);
int       cos_class_lookup(const char *name, COS_CLASS *out);
COS_CLASS cos_class_define(COS_CLASS_INFO *info);

#endif
