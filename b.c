#include <stdio.h>
#include <stdlib.h>

typedef struct Constraints_Sum Constraints_Sum; 
typedef struct Constraints_Dif Constraints_Dif;
typedef struct Variable Variable;
//typedef struct Variable Variable;

struct Variable{
    int value;
    Constraints_Sum *somme_H;
    Constraints_Sum *somme_V;
    Constraints_Dif *diff;
    //int domain[9] = {1,2,3,4,5,6,7,8,9};
    int indice_domaine;
};


struct Constraints_Sum{
    int value;
    Variable **vars;
};

struct Constraints_Dif{
    Variable **vars;
};

Variable **variables;


void a (FILE *f) {
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
    variables = malloc(tailleLongueur * tailleLargeur * sizeof (Variable));
      
    rewind(f);
    x = 0;
    caracLu = fgetc(f);
    while (caracLu != EOF) {
        Variable *var = malloc (sizeof (Variable));
         switch (caracLu) {
             case '.' :
                var->value = -1;
                variables[x] = var ;
             case '\\':
                 ++x;
             break;
             default:
                 break;
        }
       caracLu = fgetc(f);
    }
    variables[10]->value = 2;
    for (x=0; x < tailleLongueur * tailleLargeur; ++x){
        if(variables[x]) {
            Variable *var2 = variables[x];
            printf("%d ",var2->value); 
        } else {
            printf("%d ",0);
        }
    }
    printf("\n");
}

int main(int argc, char const *argv[]) {
    FILE *fic = fopen("kakuro/enonce.txt","r");
    if(fic == NULL) {
        perror("fopen");
        exit(1);
    }
    a(fic);
    fclose(fic);
    return 0;
}
