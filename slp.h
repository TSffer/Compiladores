typedef struct A_stm_ *A_stm;
typedef struct A_exp_ *A_exp;
typedef struct  A_expList_ *A_expList;
typedef enum {A_plus,A_minus,A_times,A_div} A_binop;

struct A_stm_{enum{A_compoundStm,A_assignStm,A_printStm} kind;
            union {struct{A_stm stm1,stm2;} compound;
                
            };
            
}   