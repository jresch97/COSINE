#include <stdio.h>
#include <stdlib.h>
#include <cosine.h>

int main(void)
{
        cos_object o1, o2, o3;
        cos_string s1, s2, s3;
        o1 = cos_new_object();
        o2 = cos_new(COS_OBJECT);
        o3 = cos_ref(o1);
        printf("%lu\n", cos_object_hash(o1));
        printf("%lu\n", cos_object_hash(o2));
        printf("%lu\n", cos_object_hash(o3));
        printf("%i\n",  cos_object_equals(o1, o3));
        printf("%i\n",  cos_object_equals(o1, o2));
        s1 = cos_object_to_string(o1);
        s2 = cos_object_to_string(o1);
        s3 = cos_object_to_string(o1);
        printf("%s\n", s1->c_str);
        printf("%s\n", s2->c_str);
        printf("%s\n", s3->c_str);
        printf("%lu\n", cos_object_hash((cos_object)s1));
        printf("%lu\n", cos_object_hash((cos_object)s2));
        cos_deref_many(3, o1, o2, o3);
        cos_deref_many(3, s1, s2, s3);
        return EXIT_SUCCESS;
}
