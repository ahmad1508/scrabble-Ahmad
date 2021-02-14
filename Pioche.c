/* ce fichier comporte les fonctions de la pioche:
    -melange de la pioche
    -valeur des lettres du scrabble
*/

#include "Pioche.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void melangePioche(t_donnee *jeu)
{
    char tempo;
    int i, j ;

    strcpy(jeu->pioche,"AAAAAAAAABBCCDDDEEEEEEEEEEEEEEEFFGGHHIIIIIIIIJKLLLLLMMMNNNNNNOOOOOOPPQRRRRRRSSSSSSTTTTTTUUUUUUVVWXYZ??");
    // on copie la lettre de la pioche manuellement dans jeu->pioche
    srand(time(NULL));//on initialise le genrateur

    for(j=0;j<102;j++)
    {
        i=rand()%(102);/* on genere des nombres aleatoires  entre et 102*/

        tempo = jeu->pioche[i];
        jeu->pioche[i]=jeu->pioche[j];// on echange la lettre du rang j de la boucle avec la lettre de rang i qui est aleatoire
        jeu->pioche[j]=tempo;
    }
    // a la fin on a une pioche suffisament mélangée
}

int valeurLettre(char carac)/* cette fonction va etre utilisée pour compter
                            les valeurs des mot mit par l'utilisateur
                            elle rend la valeur de chaque caractere recu en parametre par valeur*/
{
    if (carac=='A')
        return 1;
    if (carac=='B')
        return 3;
    if (carac=='C')
        return 3;
    if (carac=='D')
        return 2;
    if (carac=='E')
        return 1;
    if (carac=='F')
        return 4;
    if (carac=='G')
        return 2;
    if (carac=='H')
        return 4;
    if (carac=='I')
        return 1;
    if (carac=='J')
        return 8;
    if (carac=='K')
        return 10;
    if (carac=='L')
        return 1;
    if (carac=='M')
        return 2;
    if (carac=='N')
        return 1;
    if (carac=='O')
        return 1;
    if (carac=='P')
        return 3;
    if (carac=='Q')
        return 8;
    if (carac=='R')
        return 1;
    if (carac=='S')
        return 1;
    if (carac=='T')
        return 1;
    if (carac=='U')
        return 1;
    if (carac=='V')
        return 4;
    if (carac=='W')
        return 10;
    if (carac=='X')
        return 10;
    if (carac=='Y')
        return 10;
    if (carac=='Z')
        return 10;
    if (carac=='?')
        return 0;
    return 0;
}
