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

#include "class.h"
#include "param.h"
#include "value.h"

#define COS_NAME2CLASS_N 257

static COS_CLASS cos_name2class[COS_NAME2CLASS_N];

static size_t cos_class_name_hash(const char *s)
{
        int c;
        size_t h = 5381;
        while ((c = *s++)) h = ((h << 5) + h) + c;
        return h;
}

static COS_CLASS cos_class_alloc(COS_CLASS_INFO *info)
{
        size_t n_params;
        COS_CLASS class = malloc(info->class.size);
        if (!class) return NULL;
        assert(info->name);
        class->name = malloc(strlen(info->name) + 1);
        if (!class->name) {
                free(class);
                return NULL;
        }
        strcpy(class->name, info->name);
        class->parent = info->parent;
        class->next = NULL;
        class->n_inst = 0;
        class->class.size = info->class.size;
        assert(info->class.ctor);
        class->class.ctor = info->class.ctor;
        assert(info->class.dtor);
        class->class.dtor = info->class.dtor;
        class->inst.size = info->inst.size;
        assert(info->inst.ctor);
        class->inst.ctor = info->inst.ctor;
        assert(info->inst.dtor);
        class->inst.dtor = info->inst.dtor;
        assert(info->inst.params);
        class->inst.params = info->inst.params;
        n_params = cos_params_len(class->inst.params);
        class->inst.vals = cos_values_alloc(n_params);
        if (!class->inst.vals) {
                free(class->inst.params);
                free(class->name);
                free(class);
                return NULL;
        }
        return class;
}

static void cos_class_free(COS_CLASS class)
{
        if (class) {
                cos_values_free(class->inst.vals);
                cos_params_free(class->inst.params);
                free(class->name);
        }
        free(class);
}

void cos_class_init()
{
        size_t i;
        for (i = 0; i < COS_NAME2CLASS_N; i++) {
                cos_name2class[i] = NULL;
        }
}

void cos_class_term()
{
        size_t i;
        COS_CLASS curr, tmp;
        for (i = 0; i < COS_NAME2CLASS_N; i++) {
                curr = cos_name2class[i];
                while (curr) {
                        tmp = curr, curr = curr->next;
                        cos_class_free(tmp);
                }
        }
}

COS_CLASS cos_class(const char *name)
{
        COS_CLASS class;
        if (cos_class_lookup(name, &class)) return class;
        return NULL;
}

int cos_class_lookup(const char *name, COS_CLASS *out)
{
        size_t hash;
        COS_CLASS curr;
        hash = cos_class_name_hash(name);
        curr = cos_name2class[hash % COS_NAME2CLASS_N];
        while (curr) {
                if (strcmp(name, curr->name) == 0) {
                        *out = curr;
                        return 1;
                }
                curr = curr->next;
        }
        return 0;
}

COS_CLASS cos_class_define(COS_CLASS_INFO *info)
{
        size_t hash;
        COS_CLASS class, curr, prev;
        class = cos_class_alloc(info);
        if (!class) return NULL;
        hash = cos_class_name_hash(class->name);
        if (!cos_name2class[hash % COS_NAME2CLASS_N]) {
                cos_name2class[hash % COS_NAME2CLASS_N] = class;
                return class;
        }
        curr = cos_name2class[hash % COS_NAME2CLASS_N];
        while (curr) {
                if (strcmp(class->name, curr->name) == 0) return NULL;
                prev = curr, curr = curr->next;
        }
        prev->next = class;
        return class;
}
