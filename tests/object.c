#include <stdio.h>
#include <stdlib.h>
#include <cosine.h>

int main(void)
{
        cos_object o1, o2, o3;

        o1 = cos_new_object();
        o2 = cos_new(COS_OBJECT);
        o3 = cos_ref(o1);
        
        printf("%lu\n", cos_object_hash(o1));
        printf("%lu\n", cos_object_hash(o2));
        printf("%lu\n", cos_object_hash(o3));
        printf("%i\n",  cos_object_equals(o1, o3));
        printf("%i\n",  cos_object_equals(o1, o2));
        
        cos_deref_many(3, o1, o2, o3);
        
        return EXIT_SUCCESS;
}
