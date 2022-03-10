#include <assert.h>
#include <stdio.h>

#include "int.h"

COS_CLASS cos_int_class_get()
{
        COS_CLASS class;
        COS_CLASS_INFO info;
        if (cos_class_lookup(COS_INT_CLASS_NAME, &class)) return class;
        info.name = COS_INT_CLASS_NAME;
        info.parent = COS_OBJECT_CLASS;
        info.class.size = sizeof(COS_INT_CLASS_S);
        info.class.ctor = cos_int_class_ctor;
        info.class.dtor = cos_int_class_dtor;
        info.inst.size = sizeof(COS_INT_S);
        info.inst.ctor = cos_int_ctor;
        info.inst.dtor = cos_int_dtor;
        info.inst.params = cos_params_alloc(1);
        cos_params_append(info.inst.params,
                cos_param_alloc("value", COS_TYPE_INT));
        return cos_class_define(&info);
}

void cos_int_class_ctor(COS_CLASS class)
{
        cos_obj_class_ctor(COS_OBJECT_CAST(class));
}

void cos_int_class_dtor(COS_CLASS class)
{
        cos_obj_class_dtor(COS_OBJECT_CAST(class));
}

void cos_int_sum(COS_INT a, ...)
{
        
}

void cos_int_ctor(COS_OBJECT this, COS_VALUES vals)
{
        cos_obj_ctor(obj);
        COS_INT_CAST(obj)->val = cos_unbox_int(cos_values_at(vals, 0));
}

void cos_int_dtor(COS_OBJECT this)
{
        /* Nothing to do. */
}

int cos_int_val(COS_INT this)
{
        return this->val;
}

void cos_int_print(COS_INT this)
{
        printf("%d\n", sint->val);
}
