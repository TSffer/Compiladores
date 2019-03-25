#include "maxargs.h"
#include <stdlib.h>
/*
int maxargs(A_stm stm)
{
    assert(stm != NULL);

    if(stm->kind == A_AssignStm)
    {
        if(stm->u.assign.exp->kind == A_eseqExp)
        {
            return maxargs(stm->u.assign.exp->u.eseq.stm);
        }
        else
        {
            return 0;
        }
    }
    else if(stm->kind == A_compoundStm)
    {
        int t1 = maxargs(stm->u.compound.stm1);
        int t2 = maxargs(stm->u.compound.stm2);
        return t1 > t2 ? t1 : t2;
    }
    else if(stm->kind == A_printStm)
    {
        A_expList list = stm->u.print.exps;
        if(list->kind == A_lastExpList)
        {
            int substm_num = 0;

            if(list->u.last->kind == A_eseqExp)
                substm_num = maxargs(list->u.last->u.eseq.stm);
            return substm_num > 1 ? substm_num : 1;
        }
        else
        {
            int args_num = 1;
            int substm_num = 0;
            int max_substm_num = 0;
            while(list->kind != A_lastExpList)
            {
                if(list->u.pair.head->kind == A_eseqExp)
                {
                    substm_num = maxargs(list->u.pair.head->u.eseq.stm);
                    if(substm_num > max_substm_num)
                        max_substm_num = substm_num;
                }
                list = list->u.pair.tail;
                args_num++;
            }
            return max_substm_num > args_num ? max_substm_num : args_num;
        }
    }
    else
    {
       // assert(!"Unban lobitos");
    }
    
}
////////////////////////////////////////////////////////////

int bigger(int first, int second)
{
    return first > second ? first : second;
}

int argsOfExp(A_exp exp)
{
    if(NULL == exp)
        return 0;
    switch (exp->kind)
    {
        case A_idExp:
            return 0;
        case A_numExp:
            return 0;
        case A_opExp:
            return bigger(argsOfExp(exp->u.op.left), argsOfExp(exp->u.op.right));
        case A_eseqExp:
            return bigger(maxargs(exp->u.eseq.stm),argsOfExp(exp->u.eseq.exp));
    }
    return 0;
}

int argsOfExps(A_expList exps)
{
    if(NULL == exps)
        return 0;
    switch (exps->kind)
    {
        case A_lastExpList:
            return 1;
        case A_pairExpList:
            return bigger(argsOfExp(exps->u.pair.head),1 + argsOfExps(exps->u.pair.tail));
    }
    return 0;
}

int maxargs2(A_stm a_stm)
{
    if(NULL == a_stm)
        return 0;
    switch (a_stm->kind)
    {
        case A_compoundStm:
            return bigger(maxargs(a_stm->u.compound.stm1),maxargs(a_stm->u.compound.stm2));
        case A_assignStm:
            return argsOfExp(a_stm->u.assign.exp);
        case A_printStm:
            return argsOfExps(a_stm->u.print.exps);
    }
    return 0;
}
*/