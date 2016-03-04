#include <stdio.h>
#include <stdlib.h>

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))

#define X_MAX   (5)
#define Y_MAX   (6)

int matrix[X_MAX][Y_MAX];

typedef struct {
    int value;
    int **tabPointer;
} C_Sum;

typedef struct {
    int **tabPointer;
} C_Diff;

typedef struct {
    int value;
    int **tabDomain;
    C_Sum horizontal;
    C_Sum vertical;
} Variable;

void readFile (FILE *f) {
    int x = 0;
    int y = 0;

    char caracLu = fgetc(f);

    while (caracLu != EOF) {
        printf("%c",caracLu);
        switch (caracLu) {
            case '.':
                
                matrix[y][x] = -1;

                ++x;
            break;
            case '\n' :
                 printf("\n");
                ++y;
                x = 0;
            break;
            case ' ':
            break;
            default:
                printf("%d",y);
                matrix[y][x] = -2;
                ++x;
                break;
        }
        caracLu = fgetc(f);
        while(is_num(caracLu)){
            caracLu = fgetc(f);    
        }
    }

    rewind(f);
    
    for (int i = 0; i < X_MAX; ++i)
    {
        for (int j = 0; j < Y_MAX; ++j)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    /*
    //Recherche contrainte horizontal
    while (caracLu != EOF){
        if (caracLu == '\\') {
            caracLu = fgetc(f);
            if (is_num(caracLu)) {
                c2 = atoi(caracLu);
                caracLu = fgetc(f);
                while(is_num(caracLu)) {
                    c2 = c2 * 10 + atoi(caracLu);
                    caracLu = fgetc(f);
                }
                if (c2 != 0) {
                    C_Sum sum_horizon;
                    while(caracLu != '\\'|| caracLu != '\n' ){
                        caracLu = fgetc(f);
                        C_Sum.tabPointer
                    }
                    c2 = 0;
                }
            }
        }
        caracLu = fgetc(f);
    }*/
}

int main(int argc, char const *argv[])
{
    FILE *fic = fopen("kakuro/enonce.txt","r");
    if(fic == NULL){
        perror("fopen");
        exit(1);
    }
    for (int i = 0; i < X_MAX; ++i)
        for (int j = 0; j < Y_MAX; ++j)
            matrix[i][j] = -1;
    readFile(fic);
    fclose(fic);
    return 0;
}
