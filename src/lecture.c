#include <stdio.h>
#include <stdlib.h>
typedef int POSITION; 

#define is_num(c)(('0' <= (c)) && ((c) <= '9'))
#define VERTICAL 1
#define HORIZONTAL 2
#define N 40 

typedef struct{
	int x;
	POSITION scope;
} Contrainte;

typedef struct {
	int x;
	int y;
	Contrainte tabCont[N]; 
} CaseVide;

int cptCaseVide = 0;
int cptContrainte = 0;

Contrainte tabContrain[N];
CaseVide tabCaseVide[N];

void ajoutCaseVide( int x , int y ){
	CaseVide nouvelleCase;
	nouvelleCase.x = x;
	nouvelleCase.y = y;
	tabCaseVide[cptCaseVide] = nouvelleCase;
	++cptCaseVide;
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
