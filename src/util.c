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
    for (int i = 0; i < 9; ++i)
        var->tabdomainVar[i] = i + 1;
}

int is_in_sum(Constraints_Sum **sums, Constraints_Sum *s, int number_of_empty_case) {
    int i = 0;
    while(sums[i]) {
        if (sums[i] == s) return 42;
        ++i;
    }
    return 0;
}

int is_in_diff(Constraints_Diff **diffs, Constraints_Diff *s, int number_of_empty_case) {
    int i = 0;
    while(diffs[i]) {
        if (diffs[i] == s) return 42;
        ++i;
    }
    return 0;
}

void freedom (Variable **vars, int number_of_empty_case) {
    int i_diffs = 0;
    Constraints_Diff **diffs = calloc (number_of_empty_case, sizeof (Constraints_Diff));
    int i_sums = 0;
    Constraints_Sum **sums = calloc (number_of_empty_case, sizeof (Constraints_Sum));

    for (int i = 0; i < number_of_empty_case; ++i) {
        Variable *v = vars[i];
        if (v->sum_H && (! is_in_sum(sums, v->sum_H, number_of_empty_case)) ) {
            sums[i_sums] = v->sum_H;
            ++i_sums;
        }
        if (v->sum_V && (! is_in_sum(sums, v->sum_V, number_of_empty_case)) ) {
            sums[i_sums] = v->sum_V;
            ++i_sums;
        }
        if (v->diff && (! is_in_diff(diffs, v->diff, number_of_empty_case)) ) {
            diffs[i_diffs] = v->diff;
            ++i_diffs;
        }
    }

    int i = 0;
    while(sums[i]) {
        free(sums[i]->vars);
        free(sums[i]);
        ++i;
    }

    i = 0;
    while(diffs[i]) {
        free(diffs[i]->vars);
        free(diffs[i]);
        ++i;
    }

    i = 0;
    while(vars[i]) {
        free(vars[i]);
        ++i;
    }

    free(diffs);
    free(sums);
    free(vars);
}
