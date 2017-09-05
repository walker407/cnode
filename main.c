#include "node.h"
#include <stdio.h>

DECLARE_NODE(float,float)

int main()
{
    NODE_T(float,float) *node1 = CREATE_NODE(float,float)(10,1,COMPUTE_FUNC_T(AVG,float,float));

    for(uintmax_t i=0;i<node1->in->len;i++)
    {
      node1->in->data[i] = i;
    }

    for(uintmax_t i=0;i<node1->in->len;i++)
    {
      printf("in value: %f\n",node1->in->data[i]);
    }

    COMPUTE_NODE(float,float)(node1);

    for(uintmax_t i=0;i<node1->out->len;i++)
    {
      printf("out value: %f\n",node1->out->data[i]);
    }
    printf("\n");

    NODE_T(float,float) *node2 = CREATE_NODE(float,float)(100,1,COMPUTE_FUNC_T(SUM,float,float));

    for(uintmax_t i=0;i<node2->in->len;i++)
    {
      node2->in->data[i] = i;
    }

    for(uintmax_t i=0;i<node2->in->len;i++)
    {
      printf("in value: %f\n",node2->in->data[i]);
    }

    COMPUTE_NODE(float,float)(node2);

    for(uintmax_t i=0;i<node2->out->len;i++)
    {
      printf("out value: %f\n",node2->out->data[i]);
    }

    FREE_NODE(float,float)(node1);

    return 0;
}
