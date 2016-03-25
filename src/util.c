#include <stdlib.h>
#include "util.h"

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
