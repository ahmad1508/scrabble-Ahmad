#include "menu.h"

#include <stdio.h>
#include <stdlib.h>




int menu(t_placer *Mot,t_joueurs **joueur,t_donnee *jeu)
{
    int choix,x=9;
    gotoligcol(1,82);
    printf("****Menu****\n\n");
    gotoligcol(2,82);
    printf("Que voulez-vous faire?\n");//les choix dans le jeu
    gotoligcol(3,82);
    printf("1-Lancer une nouvelle partie.\n");
    gotoligcol(4,82);
    printf("2-Reprendre une partie sauvegardee.\n");
    gotoligcol(5,82);
    printf("3-Afficher l'aide.\n");
    gotoligcol(6,82);
    printf("4-Afficher le score des joueurs.\n");
    gotoligcol(7,82);
    printf("5-Quitter le jeu\n");
    gotoligcol(8,82);
    printf("Choix:");
    do//blindage du choix
    {
        fflush(stdin);
        scanf("%d",&choix);
        if (choix<=0||choix>5)
        {
            gotoligcol(x++,82);
            printf("Ce choix n'est pas possible. Refaites un choix\n");
            gotoligcol(x++,82);
            printf("Choix:");
        }
    }
    while(choix<=0||choix>5);
    printf("\n");

    switch(choix)
    {
    case 1:
        system("cls");
        joueur = tableauStruct(Mot);//on alloue dynamiquement de la place a joueur
        lancerNouvellePertie(Mot,joueur,jeu);///appel de lancer une nouvelle partie
        break;
    case 2://ne fonctionne pas aller dans jeu.c et lire l'entete
        afficherPlateau(jeu);
        jouer(Mot,joueur,jeu);///appel fonction qui continue une partie
        break;
    case 3:
        afficherPlateau(jeu);
        Aide();//on affiche le plateau puis l'aide
        printf("presser entrer pour continuer");
        fflush(stdin);
        getchar();
        break;
    case 4:
        afficherPlateau(jeu);
        affichageScore(Mot,joueur);//afichage du score de tous les joueurs

        break;
    case 5:
        exit(0);//pour sortir du jeu
        break;
    }
    return choix;

}

int demandeMenu(t_placer *Mot,t_joueurs * joueur[Mot->nbr_Joueurs],t_donnee *jeu)//fonction appeler pour demander si quelqu'un veut le menu
{
    int affiche,choix,x=1;

    if(Mot->tourJ==(Mot->nbr_Joueurs-1))/*si le programme rentre dans la fonction affiche et revient au menu
                                        et qu'on veut continuer la partie, on passe au tour du joueur suivant*/
    {
        Mot->tourJ=0;

    }
    else{
        Mot->tourJ++;

    }
    gotoligcol(0,82);
    printf(" (1) pour aide? ou Score? et  (2) continuez?:");
    do//blindage du choix
    {
        fflush(stdin);
        scanf("%d",&affiche);
        if(affiche<1 || affiche>2){
            gotoligcol(x++,82);
            printf("choix invalide ,refaites le choix:");}
    }
    while(affiche<1 || affiche>2);
    if (affiche==1)
    {
        choix=menu(Mot,joueur,jeu);//affichage du menu

    }
    return choix;
}
