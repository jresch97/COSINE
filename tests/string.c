#include <stdio.h>
#include <stdlib.h>
#include <cosine.h>

int main(void)
{
        cos_string s1, s2;
        s1 = cos_new_string("Hello");
        s2 = cos_new_string("World");
        printf("%s\n", s1->c_str);
        printf("%s\n", s2->c_str);
        cos_deref_many(2, s1, s2);
        return EXIT_SUCCESS;
}
