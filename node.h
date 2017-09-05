#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "func.h"

#include <stdlib.h>
#include <stdint.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BUFF_T(TYPE) TYPE##_BUFF
#define COMPUTE_T(TYPE_IN,TYPE_OUT) TYPE_IN##_##TYPE_OUT##_COMPUTE
#define NODE_T(TYPE_IN,TYPE_OUT) TYPE_IN##_##TYPE_OUT##_NODE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define COMPUTE_NODE(TYPE_IN,TYPE_OUT) COMPUTE_##TYPE_IN##_##TYPE_OUT##_NODE
#define CREATE_NODE(TYPE_IN,TYPE_OUT) CREATE_##TYPE_IN##_##TYPE_OUT##_NODE
#define FREE_NODE(TYPE_IN,TYPE_OUT) FREE_##TYPE_IN##_##TYPE_OUT##_NODE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_BUFF_T(TYPE)    \
typedef struct BUFF_T(TYPE)     \
{                               \
    uintmax_t len;              \
    TYPE*     data;             \
} BUFF_T(TYPE);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_COMPUTE_T(TYPE_IN,TYPE_OUT) \
typedef void(*COMPUTE_T(TYPE_IN,TYPE_OUT))(BUFF_T(TYPE_IN)*,BUFF_T(TYPE_OUT)*);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_NODE_T(TYPE_IN,TYPE_OUT)    \
typedef struct NODE_T(TYPE_IN,TYPE_OUT)     \
{                                           \
    BUFF_T(TYPE_IN)  *in;                   \
    BUFF_T(TYPE_OUT) *out;                  \
                                            \
    COMPUTE_T(TYPE_IN,TYPE_OUT) func;       \
} NODE_T(TYPE_IN,TYPE_OUT);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define COMPUTE_FUNC(NAME,TYPE_IN,TYPE_OUT) \
void COMPUTE_FUNC_T(NAME,TYPE_IN,TYPE_OUT)(BUFF_T(TYPE_IN) *in,BUFF_T(TYPE_OUT) *out)

#define DECLARE_COMPUTE_FUNC(NAME,TYPE_IN,TYPE_OUT) \
COMPUTE_FUNC(NAME,TYPE_IN,TYPE_OUT);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT) \
void COMPUTE_NODE(TYPE_IN,TYPE_OUT)(NODE_T(TYPE_IN,TYPE_OUT) *node)

#define DECLARE_COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT) \
COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT);

#define DEFINE_COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT)  \
COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT)                 \
{                                                   \
    node->func(node->in,node->out);                 \
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT)  \
NODE_T(TYPE_IN,TYPE_OUT)* CREATE_NODE(TYPE_IN,TYPE_OUT)(const uintmax_t num_in, const uintmax_t num_out, COMPUTE_T(TYPE_IN,TYPE_OUT) func)

#define DECLARE_CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT) \
CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT);

#define DEFINE_CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT)                                                                                   \
CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT)                                                                                                  \
{                                                                                                                                   \
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FREE_NODE_FUNC(TYPE_IN,TYPE_OUT)    \
void FREE_NODE(TYPE_IN,TYPE_OUT)(NODE_T(TYPE_IN,TYPE_OUT) *node)

#define DECLARE_FREE_NODE_FUNC(TYPE_IN,TYPE_OUT)    \
FREE_NODE_FUNC(TYPE_IN,TYPE_OUT);

#define DEFINE_FREE_NODE_FUNC(TYPE_IN,TYPE_OUT) \
FREE_NODE_FUNC(TYPE_IN,TYPE_OUT)                \
{                                               \
    if(node->in)                                \
    {                                           \
        if(node->in->data)                       \
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DECLARE_NODE(TYPE_IN,TYPE_OUT)         \
DECLARE_BUFF_T(TYPE_IN)                        \
DECLARE_COMPUTE_T(TYPE_IN,TYPE_OUT)            \
DECLARE_NODE_T(TYPE_IN,TYPE_OUT)               \
DEFINE_COMPUTE_NODE_FUNC(TYPE_IN,TYPE_OUT)     \
DEFINE_CREATE_NODE_FUNC(TYPE_IN,TYPE_OUT)      \
DEFINE_FREE_NODE_FUNC(TYPE_IN,TYPE_OUT)        \
                                               \
DEFINE_SUM_COMPUTE_FUNC(TYPE_IN,TYPE_OUT)      \
DEFINE_AVG_COMPUTE_FUNC(TYPE_IN,TYPE_OUT)
