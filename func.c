#include "func.h"

#define DEFINE_SUM_COMPUTE_FUNC(TYPE_IN,TYPE_OUT)   \
COMPUTE_FUNC(SUM,TYPE_IN,TYPE_OUT)                  \
{                                                   \
    for(uintmax_t i=0;i<out->len;i++)               \
    {                                               \
        out->data[i] = 0;                           \
        for(uintmax_t j=0;j<in->len;j++)            \
        {                                           \
          out->data[i]+=in->data[j];                \
        }                                           \
    }                                               \
}

#define DEFINE_AVG_COMPUTE_FUNC(TYPE_IN,TYPE_OUT)   \
COMPUTE_FUNC(AVG,TYPE_IN,TYPE_OUT)                  \
{                                                   \
    for(uintmax_t i=0;i<out->len;i++)               \
    {                                               \
        out->data[i] = 0;                           \
        for(uintmax_t j=0;j<in->len;j++)            \
        {                                           \
          out->data[i]+=in->data[j];                \
        }                                           \
        out->data[i] /= in->len;                    \
    }                                               \
}

#define DEFINE_COMPUTE_FUNC(TYPE_IN,TYPE_OUT) \
DEFINE_SUM_COMPUTE_FUNC(TYPE_IN,TYPE_OUT)     \
DEFINE_AVG_COMPUTE_FUNC(TYPE_IN,TYPE_OUT)

DEFINE_COMPUTE_FUNC(float,float)
