/*Dans ce fichier on a mis les fonctions gotoligcol et color et les fonctions de sauvegarde et chargement :
    -chargement et sauvgarder struct Mot pour la structure Mot.
    -chargement et sauvgarder struct joueur pour la structure joueur.
    -chargement et sauvgarder struct jeu pour la structure jeu.

La fonction de sauvegarde fonctionne bien, on garder les fichier .txt dans le dossier mais les fonctions
de chargement des struct joueur et jeu ne marchent pas et on les a mis en commentaire pour que vous puissiez
les voir , on a aussi essayé d'utiliser des tableaux de structure à la place de pointeurs sur les tableaux
de structure mais ca a causé des problemes dans l'execution qu'on a pas pu resoudre, on a aussi essayé les
fichiers binaires mais le tableau de structure ne charge pas.
    */
#include "jeu.h"
#include "Pioche.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void gotoligcol( int lig, int col )
{
// ressources
COORD mycoord;

mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
/*void chargement_structMot(t_placer *Mot)
{
    FILE *fic = NULL;

    if((fic=fopen("save_Struct_Mot.TXT","r"))==NULL)
    {
        printf("****echec ouverture****");
        exit(EXIT_FAILURE);
    }

    fscanf(fic,"%d %d %d",&Mot->nbr_Joueurs,&Mot->tourJ,&Mot->nbrMot);
    printf("%d %d %d",Mot->nbr_Joueurs,Mot->tourJ,Mot->nbrMot);

    fclose(fic);

}

void sauvegarder_StructMot(t_placer *Mot)
{
    FILE *fichier;

    if((fichier=fopen("save_Struct_Mot.TXT","w"))==NULL)
    {
        printf("echec ouverture");
        exit(EXIT_FAILURE);
    }

    fprintf(fichier,"%d %d %d",Mot->nbr_Joueurs,Mot->tourJ,Mot->nbrMot);
    fclose(fichier);
}


void sauvegarder_StructJoueur(t_placer * Mot,t_joueurs joueur[Mot->nbr_Joueurs])
{
    FILE *fichier;
    int i;

    if((fichier=fopen("save_Struct_Joueur.TXT","w"))==NULL)
    {
        printf("echec ouverture");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        fprintf(fichier,"%s %s %d",joueur[i].nom,joueur[i].chevalet,joueur[i].score);
    }
    fclose(fichier);
}

void chargement_structJoueur(t_placer *Mot,t_joueurs joueur[Mot->nbr_Joueurs])
{
    FILE *fic = NULL;
    int i;

    if((fic=fopen("save_Struct_Joueur.TXT","r"))==NULL)
    {
        printf("****echec ouverture****");
        exit(EXIT_FAILURE);
    }

    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        fscanf(fic,"%s %s %d",joueur[i].nom,joueur[i].chevalet,&joueur[i].score);
    }
    fclose(fic);

}*/






/*void charger_StructJeu(t_donnee *jeu)
{
    FILE *fichier = NULL;
    int i,j,k;
    for(i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            for(k=0;k<2;k++)
            {
                fscanf(fichier,"%d;",&jeu->plateau[i][j][k]);
            }
        }
    }
    fscanf(fichier,"%s",jeu->pioche);
    fclose(fichier);

}

void savePioche(t_donnee *jeu)
{
    FILE *fichier;
    if((fichier = fopen("save.TXT","a"))==NULL)
    {
        printf("---Echec ouverture---");
        exit(-1);
    }
    fprintf(fichier,"%s",jeu->pioche);

    fclose(fichier);
}*/
