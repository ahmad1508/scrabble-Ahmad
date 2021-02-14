#ifndef DICTIONNAIRE_H_INCLUDED
#define DICTIONNAIRE_H_INCLUDED


#include "jeu.h"

int dictio(t_placer *Mot);
int contestationMot(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs]);
void Aide();
#endif // DICTIONNAIRE_H_INCLUDED
