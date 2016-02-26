#include <stdio.h>
#include <stdlib.h>

int matrix[50][50];

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

    while (caracLu != EOF){
        switch (caracLu) {
            
        }
        caracLu = fgetc(f);
    }
}

int main(int argc, char const *argv[])
{
    FILE *fic = fopen("kakuro/enonce.txt","r");
    if(fic == NULL){
        perror("fopen");
        exit(1);
    }

    /*matrix[0][0] = 50;
    for (int i = 0; i < 50; ++i)
    {
        for (int j = 0; j < 50; ++j)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }*/
    readFile(fic);

    return 0;
}
