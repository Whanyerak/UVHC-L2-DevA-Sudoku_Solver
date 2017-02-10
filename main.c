#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include <time.h>
#include <string.h>


void readOptions(int nbOptions, char** options, int* optionsTab) {		//Procédure de lecture des options.
	
	int cpt;

	for(cpt = 0; cpt < nbOptions; cpt++) {

		if(strcmp(options[cpt], "-print") == 0)
			optionsTab[0] = 1;

		if(strcmp(options[cpt], "-timeAlert") == 0)
			optionsTab[1] = 1;
		
		if(strcmp(options[cpt], "-verbose") == 0)
			optionsTab[2] = 1;

	}	
}


int countGrids() {		//On compte le nombre de grilles données dans le fichier d'entrée.

	FILE* file = NULL;
	int totGrid = 0;
	int value;

	file = fopen("grilles.txt", "r");

	while(fscanf(file, "%81d", &value) == 1)
		totGrid ++;

	fclose(file);

	return totGrid;
}


void writeSolutions(cellsTab grid, int numGrid) {		//Procédure d'écriture des résultats dans un fichier.
    
    int X, Y;
    FILE* file = NULL;

    file = fopen("solution_MORIN_Valentin.txt","a");	//Création du fichier de sortie.

    fseek(file, numGrid*82, SEEK_CUR);					//On parcourt 82 caractères par grilles car 81 chiffres + \n à la fin.

    if(file != NULL) {

	    for(X = 0; X < 9; ++X) {

	        for(Y = 0; Y < 9; ++Y)
	           fprintf(file, "%d", grid.cell[X][Y]);
	        
    	}

    	fprintf(file, "\n");

	}

}


void printGrid(cellsTab grid) {		//Procédure d'affichage des grilles.

    int X, Y;
    
    printf(" -------------------------------------");
    printf("\n");

    for(X = 0; X < 9; ++X) {

        for(Y = 0; Y < 9; ++Y) {			//On dessine une grille propre.

        	printf(" | ");
            printf("%d", grid.cell[X][Y]);
        
        }

        printf(" | ");
        printf("\n");

        printf(" -------------------------------------");
        printf("\n");
    }

    printf("\n");

}





		/////////////////////////
		// Programme principal //
		/////////////////////////



int main(int argc, char *argv[]) {

    int numGrid;
    int totGrid;
    double timeGiven = 3600.0;


    int optionsTab[3] = {0, 0, 0};

    clock_t start, end;							//Variable pour la mesure du temps de résolution d'une grille.
    clock_t begin_time, end_time;				//Variables pour le timeAlert initialisées plus loin.

    readOptions(argc, argv, optionsTab);								//On lit les options données.

    totGrid = countGrids();												//On compte le nombre de grilles à traiter.

    cellsTab *grids = (cellsTab *)malloc(totGrid * sizeof(cellsTab));	//On range les sudoku dans une grille.

    gridCreation(grids);												//On lit les grids et les place dans un tableau de grids.


    remove("solution_MORIN_Valentin.txt");								//On supprime l'ancien fichier de sauvegarde s'il existe.



	begin_time = clock();		//
	end_time = clock(); 		//Variables pour le timeAlert initialisées.
	int cpt_grids = 0;			//

	if (optionsTab[1] == 1) {
		printf("Quel est le temps imparti ?\n");
		timeGiven = scanf("%lf", &timeGiven);

		printf("bite %lf\n", timeGiven);
	}


	for (numGrid = 0; numGrid < totGrid; numGrid++) {

	    cellsTab grid = grids[numGrid];

	    if (optionsTab[0] == 1 && numGrid == cpt_grids) {		//Si option print alors on affiche la grille base.

    		printf("\n\nGrille numero %d.\n\n\n", numGrid + 1);		
			printf("Grille originale : \n\n");

			printGrid(grid);

		}

		start = clock();


		if (isValid(&grid, 0, 0)) {
			if (optionsTab[1] == 0 || (optionsTab[1] == 1 && (end_time - begin_time)/(double)CLOCKS_PER_SEC < timeGiven)) {

        		end = clock();
        		end_time = clock();
        		if ((end_time - begin_time)/(double)CLOCKS_PER_SEC < timeGiven) {
        			cpt_grids++;

	        		if (optionsTab[0] == 1) {					//Si option print alors on affiche la grille résolue.

		      		  	printf("Grille solution :\n\n");

			       		printGrid(grid);

			       	}

	    		}


	        writeSolutions(grid, numGrid);					     //On écrit la solution dans le fichier.

	        printf("\nTemps de resolution : %fs.\n\n\n", (end-start) / (double)CLOCKS_PER_SEC);
	        printf("--------------------------------------\n");
	        printf("--------------------------------------\n");
	        printf("--------------------------------------\n\n");


		    }   

		} else printf("Le sudoku n'a pas de solution \n\n\n\n");	//Si après tests aucune solution bonne alors sudoku insolvable.

	    	
	}
	
	if(optionsTab[1] ==1)
		printf("\nNombre de grilles resolues dans le temps imparti : %d.\n\n\n", cpt_grids);
		
	if(optionsTab[2] ==1)
		printf("Verbose n'est pas implémenté.\n\n");
	

    return 0;

}
