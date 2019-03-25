#include <stdio.h>
#include "slp.h"
#include "util.h"
#include "interp.h"
//#include "maxargs.h"
#include "prog1.h"

/*
int exp_helper(A_expList list)
{
    if(list->kind == A_LastExpList)
    {
        return 1;
    }
    return 1 + exp_helper(list->u.pair.tail);
}

int maxargs(A_stm prog)
{
    switch (prog->kind)
    {
        case A_compoundStm:
        {
            int left = maxargs(prog->u.compound.stm1);
            int right = maxargs(prog->u.compound.stm2);
            return (left > right) ? left : right;
        }
        case A_assignStm:
        {
            A_exp exp = prog->u.assign.exp;
            if(exp->kind == A_eseqExp)
            {
                return maxargs(exp->u.eseq.stm);
            }
            else
            {
                return 0;
            }
            
        }
        case A_printStm:
        {
            A_expList list = prog->u.print.exps;
            return exp_helper(list);
        }
        default:
            return 0;
    }
}
*/

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

int maxargs(A_stm a_stm)
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

int main()
{
    //printf(">>Right Prog Section:\n");
    printf("maxargs: %d\n",maxargs(prog()));
    printf("interpret:\n");
    interp(prog());

    return 0;
}