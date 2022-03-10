#ifndef COS_OBJECT_H
#define COS_OBJECT_H

#include "type.h"

#define COS_OBJECT_CLASS      (cos_obj_class_get())
#define COS_OBJECT_CLASS_NAME "Object"

struct COS_OBJECT_CLASS_S {
        struct COS_CLASS_S class;
};

COS_CLASS cos_obj_class_get();
void      cos_obj_class_ctor(COS_CLASS class);
void      cos_obj_class_dtor(COS_CLASS class);

#define COS_OBJECT_CAST(obj) ((COS_OBJECT)obj)

struct COS_OBJECT_S {
        size_t    n_refs;
        COS_CLASS class;
};

void      cos_obj_ctor(COS_OBJECT this, COS_VALUES values);
void      cos_obj_dtor(COS_OBJECT this);
int       cos_obj_n_refs(COS_OBJECT this);
COS_CLASS cos_obj_class(COS_OBJECT this);

COS_OBJECT cos_new(COS_CLASS class, ...);
COS_OBJECT cos_ref(COS_OBJECT obj);
void       cos_deref(COS_OBJECT obj);
void       cos_deref_many(COS_OBJECT obj, ...);

#endif
