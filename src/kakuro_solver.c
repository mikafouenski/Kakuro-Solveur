#include <stdio.h>
#include <stdlib.h>

#include "kakuro_solver.h"

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))

int EmptyCaseIndice = 0;
int numberOfEmptyCase = 0;
int size_length = 0;
int size_width = 0;

void addContraintVertical(int indice,int number){
    Constraints_Sum *sum = malloc( sizeof(Constraints_Sum));
    sum->value = number;
    sum->vars = malloc (sizeof(Variable) * numberOfEmptyCase);
    indice += size_width;
    int i = 0;
    while(variables[indice]){
        sum->vars[i] = variables[indice];
        variables[indice]->sum_V = sum;
        ++i;
        indice += size_width;
    }
}

void addContraintHorizontal(int indice, int number){
    Constraints_Sum *sum = malloc( sizeof(Constraints_Sum));
    sum->value = number;
    sum->vars = malloc (sizeof(Variable) * numberOfEmptyCase);
    ++indice;
    if(!variables[indice]) printf("%d\n",indice);
    int i = 0;
    while(variables[indice]){
        sum->vars[i] = variables[indice];
        variables[indice]->sum_H = sum;
        ++i;
        ++indice;
    }
}

void AfficheContrainte(Constraints_Sum *sum){
    int i;
    printf("Contrainte sum ");
    printf("%d ---", sum->value);
    for(i = 0; sum->vars[i]; ++i)
        printf(" %d ",sum->vars[i]->indice);
    printf("\n");
}

void initVal(FILE *file){
    char readed_char = fgetc(file);
    while (readed_char != EOF) {
        if(readed_char == '.' || readed_char == '\\')
            ++size_width;
        if(readed_char == '\n')
            ++size_length;
        readed_char = fgetc(file);
    }
    size_width = size_width/size_length;
    variables = malloc(size_width * size_length * sizeof (Variable));
}

void RechercheCaseBlanche(FILE *file){
    rewind(file);
    char readed_char;
    int x = 0;
    readed_char = fgetc(file);
    while (readed_char != EOF) {
        Variable *var = malloc (sizeof (Variable));
        switch (readed_char) {
            case '.' :
                var->value = -1;
                var->indice = EmptyCaseIndice;
                variables[x] = var;
                ++numberOfEmptyCase;
            case '\\':
                ++EmptyCaseIndice; 
                ++x;
                break;
            default:
                break;
        }
        readed_char = fgetc(file);
    }
}

void RechercheContrainte(FILE *file){
    rewind(file);
    char readed_char;
    int number1 = 0;
    int number2 = 0;
    int indice = 0;
    readed_char = fgetc(file);
    while(readed_char != EOF){
        switch(readed_char ){
            case '\\':
                if(number1 != 0){
                    addContraintVertical(indice,number1);
                    number1 = 0;
                }
                readed_char = fgetc(file);
                while(is_num (readed_char)){
                    number2 *= 10;
                    number2 += atoi(&readed_char);
                    readed_char = fgetc(file);
                }
                if(number2){
                    addContraintHorizontal(indice,number2);
                    number2 = 0;
                }
            case '.' :
                ++indice;
                break;
            default :
                if (is_num(readed_char)){
                    number1 *= 10;
                    number1 += atoi(&readed_char);
                }
                break;
        }
        readed_char = fgetc(file);
    }
}

void solve_kakuro (FILE *file) {
    initVal(file);
    RechercheCaseBlanche(file);
    RechercheContrainte(file);
    int i;
    for (i=0; i < size_width * size_length; ++i){
        if(variables[i]) {
            Variable *var2 = variables[i];
            printf("Case n°%d \n", var2->indice); 
            printf("Contrainte Horizontal \n"); 
            if (var2->sum_V)
               AfficheContrainte(var2->sum_V);
           printf("Contrainte Vertical \n"); 
           if (var2->sum_H)
            AfficheContrainte(var2->sum_H);
        }
    }
}
