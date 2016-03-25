#include "fc_solver.h"
#include "kakuro_solver.h"

extern int number_of_empty_case;
extern int tabdomain[sizeDomain];

void rebootDomain(Variable *v){
    for (int i = 0; i < sizeDomain; ++i)
    {
        v->tabdomainVar[i] = tabdomain[i];
    }
}

void eraseDomain(Variable *v){

}

void echec(){
    printf("TG Micka\n");
    freedom();
    exit(1);
}

void fc(Variable **v){
    int i = 0;
    Variable *current = v[i];
    while(i < number_of_empty_case){
        eraseDomain(current);
        do {
            while(current->indice_domaine > sizeDomain || 
                current->tabdomainVar[current->indice_domaine] == -1){
                ++current->indice_domaine;
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
        ++i;
        current = v[i];
    }
}


