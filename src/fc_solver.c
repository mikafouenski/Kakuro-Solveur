#include "fc_solver.h"

void rebootDomain(Variable *v) {
    for (int i = 0; i < sizeDomain; ++i)
        v->tabdomainVar[i] = tabdomain[i];
}

void eraseContraintSum(Variable *v, Constraints_Sum *cs ) {
    int sum = 0;
    int i = 0;
    int is_declared = 0;
    int max;
    while(cs->vars[i]) {
        if(cs->vars[i]->value != -1) {
            sum += cs->vars[i]->value;
            ++is_declared;
        }
    }
    if(is_declared == 1) {
        max = cs->value - sum;
        for (i = 0; i < sizeDomain; ++i)
            if(i != max-1)
                v->tabdomainVar[i] = -1;
    } else {
        max =  cs->value - sum;
        if(max <= 9)
            for (i = 0;i < sizeDomain; ++i)
                if(i >= max-1)
                    v->tabdomainVar[i] = -1;
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

void fc(Variable **v) {
    int i = 0;
    Variable *current = v[i];
    while(i < number_of_empty_case) {
        eraseDomain(current);
        do {
            while(current->indice_domaine > sizeDomain || 
                current->tabdomainVar[current->indice_domaine] == -1)
                ++current->indice_domaine;
            current->value = current->tabdomainVar[current->indice_domaine];
            while(current->indice_domaine > sizeDomain) {
                current->indice_domaine = 0;
                if(i == 0) echec();
                rebootDomain(current);
                current->value = -1;
                --i;
                current = v[i];
            }
            ++current->indice_domaine;
        } while(!(testContraintDiff(current->diff,current->value) && 
            testContraintSomme(current->sum_H) &&
            testContraintSomme(current->sum_V)));
        ++i;
        current = v[i];
    }
}
