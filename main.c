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

#include "cos.h"

void test_constructor(COS_OBJECT this, COS_VALUE values)
{

}

void test_destructor(COS_OBJECT this)
{

}

void test_print(COS_OBJECT this)
{

}

COS_VALUE test_sum(COS_OBJECT this)
{
        return cos_box_int(0);
}

int main(void)
{
        COS_CLASS object_class, test_class;
        /*COS_OBJECT object, test;*/
        assert(cos_init());
        object_class = cos_def_class("Object", COS_DEF_EMPTY);
        assert(object_class);
        printf("defined class %s\n", cos_name_of_class(object_class));
        test_class = cos_def_class("Test",
                COS_DEF_BEGIN,
                COS_DEF_PARENT, "Object",
                COS_DEF_CTOR, COS_PUBLIC, test_constructor, 3,
                        "a", COS_TYPE_INT,
                        "b", COS_TYPE_INT,
                        "c", COS_TYPE_INT,
                COS_DEF_DTOR, COS_PUBLIC, test_destructor,
                COS_DEF_FIELD, COS_PUBLIC, "a", COS_TYPE_INT, 0,
                COS_DEF_FIELD, COS_PUBLIC, "b", COS_TYPE_INT, 0,
                COS_DEF_FIELD, COS_PUBLIC, "c", COS_TYPE_INT, 0,
                COS_DEF_METHOD, COS_PUBLIC, "sum", COS_TYPE_INT, test_sum, 0,
                COS_DEF_METHOD, COS_PUBLIC, "print", COS_TYPE_VOID, test_print, 0,
                COS_DEF_END);
        assert(test_class);
        printf("defined class %s\n", cos_name_of_class(test_class));
        /*
        object = cos_new(object_class);
        test = cos_new(test_class);
        printf("sum=%d\n", unbox_int(cos_call_by_name("sum", test));
        cos_call_by_name("print", test);
        */
        cos_term();
	return EXIT_SUCCESS;
}
