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

#include "cosine.h"

/*
void test_ctor(COS_OBJECT this, COS_VALUES values)
{
        cos_set_field("a", this, cos_value_at(values, 0));
        cos_set_field("b", this, cos_value_at(values, 1));
        cos_set_field("c", this, cos_value_at(values, 2));
}

void test_dtor(COS_OBJECT this)
{

}

void test_print(COS_OBJECT this)
{
        int a, b, c;
        a = unbox_int(cos_field("a", this));
        b = unbox_int(cos_field("b", this));
        c = unbox_int(cos_field("c", this));
        printf("%d %d %d\n", a, b, c);
}

COS_VALUE test_sum(COS_OBJECT this, COS_VALUE values)
{
        return cos_box_int(0);
}
*/

const char *cos_type_to_c_type_str(int type)
{
        switch (type) {
                case COS_TYPE_VOID: return "void";
                case COS_TYPE_INT:  return "int";
                default: assert(0 && "Unknown type.");
        }
}

static void cos_debug_print_method(COS_METHOD method)
{
        size_t i;
        COS_PARAM param;
        COS_PARAMS params;
        if (!method) return;
        params = cos_params_of_method(method);
        printf("+ %s %s(", cos_type_to_c_type_str(cos_type_of_method(method)),
                           cos_name_of_method(method));
        for (i = 0; i < cos_params_len(params); i++) {
                param = cos_params_get(params, i);
                printf("%s %s", cos_type_to_c_type_str(cos_type_of_param(param)),
                                cos_name_of_param(param));
                if (i < cos_params_len(params) - 1) printf(", ");
        }
        printf(") -> \n");
}

static void cos_debug_print_class(COS_CLASS class)
{
        cos_debug_print_method(cos_ctor_of_class(class));
        cos_debug_print_method(cos_dtor_of_class(class));
}

int main(void)
{
        size_t i;
        COS_CLASS object_class, hello_class, test_class;
        
        assert(cos_init());
        
        object_class = cos_def_class("Object", COS_DEF_EMPTY);
        assert(object_class);
        
        hello_class = cos_def_class("Hello", COS_DEF_CLASS, object_class);
        assert(hello_class);
        
        test_class = cos_def_class("Test",
                COS_BEG_CLASS,
                        COS_DEF_PARENT, object_class,
                        COS_BEG_CTOR,
                                COS_DEF_VIS, COS_VIS_PUBLIC,
                                COS_DEF_CODE, NULL,
                                COS_DEF_PARAM, COS_TYPE_INT, "a",
                                COS_DEF_PARAM, COS_TYPE_INT, "b",
                                COS_DEF_PARAM, COS_TYPE_INT, "c",
                        COS_END_CTOR,
                        COS_BEG_DTOR,
                                COS_DEF_VIS, COS_VIS_PUBLIC,
                                COS_DEF_CODE, NULL,
                        COS_END_DTOR,
                        COS_BEG_FIELD,
                                COS_DEF_VIS, COS_VIS_PRIVATE,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "a",
                        COS_END_FIELD,
                        COS_BEG_FIELD,
                                COS_DEF_VIS, COS_VIS_PRIVATE,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "b",
                        COS_END_FIELD,
                        COS_BEG_FIELD,
                                COS_DEF_VIS, COS_VIS_PRIVATE,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "c",
                        COS_END_FIELD,
                        COS_BEG_METHOD,
                                COS_DEF_VIS, COS_VIS_PUBLIC,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "sum",
                                COS_DEF_CODE, NULL,
                        COS_END_METHOD,
                        COS_BEG_METHOD,
                                COS_DEF_VIS, COS_VIS_PUBLIC,
                                COS_DEF_TYPE, COS_TYPE_VOID,
                                COS_DEF_NAME, "print",
                                COS_DEF_CODE, NULL,
                        COS_END_METHOD,
                COS_END_CLASS);
        assert(test_class);
        
        cos_debug_print_class(test_class);
        
        cos_term();
        
	return EXIT_SUCCESS;
}
