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

#include "../cosine.h"
#include "../examples/int.h"
#include "../examples/string.h"

#define INTS_N 10

int main(void)
{
        size_t     i;
        cos_int    a, b, c, sum, ints[INTS_N];
        cos_string hello, world;

        if (!cos_init()) return EXIT_FAILURE;

        a = cos_new(COS_INT, 1);
        b = cos_new(COS_INT, 2);
        c = cos_new(COS_INT, 3);

        assert(a && b && c);

        sum = cos_int_sum(3, a, b, c);
        
        assert(sum);
        
        printf("a = %d\n",         COS_INT_VAL(a));
        printf("b = %d\n",         COS_INT_VAL(b));
        printf("c = %d\n",         COS_INT_VAL(c));
        printf("a + b + c = %d\n", COS_INT_VAL(sum));

        cos_deref_many(4, a, b, c, sum);

        hello = cos_new(COS_STRING, "hello");
        world = cos_new(COS_STRING, "world");
        
        printf("\"%s\" \"%s\"\n",    COS_STRING_C_STR(hello),
                                     COS_STRING_C_STR(world));
        printf("\"%s\".len = %lu\n", COS_STRING_C_STR(hello),
                                     COS_STRING_LEN(hello));
        printf("\"%s\".len = %lu\n", COS_STRING_C_STR(world),
                                     COS_STRING_LEN(world));

        cos_deref_many(2, hello, world);

        for (i = 0; i < INTS_N; i++) ints[i] = cos_new(COS_INT, i);
        for (i = 0; i < INTS_N; i++) {
                printf("ints[%lu]=%d\n", i, COS_INT_VAL(ints[i]));
        }
        for (i = 0; i < INTS_N; i++) cos_deref(ints[i]);

        cos_term();

        return EXIT_SUCCESS;
}
