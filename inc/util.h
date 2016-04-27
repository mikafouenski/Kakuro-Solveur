#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdlib.h>

#define sizeDomain 9

typedef struct Constraints_Sum Constraints_Sum;
typedef struct Constraints_Diff Constraints_Diff;
typedef struct Variable Variable;
typedef struct Size Size;
typedef struct Stat Stat;

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

struct Stat {
    int nb_node;
    int nb_test_constraints;
};

int testContraintDiff(Constraints_Diff *  contraint, int val, Stat *stats);

int testContraintSomme(Constraints_Sum * contraint, Stat *stats);

void echec(Variable **variablesInst, int number_of_empty_case, int size_width);

void initDomain(Variable * var);

void freedom(Variable **v, int number_of_empty_case, int size_width);

#endif
