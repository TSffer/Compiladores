#include <stdio.h>
#include <stdlib.h>
#include "interp.h"

static int LOOK_UP_VALID = 1;

Table_ Table(string id, int value,struct table *tail)
{
    Table_ t = checked_malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}

Table_ interpStm(A_stm s,Table_ t)
{
    assert(s != NULL);

    if(s->kind == A_compoundStm)
    {
        t = interpStm(s->u.compound.stm1,t);
        t = interpStm(s->u.compound.stm2,t);
        return t;
    }
    else if (s->ki) {
        /* code */
    }
    
}