#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdlib.h>

#define sizeDomain 9

typedef struct Constraints_Sum Constraints_Sum;
typedef struct Constraints_Diff Constraints_Diff;
typedef struct Variable Variable;
typedef struct Size Size;

struct Variable {
    int indice;
    int value;
    Constraints_Sum *sum_H;
    Constraints_Sum *sum_V;
    Constraints_Diff *diff;
    int tabdomainVar[sizeDomain];
    int indice_domaine;
};

struct Constraints_Sum {
    int value;
    Variable **vars;
};

struct Constraints_Diff {
    Variable **vars;
};

struct Size {
    int length;
    int width;
};

int testContraintDiff();

int testContraintSomme();

void echec();

void initDomain(Variable * var);

void freedom();

#endif
