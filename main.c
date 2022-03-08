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
#include <stdio.h>
#include <stdlib.h>

#include "cosine.h"

const char *cos_type_str(int type)
{
        switch (type) {
                case COS_TYPE_VOID: return "void";
                case COS_TYPE_INT:  return "int";
                default: assert(0 && "Unknown type.");
        }
}

static void cos_method_print(COS_METHOD method)
{
        size_t      i;
        const char *name;
        COS_PARAMS  params;
        COS_PARAM   param;
        if (!method) return;
        name   = cos_method_name(method);
        params = cos_method_params(method);
        switch (cos_method_vis(method)) {
                case COS_VIS_PUBL: printf("+"); break;
                case COS_VIS_PRIV: printf("-"); break;
                case COS_VIS_PROT: printf("~"); break;
                default: assert("Unknown visibility type.");
        }
        if (cos_method_type(method) == COS_METHOD_NORM) {
                printf(" %s", cos_type_str(cos_method_type(method)));
        }
        printf(" %s(", cos_method_name(method));
        if (params) {
                for (i = 0; i < cos_params_len(params); i++) {
                        param = cos_params_get(params, i);
                        printf("%s %s", cos_type_str(cos_param_type(param)),
                                                     cos_param_name(param));
                        if (i < cos_params_len(params) - 1) printf(", ");
                }
        }
        printf(") -> %p\n", NULL);
}

static void cos_class_print(COS_CLASS class)
{
        size_t i;
        COS_METHODS methods = cos_class_methods(class);
        printf("%s", cos_class_name(class));
        if (cos_class_parent(class)) {
                printf(" : %s", cos_class_name(cos_class_parent(class)));
        }
        if (cos_methods_len(methods) > 0) {
                printf(" {\n\t");
                cos_method_print(cos_class_ctor(class));
                printf("\t");
                cos_method_print(cos_class_dtor(class));
                for (i = 0; i < cos_methods_len(methods); i++) {
                        printf("\t");
                        cos_method_print(cos_methods_get(methods, i));
                }
                printf("}\n");
        } else  printf("\n");
}

int main(void)
{
        size_t i;
        COS_CLASS object_class, hello_class, test_class;
        assert(cos_init());
        object_class = cos_class_define("Object", COS_DEF_EMPTY);
        assert(object_class);
        cos_class_print(object_class);
        hello_class = cos_class_define("Hello",
                COS_DEF_CLASS, object_class);
        assert(hello_class);
        cos_class_print(hello_class);
        test_class = cos_class_define("Test",
                COS_BEG_CLASS,
                        COS_DEF_PARENT, object_class,
                        COS_BEG_CTOR,
                                COS_DEF_VIS, COS_VIS_PUBL,
                                COS_DEF_CODE, NULL,
                                COS_DEF_PARAM, COS_TYPE_INT, "a",
                                COS_DEF_PARAM, COS_TYPE_INT, "b",
                                COS_DEF_PARAM, COS_TYPE_INT, "c",
                        COS_END_CTOR,
                        COS_BEG_DTOR,
                                COS_DEF_VIS, COS_VIS_PUBL,
                                COS_DEF_CODE, NULL,
                        COS_END_DTOR,
                        COS_BEG_METHOD,
                                COS_DEF_VIS, COS_VIS_PUBL,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "sum",
                                COS_DEF_CODE, NULL,
                        COS_END_METHOD,
                        COS_BEG_METHOD,
                                COS_DEF_VIS, COS_VIS_PRIV,
                                COS_DEF_TYPE, COS_TYPE_VOID,
                                COS_DEF_NAME, "print",
                                COS_DEF_CODE, NULL,
                        COS_END_METHOD,
                        /*
                        COS_BEG_FIELD,
                                COS_DEF_VIS, COS_VIS_PRIV,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "a",
                        COS_END_FIELD,
                        COS_BEG_FIELD,
                                COS_DEF_VIS, COS_VIS_PRIV,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "b",
                        COS_END_FIELD,
                        COS_BEG_FIELD,
                                COS_DEF_VIS, COS_VIS_PRIV,
                                COS_DEF_TYPE, COS_TYPE_INT,
                                COS_DEF_NAME, "c",
                        COS_END_FIELD,
                        */
                COS_END_CLASS);
        assert(test_class);
        cos_class_print(test_class);
        cos_term();
	return EXIT_SUCCESS;
}
