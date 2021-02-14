#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include "jeu.h"
#include "Pioche.h"
void gotoligcol( int lig, int col );
void Color(int couleurDuTexte,int couleurDeFond);
void remplissageplateau(t_donnee *jeu);
void afficherPlateau(t_donnee *jeu);

#endif // PLATEAU_H_INCLUDED
