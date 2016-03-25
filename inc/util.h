#include <stdio.h>
#include <stdlib.h>

#ifndef _UTILH_
#define _UTILH_

#define sizeDomain 9


typedef struct Constraints_Sum Constraints_Sum;
typedef struct Constraints_Diff Constraints_Diff;
typedef struct Variable Variable;


struct Variable{
    int indice; //only for debug
    int value;
    Constraints_Sum *sum_H;
    Constraints_Sum *sum_V;
    Constraints_Diff *diff;
    int tabdomainVar[sizeDomain];
    int indice_domaine;
};


struct Constraints_Sum{
    int value;
    Variable **vars;
};

struct Constraints_Diff{
    Variable **vars;
};

Variable **variables;
Variable **variablesInst;

int testContraintDiff();

int testContraintSomme();

#endif