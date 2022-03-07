/**
 *
 * Copyright (C) 2022 Jared B. Resch
 *
 * This file is part of COSINE.
 * 
 * COSINE is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Founentsion, either version 3 of the
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

/* Opaque */

typedef struct COS_CLASS_S *COS_CLASS;

/* Definition List Types */

enum COS_DEF_TYPES {
        COS_DEF_EMPTY,
        COS_DEF_BEGIN,
        COS_DEF_PARENT,
        COS_DEF_CTOR,
        COS_DEF_DTOR,
        COS_DEF_FIELD,
        COS_DEF_METHOD,
        COS_DEF_END
};

/* Visibility Types */

enum COS_VIS_TYPES {
        COS_VIS_PRIVATE,
        COS_VIS_PROTECTED,
        COS_VIS_PUBLIC
};

/* Class Interface */

COS_CLASS cos_def_class(const char *name, ...);
COS_CLASS cos_class(const char *name);
const char *cos_name_of_class(COS_CLASS class);
COS_CLASS cos_parent_of_class(COS_CLASS class);

#endif
