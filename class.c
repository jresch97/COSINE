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

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "class.h"
#include "hashtabx.h"

#define COS_NAME_TO_CLASS_INIT_CAP  257
#define COS_NAME_TO_CLASS_LOAD_FACT 0.5
#define COS_NAME_TO_CLASS_GROW_FACT 1.5

struct COS_CLASS_S {
        char *name;
        COS_CLASS parent;
};

static int cos_class_name_hash(const char *s)
{
        int c, hash = 5381;
        
        while ((c = *s++)) {
                hash = ((hash << 5) + hash) + c;
        }
        
        return hash;
}

static int cos_class_name_cmp(const char *s1, const char *s2)
{
        return strcmp(s1, s2) == 0;
}

HASHTABX(COS_NAME_TO_CLASS_S,
         COS_NAME_TO_CLASS_ENTRY_S,
         cos_name_to_class_,
         const char *,
         COS_CLASS,
         cos_class_name_hash,
         cos_class_name_cmp)

typedef struct COS_NAME_TO_CLASS_S *COS_NAME_TO_CLASS;

static COS_NAME_TO_CLASS cos_name_to_class = NULL;

static int cos_class_init()
{
        static int init = 0;
        
        if (init) {
                return 1;
        }
        
        cos_name_to_class = cos_name_to_class_alloc(
                COS_NAME_TO_CLASS_INIT_CAP,
                COS_NAME_TO_CLASS_LOAD_FACT,
                COS_NAME_TO_CLASS_GROW_FACT);
                
        if (!cos_name_to_class) {
                return 0;
        }
        
        init = 1;
        return 1;
}

static COS_CLASS cos_class_alloc(const char *name, COS_CLASS parent)
{
        COS_CLASS class = malloc(sizeof(*class));
        
        assert(name);
        
        if (!class) {
                return NULL;
        }
        
        class->name = malloc(strlen(name) + 1);
        strcpy(class->name, name);
        
        class->parent = parent;
        
        return class;
}

COS_CLASS cos_def_class(const char *name, ...)
{
        COS_CLASS class, parent;
        const char *parent_name;
        va_list args;
        int def;
        
        assert(name);
        
        parent = NULL;
        
        if (!cos_class_init() ||
             cos_name_to_class_lookup(cos_name_to_class, name, NULL)) {
                return NULL;
        }
        
        va_start(args, name);
        def = va_arg(args, int);
        
        if (def == COS_DEF_EMPTY) {
                goto end;
        }
        
        assert(def == COS_DEF_BEGIN && "invalid definition list");
        
        while ((def = va_arg(args, int)) != COS_DEF_END) {
                switch (def) {
                        case COS_DEF_PARENT: {
                                assert(!parent && "multiple inheritance not supported");
                                parent_name = va_arg(args, const char *);
                                assert(parent_name);
                                parent = cos_class(parent_name);
                                if (!parent) return NULL;
                                break;
                        }
                        default:
                                goto check;
                }
        }
        
check:  /*assert(def == COS_DEF_END);*/
        assert(parent != NULL);
        
end:    va_end(args);
        
        class = cos_class_alloc(name, parent);
        
        if (!class) {
                return NULL;
        }
        
        if (!cos_name_to_class_insert(cos_name_to_class, name, class)) {
                free(class);
                return NULL;
        }
        
        return class;
}

COS_CLASS cos_class(const char *name)
{
        COS_CLASS class;
        
        assert(name);
        
        if (cos_name_to_class_lookup(cos_name_to_class, name, &class)) {
                return class;
        }
        
        return NULL;
}

const char *cos_name_of_class(COS_CLASS class)
{
        assert(class);
        
        return class->name;
}

COS_CLASS cos_parent_of_class(COS_CLASS class)
{
        assert(class);
        
        return class->parent;
}
