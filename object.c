#include <stdlib.h>

#include "object.h"

COS_CLASS cos_obj_class_get()
{
        COS_CLASS class;
        COS_CLASS_INFO info;
        if (cos_class_lookup(COS_OBJECT_CLASS_NAME, &class)) return class;
        info.name = COS_OBJECT_CLASS_NAME;
        info.parent = NULL;
        info.class.size = sizeof(COS_OBJECT_CLASS_S);
        info.class.ctor = cos_obj_class_ctor;
        info.class.dtor = cos_obj_class_dtor;
        info.inst.size = sizeof(COS_OBJECT_S);
        info.inst.ctor = cos_obj_ctor;
        info.inst.dtor = cos_obj_dtor;
        info.inst.params = cos_params_alloc(1);
        cos_params_append(info.inst.params,
                cos_param_alloc("class", COS_TYPE_CLASS));
        return cos_class_define(&info);
}

void cos_obj_class_ctor(COS_CLASS class)
{
        /* Nothing to do. */
}

void cos_obj_class_dtor(COS_CLASS class)
{
        /* Nothing to do. */
}

void cos_obj_ctor(COS_OBJECT this, COS_VALUES values)
{
        this->n_refs = 1;
        this->class  = cos_unbox_class(cos_values_at(values, 0));
}

void cos_obj_dtor(COS_OBJECT this)
{
        /* Nothing to do. */
}

int cos_obj_n_refs(COS_OBJECT this)
{
        return this->nrefs;
}

COS_CLASS cos_obj_class(COS_OBJECT this)
{
        return this->class;
}

COS_OBJECT cos_new(COS_CLASS class, ...)
{
        COS_OBJECT obj;
        COS_VALUES vals;
        
        obj = malloc(class->inst.size);
        
        /* TODO: Params -> Values */
        
        obj->class->inst.ctor(obj);
        
        return obj;
}

COS_OBJECT cos_ref(COS_OBJECT obj)
{
        obj->refs++;
}

void cos_deref(COS_OBJECT obj)
{
        obj->n_refs--;
        if (obj->n_refs == 0) {
                obj->class->inst.dtor(obj);
                free(obj);
        }
}
