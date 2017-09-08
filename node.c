#include "node.h"
#include <stdlib.h>

#define DEFINE_COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT)  \
COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT)                 \
{                                                   \
    node->func(node->in,node->out);                 \
}

#define DEFINE_CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT)                                                                                   \
CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT)                                                                                                  \
{                                                                                                                                   \
                                                                                                                                    \
    BUFF_T(TYPE_IN)* in = (BUFF_T(TYPE_IN)*)malloc(sizeof(BUFF_T(TYPE_IN)));                                                        \
    in->len  = num_in;                                                                                                              \
    in->data = (TYPE_IN*)malloc(sizeof(TYPE_IN)*num_in);                                                                            \
                                                                                                                                    \
    BUFF_T(TYPE_OUT)* out = (BUFF_T(TYPE_OUT)*)malloc(sizeof(BUFF_T(TYPE_OUT)));                                                    \
    out->len  = num_out;                                                                                                            \
    out->data = (TYPE_OUT*)malloc(sizeof(TYPE_OUT)*num_out);                                                                        \
                                                                                                                                    \
    NODE_T(TYPE_IN,TYPE_OUT)* node = (NODE_T(TYPE_IN,TYPE_OUT)*)malloc(sizeof(NODE_T(TYPE_IN,TYPE_OUT))+sizeof(in)+sizeof(out));    \
    node->in    = in;                                                                                                               \
    node->out   = out;                                                                                                              \
    node->func  = func;                                                                                                             \
                                                                                                                                    \
    return node;                                                                                                                    \
}

#define DEFINE_FREE_NODE_FUNC(TYPE_IN,TYPE_OUT) \
FREE_NODE_FUNC(TYPE_IN,TYPE_OUT)                \
{                                               \
    if(node->in)                                \
    {                                           \
        if(node->in->data)                      \
        {                                       \
            free(node->in->data);               \
        }                                       \
        free(node->in);                         \
    }                                           \
    if(node->out)                               \
    {                                           \
        if(node->out->data)                     \
        {                                       \
            free(node->out->data);              \
        }                                       \
        free(node->out);                        \
    }                                           \
    if(node)                                    \
    {                                           \
        free(node);                             \
    }                                           \
}

#define DEFINE_NODE(TYPE_IN,TYPE_OUT)         \
DEFINE_COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT)    \
DEFINE_CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT)     \
DEFINE_FREE_NODE_FUNC(TYPE_IN,TYPE_OUT)

DEFINE_NODE(float,float)
