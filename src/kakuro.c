#include <stdio.h>
#include <stdlib.h>
#include "kakuro_solver.h"


int main(int argc, char const *argv[]) {
    FILE *fic = fopen("kakuro_grid/grille_8x8a.txt","r");
    if(fic == NULL) {
        perror("fopen");
        exit(1);
    }
    solve_kakuro(fic);
    fclose(fic);
    return 0;
}
