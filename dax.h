/**
 *
 * Copyright (C) 2021-2022 Jared B. Resch
 *
 * This file is part of STRUCTX.
 * 
 * STRUCTX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * STRUCTX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with STRUCTX. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef STRUCTX_DAX_H
#define STRUCTX_DAX_H

#include <assert.h>
#include <stdlib.h>

#ifndef DAX_EXPORT
#define DAX_EXPORT static
#endif

#define DAX(DA_S, FN, T, GROW_FACT) \
\
struct DA_S { \
        size_t len, cap; \
        T *data; \
}; \
\
DAX_EXPORT struct DA_S *FN ## alloc(size_t cap) \
{ \
        struct DA_S *da; \
        da = malloc(sizeof(*da)); \
        if (!da) return NULL; \
        da->len = 0; \
        da->cap = cap; \
        da->data = malloc(cap * sizeof(T)); \
        return da; \
} \
\
DAX_EXPORT void FN ## free(struct DA_S *da) \
{ \
        assert(da != NULL); \
        if (da) free(da->data); \
        free(da); \
} \
\
DAX_EXPORT void FN ## init(struct DA_S *da, size_t cap) \
{ \
        assert(da); \
        da->len = 0; \
        da->cap = cap; \
        da->data = malloc(cap * sizeof(T)); \
} \
\
DAX_EXPORT void FN ## term(struct DA_S *da) \
{ \
        assert(da); \
        da->len = da->cap = 0; \
        if (da->data) { \
                free(da->data); \
                da->data = NULL; \
        } \
} \
\
DAX_EXPORT int FN ## resize(struct DA_S *da, size_t cap) \
{ \
        T *data; \
        assert(da); \
        data = realloc(da->data, cap * sizeof(T)); \
        if (cap == 0 || (cap > 0 && data)) { \
                da->cap = cap; \
                da->data = data; \
                return 1; \
        } else  return 0; \
} \
\
DAX_EXPORT int FN ## grow(struct DA_S *da) \
{ \
        T *data; \
        size_t cap; \
        assert(da); \
        cap = (da->cap == 0) ? 1 : (size_t)(da->cap * GROW_FACT); \
        data = realloc(da->data, cap * sizeof(T)); \
        if (cap == 0 || (cap > 0 && data)) { \
                da->cap = cap; \
                da->data = data; \
                return 1; \
        } else  return 0; \
} \
\
DAX_EXPORT int FN ## shrink(struct DA_S *da) \
{ \
        T *data; \
        assert(da); \
        data = realloc(da->data, da->len * sizeof(T)); \
        if (da->len == 0 || (da->len > 0 && data)) { \
                da->cap = da->len; \
                da->data = data; \
                return 1; \
        } else  return 0; \
} \
\
DAX_EXPORT int FN ## append(struct DA_S *da, T val) \
{ \
        assert(da); \
        if (da->len == da->cap && !FN ## grow(da)) return 0; \
        da->data[da->len++] = val; \
        return 1; \
} \
\
DAX_EXPORT void FN ## remove(struct DA_S *da, size_t i) \
{ \
        size_t j; \
        assert(da); \
        assert(i < da->len); \
        for (j = i; j < da->len; j++) da->data[j] = da->data[j + 1]; \
        da->len--; \
} \
\
DAX_EXPORT T FN ## get(struct DA_S *da, size_t i) \
{ \
        assert(da);  \
        assert(i < da->len); \
        return da->data[i];   \
} \
\
DAX_EXPORT size_t FN ## len(struct DA_S *da) \
{ \
        assert(da); \
        return da->len; \
} \
\
DAX_EXPORT size_t FN ## cap(struct DA_S *da) \
{ \
        assert(da); \
        return da->cap; \
} \
\
DAX_EXPORT T *FN ## data(struct DA_S *da) \
{ \
        assert(da); \
        return da->data; \
}

#endif
