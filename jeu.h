#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

#define NBLIGNE 15
#define NBCOLONNE 15

/*la structure donnee comptient le plateau et la pioche qu'on n'utilise pas dans tout les programmes*/
typedef struct donnee
{
    char plateau[NBLIGNE][NBCOLONNE][3];
    char pioche[102];
} t_donnee;

/*la structure placer contient les variable qui peuvent servir a placer un mot et savoir
  le tour et nombre des joueurs*/
typedef struct placer
{
    char mot[15];
    char colonne,direction;
    int nbr_Joueurs;
    int col,ligne;
    int tourJ;
    int nbrMot;
    int *lettrePlateau;
} t_placer;

/*la structure joueur comporte les information de jeux de chaque joueur*/
typedef struct joueur
{
    char nom[30];
    char chevalet[8];
    int score;
} t_joueurs;

void gotoligcol( int lig, int col );
void Color(int couleurDuTexte,int couleurDeFond);
/*void chargement_structMot(t_placer *Mot);
void sauvegarder_StructMot(t_placer *Mot);
void sauvegarder_StructJoueur(t_placer * Mot,t_joueurs *joueur[Mot->nbr_Joueurs]);
void chargement_structJoueur(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs]);
void chargement_structJoueur(t_placer *Mot,t_joueurs joueur[Mot->nbr_Joueurs]);
void charger_StructJeu(t_donnee *jeu);
void savePioche(t_donnee *jeu);*/

#endif // JEU_H_INCLUDED
