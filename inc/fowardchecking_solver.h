#ifndef __FOWARDCHECKING_H__
#define __FOWARDCHECKING_H__

#include "util.h"

/**
 * @brief      foward-checking main algorithm
 *
 * @param      v                     Array of all variables
 * @param[in]  number_of_empty_case  The number of empty case
 * @param      stats                 Just here to record stats
 */
void fowardchecking(Variable **v, int number_of_empty_case, Stat *stats);

#endif
