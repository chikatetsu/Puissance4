#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //Pour l'ajout des couleurs

typedef struct {
    int row;
    int column;
} Board;

/** Change la couleur du texte */
void Color(int couleurDuTexte,int couleurDeFond) {
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

/** Affiche le tableau de jeu */
void affBoard(int **tab, Board board) {
    //ligne de début
    int b = 205;
    putchar(201); //putchar création des delimitation en ASCII
    for (int i = 0; i <13; ++i) {
        putchar(b);
        putchar(203);
    }
    putchar(b);
    putchar(187);
    printf("\n");

    //lignes avec les valeurs du tableau
    for(int i=board.row-1; i>=0; i--){
        putchar(204);
        if(tab[0][i]==0) {
            printf("   ");
        } else if(tab[0][i]==1) {
            Color(4,0); //couleur rouge
            printf(" X ");
            Color(15, 0); //couleur blanche
        } else if(tab[0][i]==2) {
            Color(14,0); //couleur jaune
            printf(" O ");
            Color(15, 0); //couleur blanche
        }
        for(int j=1; j<board.column; j++) {
            putchar(206);
            if(tab[j][i]==0) {
                printf("   ");
            } else if(tab[j][i]==1) {
                Color(4,0); //couleur rouge
                printf(" X ");
                Color(15, 0); //couleur blanche
            } else if(tab[j][i]==2) {
                Color(14,0); //couleur jaune
                printf(" O ");
                Color(15, 0); //couleur blanche
            }
        }
        putchar(185);
        printf("\n");
    }
    //dernière ligne
    putchar(200);
    for (int i = 0; i < 13 ; ++i) {
        putchar(b);
        putchar(202);
    }
    putchar(b);
    putchar(188);
    printf("\n");

    //numéro des colonnes
    for (int i = 1; i <= board.column ; ++i) {
        printf("  %d ",i);
    }
    printf("\n");
}

/** Vérifie si un joueur est en train de gagner */
int verifJoueur(int val, int *valJoueur, int *compteur) {
    if(val == 0) {
        *valJoueur = 0;
        *compteur = 0;
        return 0;
    }
    if(*compteur == 0) {
        *valJoueur = val;
        (*compteur)++;
    } else {
        if(*valJoueur == val) {
            (*compteur)++;
        }
    }
    return (*compteur) == 4;
}

/** Vérifie si le jeu a été gagné par l'un des joueurs */
int isWinned(int **tab, int sizeX, int sizeY) {
    int joueur = 0;
    int cmpt = 0;

    //vertical
    for(int i=0; i<sizeX-3; i++) {
        for(int j=0; j<sizeY; j++) {
            if(verifJoueur(tab[i][j], &joueur, &cmpt)) {
                return joueur;
            }
        }
        cmpt = 0;
    }

    //horizontal
    for(int j=0; j<sizeY; j++) {
        for(int i=0; i<sizeX-3; i++) {
            if(verifJoueur(tab[i][j], &joueur, &cmpt)) {
                return joueur;
            }
        }
        cmpt = 0;
    }

    //diagonale vers la droite
    for(int j=0; j<sizeY-3; j++) {
        for(int i=0; i<sizeX-3; i++) {
            if(verifJoueur(tab[i][j], &joueur, &cmpt)) {
                return joueur;
            }

            for(int k=0; k<4; k++) {
                if(verifJoueur(tab[i+k][j+k], &joueur, &cmpt)) {
                    return joueur;
                }
            }
        }
        cmpt = 0;
    }

    //diagonale vers la gauche
    for(int j=0; j<sizeY-3; j++) {
        for(int i=3; i<sizeX; i++) {
            if(verifJoueur(tab[i][j], &joueur, &cmpt)) {
                return joueur;
            }

            for(int k=0; k<4; k++) {
                if(verifJoueur(tab[i-k][j+k], &joueur, &cmpt)) {
                    return joueur;
                }
            }
        }
        cmpt = 0;
    }
    return 0;
}

int main() {
    Board board = {
            .row = 6,
            .column = 7,
    };

    int **tab = calloc(board.column,sizeof(int*));
    for(int i=0; i<board.column; i++) {
        tab[i] = calloc(board.row, sizeof(int));
    }

    affBoard(tab, board);

    short isRunning = 1;
    int input;
    int joueur = 0;
    int win;

    while(isRunning) {
        if(joueur) {
            printf("Au tour des ");
            Color(14, 0); //couleur jaune
            printf("jaunes");
            Color(15, 0); //couleur blanche
            printf("! Entrez une colonne : ");
        } else {
            printf("Au tour des ");
            Color(4, 0); //couleur rouge
            printf("rouges");
            Color(15, 0); //couleur blanche
            printf("! Entrez une colonne : ");
        }
        scanf("%d", &input);
        printf("\n");

        if(input < 1 || input > board.column) {
            printf("Cette colonne n'existe pas\n");
            continue;
        }

        int i=0;
        while(tab[input-1][i] != 0 && i<board.column) {
            i++;
        }
        if(i<board.column) {
            tab[input-1][i] = joueur+1;
        }
        else {
            printf("Cette colonne est deja rempli\n");
            continue;
        }

        affBoard(tab, board);

        win = isWinned(tab, board.column, board.row);
        if(win) {
            if(win == 1) {
                Color(4, 0); //couleur rouge
                printf("Les rouges ont gagnes!");
            } else if(win == 2) {
                Color(14, 0); //couleur jaune
                printf("Les jaunes ont gagnes!");
            }
            isRunning = 0;
        }
        joueur = !joueur;
    }
    while(1);
    return 0;
}
