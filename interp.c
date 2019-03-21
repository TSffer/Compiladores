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
    else if(s->kind == A_assignStm) 
    {
        struct IntAndTable it = interExp(s->u.assign.exp,t);
        return Table(s->u.assign.id, it.i,it.t);
    }
    else if(s->kind == A_printStm)
    {
        struct IntAndTable it;
        A_expList list = s->u.print.exps;
        if(list->kind == A_lastExpList)
        {
            it = interExp(list->u.last,t);
            printf("%d\n",it.i);
            return it.t;
        }
        else
        {
            while(list->kind != A_lastExpList)
            {
                it = interExp(list->u.pair.head,t);
                printf("%d ",it.i);
                t = it.t;
                list = list->u.pair.tail;
            }
            it = interExp(list->u.last,t);
            printf("%d\n",it.i);
            return it.t;
        }
    }
    else
    {
        assert(!"ag");
    }
}

struct IntAndTable interExp(A_exp e, Table_ t)
{
    if(e->kind == A_idExp)
    {
        int value = lookup(t,e->u.id);
        assert(LOOK_UP_VALID);

        struct IntAndTable it;
        it.t = t;
        it.i = value;
        return it;
    }
    else if(e->kind == A_numExp)
    {
        struct IntAndTable it;
        it.t = t;
        it.i = e->u.num;
        return it;         
    }
    else if(e->kind == A_opExp)
    {
        struct IntAndTable it;
        struct IntAndTable left = interExp(e->u.op.left,t);
        struct IntAndTable right = interExp(e->u.op.right,left.t);
        switch (e->u.op.oper)
        {
            case A_plus : it.i = left.i + right.i; break;
            case A_minus: it.i = left.i - right.i; break;
            case A_times: it.i = left.i * right.i; break;
            case A_div  : it.i = left.i / right.i; break;
            default:
                assert(!"agg");
        }
        it.t = right.t;
        return it;
    }
    else if(e->kind == A_eseqExp)
    {
        struct IntAndTable it;
        t = interpStm(e->u.eseq.stm,t);
        it = interExp(e->u.eseq.exp,t);
        return it;
    }
    else
    {
        assert(!"aggg");
    }   
};

int lookup(Table_ t, string key)
{
    if(t == NULL || key == NULL)
        return LOOK_UP_VALID = 0;
    
    Table_ next = t;

    while(next != NULL)
    {
        if(next->id == key)
        {
            LOOK_UP_VALID = 1;
            return next->value;
        }
        next = t->tail;
    }
    return LOOK_UP_VALID = 0;   
}

void interp(A_stm stm)
{
    interpStm(stm,NULL);
}
