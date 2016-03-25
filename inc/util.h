#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdlib.h>

#define sizeDomain 9

int tabdomain[sizeDomain];
int number_of_empty_case;
int size_length;
int size_width;

typedef struct Constraints_Sum Constraints_Sum;
typedef struct Constraints_Diff Constraints_Diff;
typedef struct Variable Variable;

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

Variable **variables;
Variable **variablesInst;

int testContraintDiff();

int testContraintSomme();

void echec();

void freedom();

#endif
