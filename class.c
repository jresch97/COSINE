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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.h"
#include "param.h"
#include "value.h"

#define COS_NAME2CLASS_N 257

static cos_class cos_name2class[COS_NAME2CLASS_N];

static size_t cos_class_name_hash(const char *s)
{
        int c;
        size_t h = 5381;
        while ((c = *s++)) h = ((h << 5) + h) + c;
        return h;
}

static cos_class cos_class_alloc(cos_class_spec *spec)
{
        size_t n_params;
        cos_class cls = malloc(spec->cls.size);
        if (!cls) return NULL;
        assert(spec->name);
        cls->name = malloc(strlen(spec->name) + 1);
        if (!cls->name) {
                free(cls);
                return NULL;
        }
        strcpy(cls->name, spec->name);
        cls->parent = spec->parent;
        cls->next = NULL;
        cls->n_objs = 0;
        cls->cls.size = spec->cls.size;
        assert(spec->cls.ctor);
        cls->cls.ctor = spec->cls.ctor;
        assert(spec->cls.dtor);
        cls->cls.dtor = spec->cls.dtor;
        cls->inst.size = spec->inst.size;
        assert(spec->inst.ctor);
        cls->inst.ctor = spec->inst.ctor;
        assert(spec->inst.dtor);
        cls->inst.dtor = spec->inst.dtor;
        assert(spec->inst.params);
        cls->inst.params = spec->inst.params;
        n_params = cos_params_len(cls->inst.params);
        cls->inst.vals = cos_values_alloc(n_params);
        if (!cls->inst.vals) {
                free(cls->inst.params);
                free(cls->name);
                free(cls);
                return NULL;
        }
        cls->cls.ctor(cls);
        return cls;
}

static void cos_class_free(cos_class cls)
{
        if (cls) {
                cos_values_free(cls->inst.vals);
                cos_params_free(cls->inst.params);
                free(cls->name);
        }
        free(cls);
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
        cos_class curr, tmp;
        for (i = 0; i < COS_NAME2CLASS_N; i++) {
                curr = cos_name2class[i];
                while (curr) {
                        tmp = curr, curr = curr->next;
                        cos_class_free(tmp);
                }
        }
}

int cos_class_lookup(const char *name, cos_class *out)
{
        size_t hash;
        cos_class curr;
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

cos_class cos_class_define(cos_class_spec *spec)
{
        size_t hash;
        cos_class class, curr, prev;
        class = cos_class_alloc(spec);
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
