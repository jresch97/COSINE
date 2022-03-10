#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "int.h"

int main(void)
{
        COS_INT a, b, c, sum;
        if (!cos_init()) return EXIT_FAILURE;
        a = cos_new(COS_INT_CLASS, 1);
        b = cos_new(COS_INT_CLASS, 2);
        c = cos_new(COS_INT_CLASS, 3);
        sum = cos_int_sum(a, b, c);
        assert(a && b && c && sum);
        printf("a = %d\n", cos_int_val(a));
        printf("b = %d\n", cos_int_val(b));
        printf("c = %d\n", cos_int_val(c));
        printf("a + b + c = %d\n", cos_int_val(sum));
        cos_deref_many(a, b, c);
        cos_deref(sum);
        cos_term();
        return EXIT_SUCCESS;
}
