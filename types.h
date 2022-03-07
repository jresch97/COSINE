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

#ifndef COS_TYPES_H
#define COS_TYPES_H

/* Primitive Types */

enum COS_TYPES {
        COS_TYPE_VOID,
        COS_TYPE_CLASS,
        COS_TYPE_POINTER,
        COS_TYPE_CHAR,
        COS_TYPE_SHORT,
        COS_TYPE_INT,
        COS_TYPE_LONG,
        COS_TYPE_UNSIGNED_CHAR,
        COS_TYPE_UNSIGNED_SHORT,
        COS_TYPE_UNSIGNED_INT,
        COS_TYPE_UNSIGNED_LONG,
        COS_TYPE_FLOAT,
        COS_TYPE_DOUBLE,
        COS_TYPE_SIZE
};

#endif
