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

void echec(Variable **variablesInst, int number_of_empty_case){
    for (int i=0; i < number_of_empty_case; ++i) {
        Variable *var2 = variablesInst[i];
        printf("Case n°%d : %d", var2->indice,var2->value); 
        printf("\n");
    }
    printf("ECHEC !\n");
    freedom(variablesInst, number_of_empty_case);
    exit(1);
}

void initDomain(Variable * var){
    for (int i = 0; i < sizeDomain; ++i)
        var->tabdomainVar[i] = i + 1;
}

void freedom (Variable **vars, int number_of_empty_case) {
    for (int i = 0; i < number_of_empty_case; ++i) {
        Variable *v = vars[i];
        free(v);
    }

    // for (int i = 0; i < number_of_empty_case; ++i) {
    //     Variable *v = vars[i];
    //     if (v->sum_H) {
            
    //     }
    // }
    free(vars);
}
