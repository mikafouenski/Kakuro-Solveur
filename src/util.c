#include "util.h"

int tabdomain[sizeDomain] = {1,2,3,4,5,6,7,8,9};
int number_of_empty_case = 0;
int size_length = 0;
int size_width = 0;

int testContraintSomme(Constraints_Sum * contraint){
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

int testContraintDiff(Constraints_Diff *  contraint, int val){
    int i = 0;
    while(contraint->vars[i]){
        if (contraint->vars[i]->value == val) return 0;
        ++i;
    }
    return 42;
}

void echec(){
    for (int i=0; i < number_of_empty_case; ++i) {
        Variable *var2 = variablesInst[i];
        printf("Case n°%d : %d", var2->indice,var2->value); 
        printf("\n");
    }
    printf("ECHEC !\n");
    freedom();
    exit(1);
}

void freedom () {
    int i;
    for (i = 0; i < number_of_empty_case; ++i)
        if(variablesInst[i])
            free(variablesInst[i]);
    free(variables);
    free(variablesInst);
}
