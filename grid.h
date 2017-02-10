#ifndef GRILLE_H_INCLUDED
#define GRILLE_H_INCLUDED


					///////////////
					// Type defs //
					///////////////


typedef struct cellsTab_ {		//Structure correspondant à la grille de sudoku.
    
    int cell[9][9];

} cellsTab;




					///////////////
					// Fonctions //
					///////////////



void gridCreation(cellsTab *grilles);					//Fonction de création des grilles.

int isValid(cellsTab *tc, int ligne, int colonne);		//Fonction de test de validité de la valeur.

// int isAbsent(cellsTab *tc, int ligne, int colonne, int V);	//Fonction de test de présence sur X Y et zone.


#endif // GRILLE_H_INCLUDED
