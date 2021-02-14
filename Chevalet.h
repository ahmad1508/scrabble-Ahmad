#ifndef CHEVALET_H_INCLUDED
#define CHEVALET_H_INCLUDED


#include "Pioche.h"

void initialiser_struct( t_placer *Mot , t_joueurs *joueur[Mot->nbr_Joueurs], t_donnee * jeu);
void affichageChevalet(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs]);
void rempliChevalet(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs], t_donnee *jeu);
void vidageChevalet(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs]);
int lettre_plateau(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs], t_donnee *jeu);
int check_lettre_mot(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs], t_donnee *jeu);
void changerLettre(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu);
void resteChevalet(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],int *lettreChevalet);
void VoirFinPartie(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu);
void FinPartie(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs] , int *lettreChevalet , int chevalet);

#endif // CHEVALET_H_INCLUDED
