#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define BUFF_T(TYPE) TYPE##_BUFF
#define COMPUTE_T(TYPE_IN,TYPE_OUT) TYPE_IN##_##TYPE_OUT##_COMPUTE
#define NODE_T(TYPE_IN,TYPE_OUT) TYPE_IN##_##TYPE_OUT##_NODE

#define DECLARE_BUFF_T(TYPE)    \
typedef struct BUFF_T(TYPE)     \
{                               \
    uintmax_t  len;             \
    TYPE*     data;             \
} BUFF_T(TYPE);

#define DECLARE_COMPUTE_T(TYPE_IN,TYPE_OUT) \
typedef void(*COMPUTE_T(TYPE_IN,TYPE_OUT))(BUFF_T(TYPE_IN)*,BUFF_T(TYPE_OUT)*);

#define DECLARE_NODE_T(TYPE_IN,TYPE_OUT)    \
typedef struct NODE_T(TYPE_IN,TYPE_OUT)     \
{                                           \
    BUFF_T(TYPE_IN)  *in;                   \
    BUFF_T(TYPE_OUT) *out;                  \
                                            \
    COMPUTE_T(TYPE_IN,TYPE_OUT) func;       \
} NODE_T(TYPE_IN,TYPE_OUT);

#define DECLARE_BUFF_TYPES(TYPE)  \
DECLARE_BUFF_T(TYPE)

#define DECLARE_NODE_TYPES(TYPE_IN,TYPE_OUT) \
DECLARE_COMPUTE_T(TYPE_IN,TYPE_OUT)          \
DECLARE_NODE_T(TYPE_IN,TYPE_IN)

DECLARE_BUFF_TYPES(float)
DECLARE_NODE_TYPES(float,float)

#endif
