#include "fowardchecking_solver.h"

void eraseContraintSum(Variable *v, Constraints_Sum *cs ) {
    int sum = 0;
    int i = 0;
    int is_declared = 0;
    int max;
    while(cs->vars[i]) {
        if(cs->vars[i]->value != -1) {
            sum += cs->vars[i]->value;
            
        }
        else
            ++is_declared;
        ++i;
    }
    if(is_declared == 1) {
        max = cs->value - sum;
        for (i = 0; i < sizeDomain; ++i)
            if(i != max-1)
                v->tabdomainVar[i] = -1;
    }
    else {
     max =  cs->value - sum ;
     if(max <= 9){
        for (i = 0;i < sizeDomain; ++i)
            if(i > max-1)
                v->tabdomainVar[i] = -1;
        }
    }
}

void eraseDomain(Variable *v) {
    if(v->sum_H)
        eraseContraintSum(v,v->sum_H);
    if(v->sum_V)
        eraseContraintSum(v,v->sum_V);
    if(v->diff) {
        Constraints_Diff * dc = v->diff;
        int i;
        for (i = 0; dc->vars[i]; ++i)
            if(dc->vars[i]->value != -1)
                v->tabdomainVar[dc->vars[i]->value-1] = -1;
    }
}

void displayDomain(Variable *v){
    printf("variable n°%d : ",v->indice);
    for(int i = 0 ; i < sizeDomain; ++i){
        printf(" %d ", v->tabdomainVar[i]);
    }
    printf("\n");
}

void fowardchecking(Variable **v, int number_of_empty_case){
    int i = 0;
    Variable *current = v[i];
    while(i < number_of_empty_case){ 

        eraseDomain(current);
        //displayDomain(current);
        do {
            while(current->indice_domaine < sizeDomain && 
                current->tabdomainVar[current->indice_domaine] == -1){
                ++current->indice_domaine;
            }
           
            while(current->indice_domaine > sizeDomain){
                current->indice_domaine = 0;
                if(i == 0) echec();
                initDomain(current);
                current->value = -1;
                --i;
                current = v[i];
                while(current->tabdomainVar[current->indice_domaine] == -1){
                    if(current->indice_domaine > sizeDomain)
                        break;
                    ++current->indice_domaine;
                }
            }

            current->value = current->tabdomainVar[current->indice_domaine];
            ++current->indice_domaine;
        } while(!(testContraintDiff(current->diff,current->value) && 
            testContraintSomme(current->sum_H) &&
            testContraintSomme(current->sum_V)));
       // printf("current Var %d %d\n",current->indice,current ->value );
        ++i;
        current = v[i];
    }
}
