#include <stdio.h>
#include <stdlib.h>

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))

#define X_MAX   (5)
#define Y_MAX   (6)
#define ta (7878)
/*

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

Variable tabVariables[ta];
int indiceTaVar = 0
*/

int matrix[X_MAX][Y_MAX];
typedef struct CaseVide CaseVide;

struct CaseVide
{
  int x; 
  int y;
};

CaseVide *tabCaseVide;


struct Variable;
typedef struct Variable Variable;

typedef struct ContrainteSomme ContrainteSomme;
struct ContrainteSomme
{
    int result;
    Variable *tabVariables; 
};

typedef struct ConTrainteDifference ConTrainteDifference;
struct ConTrainteDifference
{
    Variable *tabVariables; 
};

struct Variable
{
    int valeur;
    ContrainteSomme tabContrainteSommeVert;
    ContrainteSomme tabContrainteSommeHori;
    ConTrainteDifference tabContrainteDiffere;
};


typedef struct 
{
    Variable *tabVariables;
   // int tabDomain[8] = {1,2,3,4,5,6,7,8,9}; //toDo
} CSP ;


void poubelle(){
    free(tabCaseVide);
    // free(p.tabVariables);
    // free(p.tabContrainteSomme);
    // free(p.tabContrainteDiffere);
}

void readFile (FILE *f) {
    int x = 0;
    int y = 0;

    char caracLu = fgetc(f);
    int tailleLargeur = 0;
    int tailleLongueur = 0;
    while (caracLu != EOF) {
        if(caracLu == '.' || caracLu == '\\')
            ++tailleLongueur;
        if(caracLu == '\n'){
            ++tailleLargeur; 
        }
        caracLu = fgetc(f);
    }
    tailleLongueur = tailleLongueur/tailleLargeur;
    tabCaseVide = malloc(tailleLongueur * tailleLargeur * sizeof (CaseVide));
   // CSP p;
   // p.tabVariables = malloc(tailleLongueur * tailleLargeur * sizeof (Variable));
    //p.tabVaritabContrainteSomme = malloc(tailleLongueur * tailleLargeur * sizeof (ContrainteSomme));
    //p.tabContrainteDiffere = malloc(tailleLongueur * tailleLargeur * sizeof (ContrainteDifference));
    
    printf("Taille Largeur %d\n", tailleLargeur);
    printf("Taille Longeur %d\n", tailleLongueur);
    
    rewind(f);
    caracLu = fgetc(f);
    while (caracLu != EOF) {
        switch (caracLu) {
            case '.':
            matrix[y][x] = -1;
            ++x;
            break;
            case '\n' :
            ++y;
            x = 0;
            break;
            case ' ':
            break;
            default:
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
    //ViderCsp(p);
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
        poubelle();
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
