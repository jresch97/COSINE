#ifndef COS_CLASS_H
#define COS_CLASS_H

#include "type.h"

#define COS_CLASS_CAST(class) ((COS_CLASS)class)

struct COS_CLASS_INFO_S COS_CLASS_INFO; {
        const char *name;
        COS_CLASS   parent;
        struct {
                size_t         size;
                COS_CLASS_CTOR ctor;
                COS_CLASS_DTOR dtor;
        } class;
        struct {
                size_t        size;
                COS_INST_CTOR ctor;
                COS_INST_DTOR dtor;
                COS_PARAMS    params;
        } inst;
} COS_CLASS_INFO;

struct COS_CLASS_S {
        char     *name;
        COS_CLASS parent;
        size_t    n_inst;
        struct {
                size_t size;
                COS_CLASS_CTOR ctor;
                COS_CLASS_DTOR dtor;
        } class;
        struct {
                size_t        size;
                COS_INST_CTOR ctor;
                COS_INST_DTOR dtor;
                COS_PARAMS    params;
        } inst;
};

COS_CLASS cos_class_define(COS_CLASS_INFO *info);

#endif
