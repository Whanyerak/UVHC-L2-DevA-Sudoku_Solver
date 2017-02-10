#include <stdio.h>
#include <stdlib.h>
#include "grid.h"


void gridCreation(cellsTab *grids) {     //procédure permettant de lire le fichier et de créer les grilles.

    int gridNum = 0;
    char currentChar = '\0';
    int X = 0;
    int Y = 0;
    FILE* file = NULL;

    file = fopen("grilles.txt", "r");

    if (file != NULL) {

        while (currentChar != EOF) {

            currentChar = fgetc(file); 

            if (currentChar == '\n')
                gridNum++;

            else {

                if (X == 9)
                    X = 0;

                if (Y == 9)
                    Y = 0;

                int valeur = currentChar - 48;   //on soustrait 48 au caractèreActuel afin de transformer code ASCII.

                if (valeur >= 0) {

	                grids[gridNum].cell[X][Y] = valeur;
	                Y++;

	                if (Y == 9)
	                    X++;

                }
            }

        }

        fclose(file);

    }

}


int isPossible(cellsTab *sudoku, int X, int Y, int V) {     //on cherche la valeur V dans les X Y et zones de la case
                                                                        //si on peut mettre la valeur alors 1 sinon 0
    int blocX = (X/3) * 3;
    int blocY = (Y/3) * 3;
    int c;

    for(c = 0; c < 9; ++c) {

        if (sudoku->cell[X][c] == V)
            return 0;
        

        if (sudoku->cell[c][Y] == V)
            return 0;
            

        if (sudoku->cell[blocX + (c%3)][blocY + (c/3)] == V)
            return 0;
        

    }
 
    return 1;   //la valeur n'étant pas présente dans le X Y ou la zone de la case on afffecte 1 car possible
}



int isValid(cellsTab *sudoku, int X, int Y) {
    int V;

    if (X < 9 && Y < 9) {

        if (sudoku->cell[X][Y] != 0) {               //on test ici la validité des valeurs comprises dans les cases

            if (Y < 8)
                return isValid(sudoku, X, Y+1);  

            else if (X < 8) 
                return isValid(sudoku, X+1, 0);
            
            else return 1;

        } else {                                    //tout n'est pas ok donc on cherche les valeurs

            for (V = 1; V <= 9; ++V) {

                if (isPossible(sudoku, X, Y, V)) {

                    sudoku->cell[X][Y] = V;

                    //Si Y est inférieur à 8 (on n'a pas atteint la fin de la X)                    
                    if (Y < 8) {

                        if (isValid(sudoku, X, Y+1))
                            return 1;

                        else sudoku->cell[X][Y] = 0;
                    } else if(X < 8) {

                        if(isValid(sudoku, X+1, 0))
                            return 1;
                       
                        else sudoku->cell[X][Y] = 0;    //si rien n'est bon on réinitialise la case et on passe à la V suivante
                    }
                    
                    else return 1;  //retourne 1 si le choix est bon, le tableau en mémoire est modifié avec toutes les bonnes valeurs et la fonction s'arrête.
                }

            }

        }

        return 0;
    }

    else return 1;
}
