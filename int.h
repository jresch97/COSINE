#ifndef COS_INT_H
#define COS_INT_H

#include "object.h"

typedef struct COS_INT_CLASS_S *COS_INT_CLASS;
typedef struct COS_INT_S       *COS_INT;

#define COS_INT_CLASS      (cos_int_class_get())
#define COS_INT_CLASS_NAME "Integer"

struct COS_INT_CLASS_S {
        struct COS_CLASS_S class;
};

COS_CLASS cos_int_class_get();
void      cos_int_class_ctor(COS_CLASS class);
void      cos_int_class_dtor(COS_CLASS class);
void      cos_int_sum(COS_INT a, ...);

#define COS_INT_CAST(obj) ((COS_INT)obj)

struct COS_INT_S {
        struct COS_OBJECT_S obj;
        int                 val;
};

void cos_int_ctor(COS_OBJECT this, COS_VALUES values);
void cos_int_dtor(COS_OBJECT this);
int  cos_int_val(COS_INT this);
void cos_int_print(COS_INT this);

#endif
