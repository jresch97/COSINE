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

#include "cosine.h"

#define INTS_N 10

int main(void)
{
        size_t i;
        COS_INT a, b, c, sum, *ints;
        COS_STRING hello, world;
        ints = malloc(INTS_N * sizeof(*ints));
        if (!cos_init()) return EXIT_FAILURE;
        a = cos_new(COS_INT_CLASS, 1);
        b = cos_new(COS_INT_CLASS, 2);
        c = cos_new(COS_INT_CLASS, 3);
        sum = cos_int_sum(3, a, b, c);
        assert(a && b && c && sum);
        printf("a = %d\n", cos_int_val(a));
        printf("b = %d\n", cos_int_val(b));
        printf("c = %d\n", cos_int_val(c));
        printf("a + b + c = %d\n", cos_int_val(sum));
        cos_int_print(a);
        cos_int_print(b);
        cos_int_print(c);
        cos_int_print(sum);
        cos_deref_many(4, a, b, c, sum);
        hello = cos_new(COS_STRING_CLASS, "hello");
        world = cos_new(COS_STRING_CLASS, "world");
        cos_str_print(hello);
        cos_str_print(world);
        printf("\"hello\".len = %lu\n", cos_str_len(hello));
        printf("\"world\".len = %lu\n", cos_str_len(world));
        cos_deref_many(2, hello, world);
        for (i = 0; i < INTS_N; i++) {
                ints[i] = cos_new(COS_INT_CLASS, i);
        }
        for (i = 0; i < INTS_N; i++) {
                cos_int_print(ints[i]);
        }
        for (i = 0; i < INTS_N; i++) {
                cos_deref(ints[i]);
        }
        free(ints);
        cos_term();
        return EXIT_SUCCESS;
}
