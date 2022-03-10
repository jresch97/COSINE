#include <assert.h>

#include "value.h"

COS_VALUE cos_box_void()
{
        COS_VALUE val;
        val.type      = COS_TYPE_VOID;
        val.data.size = 0;
        return val;
}

void cos_unbox_void(COS_VALUE val)
{
        assert(val.type == COS_TYPE_VOID);
}

COS_VALUE cos_box_class(COS_CLASS class)
{
        COS_VALUE val;
        val.type       = COS_TYPE_CLASS;
        val.data.class = class;
        return val;
}

COS_CLASS cos_unbox_class(COS_VALUE val)
{
        assert(val.type == COS_TYPE_CLASS);
        return val.class;
}

COS_VALUE cos_box_object(COS_OBJECT obj)
{
        COS_VALUE val;
        val.type     = COS_TYPE_OBJECT;
        val.data.obj = obj;
        return val;
}

COS_CLASS cos_unbox_object(COS_VALUE val)
{
        assert(val.type == COS_TYPE_OBJECT);
        return val.obj;
}

COS_VALUE cos_box_char(char s_char)
{
        COS_VALUE val;
        val.type        = COS_TYPE_CHAR;
        val.data.s_char = s_char;
        return val;
}

int cos_unbox_char(COS_VALUE val)
{
        assert(val.type == COS_TYPE_CHAR);
        return val.s_char;
}

COS_VALUE cos_box_short(short s_short)
{
        COS_VALUE val;
        val.type       = COS_TYPE_SHORT;
        val.data.s_short = s_short;
        return val;
}

int cos_unbox_short(COS_VALUE val)
{
        assert(val.type == COS_TYPE_SHORT);
        return val.s_short;
}

COS_VALUE cos_box_int(int s_int)
{
        COS_VALUE val;
        val.type       = COS_TYPE_INT;
        val.data.s_int = s_int;
        return val;
}

int cos_unbox_int(COS_VALUE val)
{
        assert(val.type == COS_TYPE_INT);
        return val.s_int;
}
