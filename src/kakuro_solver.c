#include "kakuro_solver.h"
#include "backtrack_solver.h"
#include "fowardchecking_solver.h"

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))

int empty_case_indice = 0;

void add_c_sum_vertical(int indice,int number) {
    Constraints_Sum *sum = malloc(sizeof(Constraints_Sum));
    sum->value = number;
    sum->vars = calloc (number_of_empty_case, sizeof(Variable));
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
    sum->vars = calloc (number_of_empty_case, sizeof(Variable));
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
    diff->vars = calloc (number_of_empty_case, sizeof(Variable));
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
    variables = calloc (size_width * size_length, sizeof(Variable));
}

void search_empty_case(FILE *file){
    rewind(file);
    char readed_char;
    int x = 0;
    Variable *var;
    readed_char = fgetc(file);
    while (readed_char != EOF) {
        switch (readed_char) {
            case '.' :
                var = malloc (sizeof (Variable));
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
    int readed_char;
    int number1 = 0;
    int number2 = 0;
    int indice = 0;
    readed_char = fgetc(file);
    while(readed_char != EOF) {
        switch(readed_char) {
            case '\\':
                if(number1 != 0) {
                    add_c_sum_vertical(indice,number1);
                    number1 = 0;
                }
                readed_char = fgetc(file);
                if(is_num(readed_char)) {
                    ungetc(readed_char,file);
                    fscanf(file,"%d",&number2);
                }
                if(number2 != 0) {
                    add_c_sum_horizontal(indice,number2);
                    number2 = 0;
                }
            case '.':
                ++indice;
                break;
            default :
                if (is_num(readed_char)) {
                    ungetc(readed_char,file);
                    fscanf(file,"%d",&number1);
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
    variablesInst = calloc(number_of_empty_case, sizeof(Variable));
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

void print_result () {
    int indice = 0;
    int j = 0;
    while(variablesInst[indice]){
        if(j % size_width == 0){
            printf("\n");
        }
        if(j == variablesInst[indice]->indice){
            printf(" %d ",variablesInst[indice]->value);
            ++indice;
        }
        else
            printf(" . ");
        ++j;
    }
    printf("\n");
    printf("\n");
}

void solve_kakuro (FILE *file, int useFowardChecking) {
    initVal(file);
    search_empty_case(file);
    search_contraints(file);
    search_variable(variables);

    if (useFowardChecking)
        fowardchecking(variablesInst);
    else 
        backtrack(variablesInst);

    print_result();
    freedom();
}
