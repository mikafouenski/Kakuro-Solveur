#include "kakuro_solver.h"
#include "time.h"
int main(int argc, char const *argv[]) {
    FILE *fic = fopen("kakuro_grid/grille_8x8b.txt","r");
    if(fic == NULL) {
        perror("fopen");
        exit(1);
    }
    clock_t beginning, end;
    beginning = clock();
    solve_kakuro(fic, 1);
    end = clock();
    printf("%lf\n",(double) (end - beginning) / CLOCKS_PER_SEC);
    fclose(fic);
    return 0;
}
