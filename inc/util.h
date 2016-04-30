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

/**
 * @brief      The main struct, store all the informations
 */
struct Variable {
    int indice;
    int value;
    Constraints_Sum *sum_H;
    Constraints_Sum *sum_V;
    Constraints_Diff *diff;
    int tabdomainVar[sizeDomain];
    int indice_domaine;
};

/**
 * @brief      Store the sum constraint
 */
struct Constraints_Sum {
    int value;
    Variable **vars;
};

/**
 * @brief      Store the difference constraint
 */
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

/**
 * @brief      Test of sum constraint
 *
 * @param      contraint  The contraint
 * @param      stats      The stats
 *
 * @return     the boolean if the constraints is filled
 */
int testContraintSomme(Constraints_Sum * contraint, Stat *stats);

/**
 * @brief      Test of difference constraint
 *
 * @param      contraint  The contraint
 * @param[in]  val        The val
 * @param      stats      The stats
 *
 * @return     the boolean if the constraints is filled
 */
int testContraintDiff(Constraints_Diff *  contraint, int val, Stat *stats);

/**
 * @brief      The echec function
 *
 * @param      variablesInst         The variables
 * @param[in]  number_of_empty_case  The number of empty case
 */
void echec(Variable **variablesInst, int number_of_empty_case);

/**
 * @brief      Just fill the domain a variable
 *
 * @param      var   The var
 */
void initDomain(Variable * var);

/**
 * @brief      Function to free all the structure
 *
 * @param      vars                  The vars
 * @param[in]  number_of_empty_case  The number of empty case
 */
void freedom(Variable **v, int number_of_empty_case);

#endif
