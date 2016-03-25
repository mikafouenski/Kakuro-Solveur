#include "backtrack_solver.h"

void backtrack(Variable **v){
    int i = 0;
    Variable *current = v[i];
    while(i < number_of_empty_case){
        do {
            while(current->indice_domaine > sizeDomain){
                current->indice_domaine = 0;
                if(i == 0) echec();
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
