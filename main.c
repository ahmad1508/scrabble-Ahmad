#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    t_donnee jeu;
    t_placer Mot;
    t_joueurs *joueur = NULL;// on declare 3 structures et un tableau de struct

    menu(&Mot,&joueur,&jeu);
    return 0;
}


