#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "kakuro_solver.h"
#include "time.h"

int main(int argc, char **argv) {
    int bflag = 0;
    int fflag = 0;
    int c;
    opterr = 0;

    while ((c = getopt (argc, argv, "bf")) != -1) {
        switch (c) {
            case 'b':
                bflag = 1;
                break;
            case 'f':
                fflag = 1;
                break;
            case '?':
                fprintf (stderr, "Option inconnu `\\x%x'.\n", optopt);
                return 1;
            default:
                abort ();
        }
    }

    FILE *f = fopen(argv[optind], "r"); 
    if(f == NULL){
        perror("fopen");
        return 1;
    }

    clock_t beginning, end;
    beginning = clock();

    if (bflag)
        solve_kakuro(f, 0);
    else if (fflag)
        solve_kakuro(f, 1);


    end = clock();
    printf("%lf\n",(double) (end - beginning) / CLOCKS_PER_SEC);

    fclose(f);
    return 0;
}

