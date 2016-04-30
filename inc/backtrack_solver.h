#ifndef __BACKTRACK_H__
#define __BACKTRACK_H__

#include "util.h"

/**
 * @brief      Backtracking algorithm
 *
 * @param      v                     Array of all variables
 * @param[in]  number_of_empty_case  The number of empty case
 * @param      stats                 Stat struct, just to record
 */
void backtrack(Variable **v, int number_of_empty_case, Stat *stats);

#endif
