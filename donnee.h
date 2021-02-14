#ifndef DONNEE_H_INCLUDED
#define DONNEE_H_INCLUDED

#include "Chevalet.h"
#include "Plateau.h"


void affichageScore(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs] );
void scoreMot_JOUEUR(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu);
void placerMot( t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu );
int espaceHorizentale(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu,int motPossible);
int espaceVerticale(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu,int motPossible);
void nomJoueur(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs]);
t_joueurs ** tableauStruct(t_placer *Mot);

#endif // DONNEE_H_INCLUDED
