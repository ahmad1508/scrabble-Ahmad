#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "lancer.h"

int menu(t_placer *Mot,t_joueurs **joueurs,t_donnee *jeu);
int demandeMenu(t_placer *Mot,t_joueurs * joueurs[Mot->nbr_Joueurs],t_donnee *jeu);

#endif // MENU_H_INCLUDED
