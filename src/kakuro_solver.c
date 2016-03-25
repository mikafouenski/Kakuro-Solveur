#include "kakuro_solver.h"

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))

int empty_case_indice = 0;

void add_c_sum_vertical(int indice,int number) {
    Constraints_Sum *sum = malloc(sizeof(Constraints_Sum));
    sum->value = number;
    sum->vars = malloc (sizeof(Variable) * number_of_empty_case);
    indice += size_width;
    int i = 0;
    while(variables[indice]) {
        sum->vars[i] = variables[indice];
        variables[indice]->sum_V = sum;
        ++i;
        indice += size_width;
    }
}

void add_c_sum_horizontal(int indice, int number) {
    Constraints_Sum *sum = malloc( sizeof(Constraints_Sum));
    sum->value = number;
    sum->vars = malloc (sizeof(Variable) * number_of_empty_case);
    ++indice;
    int i = 0;
    while(variables[indice]) {
        sum->vars[i] = variables[indice];
        variables[indice]->sum_H = sum;
        ++i;
        ++indice;
    }
}

void add_c_diff(Variable * var) {
    Constraints_Diff *diff = malloc(sizeof(Constraints_Diff));
    diff->vars = malloc (sizeof(Variable) * number_of_empty_case);
    int i = 0;
    int j = 0;
    if(var->sum_H){
        while(var->sum_H->vars[i]) {
            if(var->sum_H->vars[i] != var) {
                diff->vars[j] = var->sum_H->vars[i];
                ++j;
            }
            ++i;
        }
    }
    i = 0;
    if(var->sum_V){
        while(var->sum_V->vars[i]) {
            if(var->sum_V->vars[i] != var){
                diff->vars[j] = var->sum_V->vars[i];
                ++j;
            }
            ++i;
        }
    }
    var->diff = diff;
}

// void display_contraints(Constraints_Sum *sum){
//     int i;
//     printf("Contrainte sum ");
//     printf("%d ---", sum->value);
//     for(i = 0; sum->vars[i]; ++i)
//         printf(" %d ",sum->vars[i]->indice);
//     printf("\n");
// }

// void display_contraints_diff(Constraints_Diff *diff) {
//     int i;
//     printf("Contrainte diff ");
//     for(i = 0; diff->vars[i]; ++i)
//         printf(" %d ",diff->vars[i]->indice);
//     printf("\n");
// }

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

void search_empty_case(FILE *file){
    rewind(file);
    char readed_char;
    int x = 0;
    readed_char = fgetc(file);
    while (readed_char != EOF) {
        Variable *var = malloc (sizeof (Variable));
        switch (readed_char) {
            case '.' :
                var->value = -1;
                var->indice = empty_case_indice;
                variables[x] = var;
                ++number_of_empty_case;
            case '\\':
                ++empty_case_indice; 
                ++x;
                break;
            default:
                break;
        }
        readed_char = fgetc(file);
    }
}

void search_contraints(FILE *file){
    rewind(file);
    char readed_char;
    int number1 = 0;
    int number2 = 0;
    int indice = 0;
    readed_char = fgetc(file);
    while(readed_char != EOF) {
        switch(readed_char ) {
            case '\\':
                if(number1 != 0) {
                    add_c_sum_vertical(indice,number1);
                    number1 = 0;
                }
                readed_char = fgetc(file);
                while(is_num(readed_char)) {
                    number2 *= 10;
                    number2 += atoi(&readed_char);
                    readed_char = fgetc(file);
                }
                if(number2) {
                    add_c_sum_horizontal(indice,number2);
                    number2 = 0;
                }
            case '.':
                ++indice;
                break;
            default :
                if (is_num(readed_char)) {
                    number1 *= 10;
                    number1 += atoi(&readed_char);
                }
                break;
        }
        readed_char = fgetc(file);
    }
}

void initDomain(Variable * var){
    for (int i = 0; i < sizeDomain; ++i)
        var->tabdomainVar[i] = tabdomain[i];
}

void search_variable(Variable **tabvariables){
    variablesInst = malloc(sizeof (Variable) * number_of_empty_case);
    int j = 0;
    int i;
    for (i = 0; i < (size_width * size_length); ++i) {
        if(variables[i]) {
            variablesInst[j] = variables[i];
            initDomain(variablesInst[j]);
            variablesInst[j]-> indice_domaine = 0; 
            add_c_diff(variablesInst[j]);
            ++j;
        }
    }
}

void solve_kakuro (FILE *file, int useFowardChecking) {
    initVal(file);
    search_empty_case(file);
    search_contraints(file);
    search_variable(variables);
    int i;
    if (useFowardChecking)
        fc(variablesInst);
    else
        backtrack(variablesInst);
    for (i=0; i < number_of_empty_case; ++i) {
        Variable *var2 = variablesInst[i];
        printf("Case n°%d : %d", var2->indice,var2->value); 
        printf("\n");
    }
    freedom();
}
