#include "util.h"

/**
 * @brief      Test of sum constraint
 *
 * @param      contraint  The contraint
 * @param      stats      The stats
 *
 * @return     the boolean if the constraints is filled
 */
int testContraintSomme(Constraints_Sum * contraint, Stat *stats){
    stats->nb_test_constraints++;
    if(contraint == NULL) return 42;
    int i = 0;
    int sum = 0;
    while(contraint->vars[i]){
        if(contraint->vars[i]->value == -1) return 42;
        sum += contraint->vars[i]->value;
        if(sum > contraint->value) return 0;
        ++i;
    }
    if(sum == contraint->value) return 42;
    return 0;
}

/**
 * @brief      Test of difference constraint
 *
 * @param      contraint  The contraint
 * @param[in]  val        The val
 * @param      stats      The stats
 *
 * @return     the boolean if the constraints is filled
 */
int testContraintDiff(Constraints_Diff *  contraint, int val, Stat *stats){
    stats->nb_test_constraints++;
    int i = 0;
    while(contraint->vars[i]){
        if (contraint->vars[i]->value == val) return 0;
        ++i;
    }
    return 42;
}

/**
 * @brief      The echec function
 *
 * @param      variablesInst         The variables
 * @param[in]  number_of_empty_case  The number of empty case
 */
void echec(Variable **variablesInst, int number_of_empty_case){
    printf("Aucune solution trouvé!\n");
    freedom(variablesInst, number_of_empty_case);
    exit(1);
}

/**
 * @brief      Just fill the domain a variable
 *
 * @param      var   The var
 */
void initDomain(Variable * var){
    for (int i = 0; i < sizeDomain; ++i)
        var->tabdomainVar[i] = i + 1;
}

/**
 * @brief      Determine if in sum.
 *
 * @param      sums                  The sums
 * @param      s                     The sum
 * @param[in]  number_of_empty_case  The number of empty case
 *
 * @return     True if in sum, False otherwise.
 */
int is_in_sum(Constraints_Sum **sums, Constraints_Sum *s, int number_of_empty_case) {
    int i = 0;
    while(sums[i]) {
        if (sums[i] == s) return 42;
        ++i;
    }
    return 0;
}

/**
 * @brief      Determine if in diff.
 *
 * @param      diffs                 The diffs
 * @param      s                     The diff
 * @param[in]  number_of_empty_case  The number of empty case
 *
 * @return     True if in diff, False otherwise.
 */
int is_in_diff(Constraints_Diff **diffs, Constraints_Diff *s, int number_of_empty_case) {
    int i = 0;
    while(diffs[i]) {
        if (diffs[i] == s) return 42;
        ++i;
    }
    return 0;
}

/**
 * @brief      Function to free all the structure
 *
 * @param      vars                  The vars
 * @param[in]  number_of_empty_case  The number of empty case
 */
void freedom (Variable **vars, int number_of_empty_case) {
    int i_diffs = 0;
    Constraints_Diff **diffs = calloc (number_of_empty_case, sizeof (Constraints_Diff));
    int i_sums = 0;
    Constraints_Sum **sums = calloc (number_of_empty_case, sizeof (Constraints_Sum));

    for (int i = 0; i < number_of_empty_case; ++i) {
        Variable *v = vars[i];
        if (v->sum_H && (! is_in_sum(sums, v->sum_H, number_of_empty_case)) ) {
            sums[i_sums] = v->sum_H;
            ++i_sums;
        }
        if (v->sum_V && (! is_in_sum(sums, v->sum_V, number_of_empty_case)) ) {
            sums[i_sums] = v->sum_V;
            ++i_sums;
        }
        if (v->diff && (! is_in_diff(diffs, v->diff, number_of_empty_case)) ) {
            diffs[i_diffs] = v->diff;
            ++i_diffs;
        }
    }

    int i = 0;
    while(i < number_of_empty_case && sums[i]) {
        free(sums[i]->vars);
        free(sums[i]);
        ++i;
    }

    i = 0;
    while(i < number_of_empty_case && diffs[i]) {
        free(diffs[i]->vars);
        free(diffs[i]);
        ++i;
    }

    i = 0;
    while(i < number_of_empty_case && vars[i]) {
        free(vars[i]);
        ++i;
    }

    free(diffs);
    free(sums);
    free(vars);
}
