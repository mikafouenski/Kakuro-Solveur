#include <stdio.h>
#include <stdlib.h>

#define N 40 

typedef int CONTRAINT_TYPE 
#define NON_EGAL 1
#define SOMME 2
 
typedef int POSITION; 
#define VERTICAL 1
#define HORIZONTAL 2

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))

Contrainte *tabContrainX = (Contrainte*)calloc(N, sizeof List);
Contrainte *tabContrainY = (Contrainte*)calloc(N, sizeof List);;
CaseVide *tabCaseVide = (CaseVide*)calloc(N, sizeof CaseVide);;


typedef struct Chainon List;
struct Chainon {
	Contrainte constrain;
	struct Chainon *suiv;
};
 
typedef struct{
	int x;
	POSITION scope;
	CONTRAINT_TYPE type;
} Contrainte;

typedef struct {
	int x;
	int y;
	int val;
} CaseVide;

int cptCaseVide = 0;

void freeTab(){
	free (tabContrainX);
	free (tabContrainY);
	free (tabCaseVide);
}

void ajouttab(Contrainte *tab,Contrainte contraint){
	List head = tab[contraint.x];
	while(head.next != NULL){
		head = head.next;
	}
	List newContraint;
	newContraint.contraint = contraint;
	newContraint.next = NULL;
	head.next = newContraint;  
}

void ajoutContraint(int x,CONTRAINT_TYPE c,POSITION p){
	Contrainte *tab; 
	switch case (p){
		case HORIZONTAL:
			tab = tabContrainX;
		break;
		case VERTICAL:
			tab = tabContrainY;
		break;
		default
		fprintf(stderr, "Erreur contraint type inconue\n", ); 
	}
	Contrainte nouvelleContraint;
	nouvelleContraint.x = x;
	nouvelleContraint.scope = p;
	nouvelleContraint.type = c;
	ajouttab(tab,nouvelleContraint);
}

void ajoutCaseVide( int x , int y ){
	CaseVide nouvelleCase;
	nouvelleCase.x = x;
	nouvelleCase.y = y;
	tabCaseVide[cptCaseVide] = nouvelleCase;
	++cptCaseVide;
	Contrainte nouvelleContraint;
	nouvelleContraint.x = x;
	nouvelleContraint.scope = HORIZONTAL;
	nouvelleContraint.type  = NON_EGAL;
	tabContrainX =;
}

void ajoutCaseContrainte(number1,number2){
	Contrainte nouvelleContraint;
	if(number1 != 0){
		nouvelleContraint.x = number1;
		nouvelleContraint.scope= VERTICAL;
		tabContrain[cptContrainte] = nouvelleContraint;
		++cptContrainte;
	}

}
void lireFichier(FILE *fic) {
	int number1 = 0;
	int number2 = 0;
	int x = 0;
	int y = 0;
	char caracLu = fgetc(fic);
	while (caracLu != EOF){
		switch (caracLu){
			case '\n':
				x = 0;
				++y;
				caracLu = fgetc(fic);
				++x;
				break;
			case '.':
				ajoutCaseVide(x,y);
				caracLu = fgetc(fic);
				++x;
				break;
			case '/':
				caracLu = fgetc(fic);
				++x;
				while(is_num(caracLu)){
					caracLu = fgetc(fic);
				}
				ajoutCaseContrainte(number1,number2);
				number1 = 0;
				number2 = 0;
				break;
			default:
				while(is_num(caracLu)){
					if(number1 == 0){
						number1 = caracLu;
					}
					else 
						number1 = number1 *10 + caracLu;
					caracLu = fgetc(fic);
				}
				break;
		}
	}
}

void analyseFichier(char* pathName){
	FILE *fic = fopen(pathName,"r");
	printf("%s\n","ta");
	if(fic == NULL){
		fprintf(stderr, "%s\n","ta Geule Micka" );
		exit(1);
	}
	lireFichier(fic);

}


int main(int argc, char const *argv[])
{
	
	analyseFichier("enonce.txt");
	return 0;
}
