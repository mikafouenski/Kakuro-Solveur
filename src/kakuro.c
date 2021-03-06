#include <ctype.h>
#include <unistd.h>
#include "time.h"

#include "backtrack_solver.h"
#include "fowardchecking_solver.h"

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))

/**
 * @brief      Add a vertical Sum constraint 
 *
 * @param      variables             The variables array
 * @param[in]  indice                The indice
 * @param[in]  number                The value
 * @param[in]  number_of_empty_case  The number of empty case
 * @param[in]  size_width            The size width
 */
void add_c_sum_vertical(Variable **variables, int indice, int number, int number_of_empty_case, int size_width) {
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

/**
 * @brief      Add a horizontal Sum constraint 
 *
 * @param      variables             The variables array
 * @param[in]  indice                The indice
 * @param[in]  number                The value
 * @param[in]  number_of_empty_case  The number of empty case
 * @param[in]  size_width            The size width
 */
void add_c_sum_horizontal(Variable **variables, int indice, int number, int number_of_empty_case, int size_width) {
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

/**
 * @brief      Add a difference constraint
 *
 * @param      var                   The var
 * @param[in]  number_of_empty_case  The number of empty case
 */
void add_c_diff(Variable * var, int number_of_empty_case) {
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

/**
 * @brief      Get the size of the grid
 *
 * @param      file  The input file
 *
 * @return     Struct Size filed
 */
Size initVal(FILE *file){
    Size size;
    size.width = 0;
    size.length = 0;
    char readed_char = fgetc(file);
    while (readed_char != EOF) {
        if(readed_char == '.' || readed_char == '\\')
            ++size.width;
        if(readed_char == '\n')
            ++size.length;
        readed_char = fgetc(file);
    }
    size.width = size.width/size.length;
    return size;
}

/**
 * @brief      malloc all the variables
 *
 * @param      file       The input file
 * @param      variables  The variables array
 *
 * @return     the number of empty cases
 */
int search_empty_case(FILE *file, Variable **variables){
    rewind(file);
    int number_of_empty_case = 0;
    int empty_case_indice = 0;
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
    return number_of_empty_case;
}

/**
 * @brief      Fill all the Sums constraints
 *
 * @param      file                  The input file
 * @param      variables             The variables
 * @param[in]  number_of_empty_case  The number of empty case
 * @param[in]  size                  The size
 */
void search_contraints(FILE *file, Variable **variables, int number_of_empty_case, Size size){
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
                    add_c_sum_vertical(variables ,indice, number1, number_of_empty_case, size.width);
                    number1 = 0;
                }
                readed_char = fgetc(file);
                if(is_num(readed_char)) {
                    ungetc(readed_char,file);
                    fscanf(file,"%d",&number2);
                }
                if(number2 != 0) {
                    add_c_sum_horizontal(variables ,indice, number2, number_of_empty_case, size.width);
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

/**
 * @brief      Make an array with none NULL address and create difference
 *             constraints
 *
 * @param      variables             The variables
 * @param[in]  number_of_empty_case  The number of empty case
 * @param[in]  size                  The size
 *
 * @return     new array of variables
 */
Variable** search_variable(Variable **variables, int number_of_empty_case, Size size){
    Variable **variablesInst = calloc(number_of_empty_case, sizeof(Variable));
    int j = 0;
    int i;
    for (i = 0; i < (size.width * size.length); ++i) {
        if(variables[i]) {
            variablesInst[j] = variables[i];
            initDomain(variablesInst[j]);
            variablesInst[j]-> indice_domaine = 0; 
            add_c_diff(variablesInst[j], number_of_empty_case);
            ++j;
        }
    }
    return variablesInst;
}

/**
 * @brief      Display th result
 *
 * @param      variablesInst  The variables
 * @param[in]  size           The size
 */
void print_result (Variable **variablesInst, Size size) {
    int indice = 0;
    int j = 0;
    while(variablesInst[indice]){
        if(j % size.width == 0){
            printf("\n\t");
        }
        if(j == variablesInst[indice]->indice){
            printf("\e[1m");
            printf(" %d ",variablesInst[indice]->value);
            printf("\e[0m");
            ++indice;
        }
        else {
            printf("\e[30;40m");
            printf("   ");
            printf("\e[0m");
        }
        ++j;
    }
    printf("\n");
    printf("\n");
}

/**
 * @brief      The main function
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 *
 * @return     return value
 */
int main(int argc, char **argv) {
    int bflag = 0;
    int fflag = 0;
    int c;
    opterr = 0;
    clock_t beginning, end;
    Stat stats;
    stats.nb_test_constraints = 0;
    stats.nb_node = 0;

    if (argc != 3) {
        printf ("Usage: %s OPTION FILE\n", argv[0]);
        printf ("Solve Kakuro grid on the txt format.\n");
        printf("    -b,                      use backtrack method.\n");
        printf("    -f,                      use foward-checking method.\n");
        return 1;
    }

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
    printf("File: %s\n", argv[optind]);
    printf("Init CSP...\n");

    Size size = initVal(f);
    Variable **variables = calloc (size.width * size.length, sizeof(Variable));
    int number_of_empty_case = search_empty_case(f, variables);
    search_contraints(f, variables, number_of_empty_case, size);
    Variable **variablesInst = search_variable(variables, number_of_empty_case, size);
    free(variables);

    beginning = clock();

    if (fflag) {
        printf("Foward Checking...\n");
        fowardchecking(variablesInst, number_of_empty_case, &stats);
    } else if (bflag) {
        printf("Backtrack...\n");
        backtrack(variablesInst, number_of_empty_case, &stats);
    }

    end = clock();

    printf("Done.\n");
    print_result(variablesInst, size);
    printf("Time: %lf sec\n", (double) (end - beginning) / CLOCKS_PER_SEC);
    printf("Node: %d\n", stats.nb_node);
    printf("Constraint tests: %d\n", stats.nb_test_constraints);

    freedom(variablesInst, number_of_empty_case);
    fclose(f);
    return 0;
}

