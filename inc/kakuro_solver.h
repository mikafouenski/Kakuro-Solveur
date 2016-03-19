typedef struct Constraints_Sum Constraints_Sum;
typedef struct Constraints_Diff Constraints_Diff;
typedef struct Variable Variable;

struct Variable{
    int indice; //only for debug
    int value;
    Constraints_Sum *sum_H;
    Constraints_Sum *sum_V;
    Constraints_Diff *diff;
    //int domain[9] = {1,2,3,4,5,6,7,8,9};
    int indice_domaine;
};


struct Constraints_Sum{
    int value;
    Variable **vars;
};

struct Constraints_Diff{
    Variable **vars;
};

Variable **variables;

void solve_kakuro (FILE *file);
