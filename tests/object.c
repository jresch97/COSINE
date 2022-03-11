#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../cosine.h"

int main(void)
{
        cos_object obj, obj_ref;
        cos_class  obj_cls;

        obj = cos_new(COS_OBJECT);
        assert(obj);

        printf("&obj = %p\n", (void *)obj);
        printf("obj->n_refs = %lu\n", COS_OBJECT_N_REFS(obj));

        obj_cls = COS_OBJECT_CLASS(obj);
        printf("obj->cls->name=\"%s\"\n", COS_CLASS_NAME(obj_cls));

        obj_ref = cos_ref(obj);
        printf("obj_ref->n_refs = %lu\n", COS_OBJECT_N_REFS(obj_ref));

        return EXIT_SUCCESS;
}