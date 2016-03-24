#include <stdio.h>
#include "../inc/kakuro_solver.h"
#include "../inc/backtrack_solver.h"
#include "../inc/fc.h"

void fc(Variable **v){
    int i = 0;
    Variable *current = v[i];
    while(i < number_of_empty_case){
        do {
            while(indice_domaine > sizeDomain || 
                current->tabdomainVar[current->indice_domaine] == -1){
                ++indice_domaine;
            }
            current->value = current->tabdomainVar[current->indice_domaine];
            
            while(current->indice_domaine > sizeDomain){
                current->indice_domaine = 0;
                if(i == 0){
                  echec();
                }
                current->value = -1;
                --i;
                current = v[i];
            }
            ++current->indice_domaine;
        } while(!(testContraintDiff(current->diff,current->value) 
                && testContraintSomme(current->sum_H) 
                && testContraintSomme(current->sum_V)));
        eraseDomain(current->diff,current->sum_H,current->sum_V);
        ++i;
        current = v[i];
    }
}
