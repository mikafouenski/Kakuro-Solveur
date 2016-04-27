#include "util.h"

int testContraintSomme(Constraints_Sum * contraint, Stat *stats){
    stats->nb_test_constraints++;
    if(contraint == NULL) return 42;
    int i = 0;
    int sum = 0;
    while(contraint->vars[i]){
        if(contraint->vars[i]->value == -1) return 42;
        sum += contraint->vars[i]->value;
        if(sum > contraint->value) return 0;
        ++i;
    }
    if(sum == contraint->value) return 42;
    return 0;
}

int testContraintDiff(Constraints_Diff *  contraint, int val, Stat *stats){
    stats->nb_test_constraints++;
    int i = 0;
    while(contraint->vars[i]){
        if (contraint->vars[i]->value == val) return 0;
        ++i;
    }
    return 42;
}

void echec(Variable **variablesInst, int number_of_empty_case, int size_width){
    for (int i=0; i < number_of_empty_case; ++i) {
        Variable *var2 = variablesInst[i];
        printf("Case n°%d : %d", var2->indice,var2->value); 
        printf("\n");
    }
    printf("ECHEC !\n");
    freedom(variablesInst, number_of_empty_case, size_width);
    exit(1);
}

void initDomain(Variable * var){
    for (int i = 0; i < sizeDomain; ++i)
        var->tabdomainVar[i] = i + 1;
}

void freedom (Variable **vars, int number_of_empty_case, int size_width) {
    for (int i = 0; i < number_of_empty_case; ++i) {
        Variable *v = vars[i];
        int j = 0;
        if (v->sum_H) {
            int indice = v->indice;
            //++indice;
            int i = 0;
            while(vars[indice]) {
                v->sum_H->vars[i] = NULL;
                vars[indice]->sum_H = NULL;
                ++i;
                ++indice;
            }
            i = 0;
            while(v->sum_H->vars[i]) {
                if(v->sum_H->vars[i] != v) {
                    v->diff->vars[j] = NULL;
                    ++j;
                }
                ++i;
            }
        }
        if (v->sum_V) {
            int indice = v->indice;
            //indice += size_width;
            int i = 0;
            while(vars[indice]) {
                v->sum_V->vars[i] = NULL;
                vars[indice]->sum_V = NULL;
                ++i;
                indice += size_width;
            }
            i = 0;
            while(v->sum_V->vars[i]) {
                if(v->sum_V->vars[i] != v){
                    v->diff->vars[j] = NULL;
                    ++j;
                }
                ++i;
            }
        }
    }

    for (int i = 0; i < number_of_empty_case; ++i) {
        Variable *v = vars[i];
        if (v->sum_V) free(v->sum_V);
    }

    free(vars);
}
