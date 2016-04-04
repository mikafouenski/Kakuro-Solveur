#include "kakuro_solver.h"

int main(int argc, char const *argv[]) {
    FILE *fic = fopen("kakuro_grid/grille_12x12a.txt","r");
    if(fic == NULL) {
        perror("fopen");
        exit(1);
    }
    solve_kakuro(fic, 1);
    fclose(fic);
    return 0;
}
