#include <stdio.h>
#include "../inc/kakuro_solver.h"
#include "../inc/backtrack_solver.h"

extern int number_of_empty_case;


void echec(){
    printf("TG Micka\n");
    freedom();
    exit(1);
}

void backtrack(Variable **v){
    int i = 0;
    Variable *current = v[i];
    while(i < number_of_empty_case){
        do {
            while(current->indice_domaine > sizeDomain){
                current->indice_domaine = 0;
                if(i == 0){
                  echec();
                }
                current->value = -1;
                --i;
                current = v[i];
            }
            current->value = current->tabdomainVar[current->indice_domaine];
            ++current->indice_domaine;
        } while(!(testContraintDiff(current->diff,current->value) 
                && testContraintSomme(current->sum_H) 
                && testContraintSomme(current->sum_V)));
        ++i;
        current = v[i];
    }
}

int testContraintSomme(Constraints_Sum * contraint){
    if(contraint == NULL){
        return 42;
    }
    int i = 0;
    int sum = 0;
    while(contraint->vars[i]){
        if(contraint->vars[i]->value == -1){
            return 42;
        }
        sum += contraint->vars[i]->value;
        if(sum > contraint->value){
            return 0;
        }
        ++i;
    }
    if(sum == contraint->value){
        return 42;
    }
    
    return 0;
}

int testContraintDiff(Constraints_Diff *  contraint, int val){
    int i = 0;
    while(contraint->vars[i]){
        if (contraint->vars[i]->value == val){
            return 0;
        }
        ++i;
    }
    
    return 42;
}  
