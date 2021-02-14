#ifndef LANCER_H_INCLUDED
#define LANCER_H_INCLUDED

#include "donnee.h"
#include "dictionnaire.h"
#include "menu.h"

void lancerNouvellePertie(t_placer * Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu);
void jouer(t_placer * Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu);
void ligColDirection(t_placer *Mot);
void checkContestation(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu,int contest, int *count);
void saisirMot(t_placer *Mot);

#endif // LANCER_H_INCLUDED
