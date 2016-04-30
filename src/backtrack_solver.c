#include "backtrack_solver.h"

void backtrack(Variable **v, int number_of_empty_case, Stat *stats){
    int i = 0;
    Variable *current = v[i];
    while(i < number_of_empty_case){
        do{
            while(current->indice_domaine > sizeDomain){
                current->indice_domaine = 0;
                if(i == 0) echec(v, number_of_empty_case);
                current->value = -1;
                --i;
                current = v[i];
            }
            current->value = current->tabdomainVar[current->indice_domaine];
            ++stats->nb_node;
            ++current->indice_domaine;
        } while(!(testContraintDiff(current->diff, current->value, stats)
                && testContraintSomme(current->sum_H, stats)
                && testContraintSomme(current->sum_V, stats)));
        ++i;
        current = v[i];
    }
}
