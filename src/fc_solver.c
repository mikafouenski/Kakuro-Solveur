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


void eraseContraintSum(Variable *v, Constraints_Sum cs){
    
        Constraints_Sum cs = v->sum_H;
        int sum = 0;
        int i = 0;
        int nb_non_inst = 0;
        int max; 
        while(cs->vars[i]){
            if(cs->vars[i]->value != -1){
                sum += cs->vars[i]->value;
                ++nb_non_inst;
            }
        }
        if(nb_non_inst == 1){
            max = sum - cs->value;
            for (i = 0; i < sizeDomain; ++i)
            {
                if(i != max)
                    v->tabdomain[i] = -1;
            }
        }
        else {
           max = sum - cs->value;
           if(max <= 9){
                for (i = 0;i <= max; ++i)
                {
                    v->tabdomain[i] = -1;
                }
           }
        } 
    
}


void eraseDomain(Variable *v){
    //Contraint_h
    
    //Contraint_V
    //Contraint_D
    if(v->diff){
        Constraints_Diff dc = v->diff;
        int i;
        for (i = 0; dc->vars[i]; ++i)
        {
            if(dc->vars[i] != -1){
                v->tabdomainVar[dc->vars[i]->value-1] = -1;
            }
        }
    }

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


