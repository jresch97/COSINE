#include <stdio.h>
#include <stdlib.h>
#include <cosine.h>

int main(void)
{
        cos_string s1, s2, s3, s4, sp;
        s1 = cos_new_string("Hello");
        s2 = cos_new_string("World");
        sp = cos_new_string(" ");
        printf("%s\n", s1->c_str);
        printf("%s\n", s2->c_str);
        s3 = cos_string_join(s1, s2);
        printf("%s\n", s3->c_str);
        s4 = cos_string_join_many(3, s1, sp, s2);
        printf("%s\n", s4->c_str);
        cos_deref_many(5, s1, s2, s3, s4, sp);
        return EXIT_SUCCESS;
}
