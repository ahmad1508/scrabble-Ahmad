/*ce fichier contient les foncions d'execution du jeu:
    -lancer une nouvelle partie qui remet tout a 0
    -jouer qui va faire l'execution des programmes et de la totalite du jeu
    -saisir mot
    -ligcoldirection qui demande la ligne la colonne et la direction du mot à placer
*/
/**
Dans notre jeu on aurait pu faire par un simple appel que tout mot placé doit etre verifié dans le dictionnaire mais
comme dans le vrai jeu on peut placer n'importe quel mot sauf si il a ete contesté et qu'il n'est pas dans le dictionnaire
dans la fonction contestation mot dans le fichier dictionnaire le joueur ayant contesté le mot perd 10 points si le mot est
dans le dictionnaire.
**/

#include "lancer.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

int i,j,contest,motPossible,motValide;//variable globale



void lancerNouvellePertie(t_placer * Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu)
{
    contest=0;
    motPossible=0;
    motValide=0;


    initialiser_struct(Mot,joueur,jeu);// on initialise les structures


    remplissageplateau(jeu);// on remplie le plateau
    system("cls");
    afficherPlateau(jeu);//on affiche le plateau
    //puts(jeu->pioche);
    rempliChevalet( Mot,joueur,jeu );// on remplit les chevalets de tout les joueurs
    gotoligcol(0,83);
    printf("Aggrandisser l'ecran");
    gotoligcol(1,83);
    printf("avant de continuer");
    nomJoueur(Mot,joueur);//on demande la saisie des noms
    jouer(Mot,joueur,jeu);//on lance la partie
}

void jouer(t_placer * Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu)
{
    int action,count=0;

    while(Mot->tourJ<Mot->nbr_Joueurs) //boucle infinie d'execution pour sortir on fait un exit dans le menu
    {

        gotoligcol(8,82);
        if (Mot->tourJ==0)
            printf("Tour du joueur 1:\n");
        else if (Mot->tourJ==1)
            printf("Tour du joueur 2:\n");
        else if (Mot->tourJ==2)
            printf("Tour du joueur 3:\n");
        else if (Mot->tourJ==3)
            printf("Tour du joueur 4:\n");

        affichageChevalet(Mot,joueur);

        gotoligcol(10,82);
        printf("Que voulez vous faire?:\n");//les differentes actions possibles
        gotoligcol(11,82);
        printf("  1-Placer un mot\n");
        gotoligcol(12,82);
        printf("  2-Changer une lettre\n");
        gotoligcol(13,82);
        printf("  3-Passer votre tour\n");
        gotoligcol(14,82);
        printf("choix:");
        do
        {
            fflush(stdin);
            scanf("%d",&action);
            if(action<1 || action>3)
            {
                printf("Choix impossible. Refaites un choix:");
            }
        }
        while(action<1 || action>3);

        switch(action)
        {
        case 1:
            ligColDirection(Mot);//on demande la saisie de ligne colonne direction

            if((Mot->ligne<0 || Mot->ligne>14)||(Mot->col<0 || Mot->col>14))/*si elle etait impossible on fait continue
                                                                            qui va retourner au debut de la boucle et
                                                                            reexecuter les instructions*/
            {
                system("cls");
                afficherPlateau(jeu);
                affichageChevalet(Mot,joueur);
                gotoligcol(7,82);
                printf("Ligne ou colonne invalide\n");
                continue;
            }

            if(Mot->direction == 'H' || Mot->direction == 'h')// si la direction demandée est horizontale
            {
                saisirMot(Mot); //on demande la saisie des mots

                motPossible = check_lettre_mot(Mot,joueur,jeu); /**fonction qui verifie si les lettres sont presentes dans le chevalet
                et retourne 1 si c'est bon sinon retourne 0 **/
                motValide = espaceHorizentale(Mot,joueur,jeu,motPossible);//prend la valeur retournée par espace horizontale
                /**fonction qui va voir si le mot peut etre mis horizontalement**/

                /**diction = dictio(mot_a_plcer); c'est l'appel de la fonction dictionnaire si on voulait verifier chaque mot à placer
                                                dans le dictionnaire il faudra donc ajouter dans le if ( && diction ==1)et enlever
                                                la partie contestation et il faut aussi mettre dans la partie verticale*/

                if ((motValide==1)&&(motPossible==1))//si on a l'espace et les lettres on peut placer
                {
                    contest = contestationMot(Mot,joueur);//on demande si les joueurs veulent contester
                    ///possibiliter de contestation de mot et verife dans un fichier dictionnaire
                    if(contest==1)// si il ne veulent pas ou qu'il veulent et le mot est dans le dictionnaire
                    {
                        scoreMot_JOUEUR(Mot,joueur,jeu);
                        gotoligcol(35,82);//on calcule le score du mot
                        printf("presser entrer pour continuer:");
                        fflush(stdin);
                        getchar();
                        placerMot(Mot,joueur,jeu);// on place le mot
                        system("cls");//pour ne pas continuer à aller en bas de l'ecran d'execution on efface ce qui est en haut a chaque fois
                        afficherPlateau(jeu);//on affiche le plateau
                        VoirFinPartie(Mot,joueur,jeu);// on verifie si on est arrivé a la fin de la partie
                        demandeMenu(Mot,joueur,jeu);// on demande a l'utilisateur  si il veut aller au menu
                        //si le joueur ne veux pas entrer dans le menu le jeu continue
                    }
                    else
                    {
                        gotoligcol(30,82);
                        printf("presser entrer pour continuer:");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        afficherPlateau(jeu);
                        count++;// si le mot est contesté et qu'il n'est pas dans le dictionnaire on incremente un compteur

                    }
                }
                else//si on n'a pas la place pour placer le mot et on a pas les lettres
                {
                    count++;//on incremente le compteur
                    if(count==3)//si le joueurs a saisie trois mots incorrectes il perd son tour
                    {
                        count=0;
                        system("cls");
                        afficherPlateau(jeu);
                        affichageChevalet(Mot,joueur);
                        gotoligcol(1,82);
                        printf("vous avez perdu votre chance\n");
                        if(Mot->tourJ==(Mot->nbr_Joueurs-1))// on passe au tour du suivant
                        {
                            Mot->tourJ=0;
                        }
                        else
                            Mot->tourJ++;

                        jouer(Mot,joueur,jeu);// on fait un appel recursif de jouer pour continuer
                    }
                    else//si le joueur n'a pas encore fait 3 fois on revient au debut de la boucle
                    {
                        system("cls");
                        afficherPlateau(jeu);
                        gotoligcol(5,82);
                        printf("mot invalide\n");
                        affichageChevalet(Mot,joueur);
                        continue;

                    }
                }
            }
            else// dans la deuxieme partie du programme on fait la meme chose que en haut mais pour les placements verticaux
            {
                if(Mot->direction=='V' || Mot->direction=='v')
                {

                    saisirMot(Mot);

                    motPossible = check_lettre_mot(Mot,joueur,jeu);

                    motValide = espaceVerticale( Mot,joueur,jeu,motPossible);/**fonction qui va voir si le mot peut etre mis horizontalement**/

                    if((motValide==1) && (motPossible==1))
                    {
                        contest = contestationMot(Mot,joueur);
                        if(contest==1)
                        {
                            scoreMot_JOUEUR(Mot,joueur,jeu);
                            gotoligcol(35,82);
                            printf("presser entrer pour continuer:");
                            fflush(stdin);
                            getchar();
                            placerMot(Mot,joueur,jeu);
                            system("cls");
                            afficherPlateau(jeu);
                            puts(jeu->pioche);
                            VoirFinPartie(Mot,joueur,jeu);
                            demandeMenu(Mot,joueur,jeu);

                        }
                        else
                        {
                            gotoligcol(30,82);
                            printf("presser entrer pour continuer:");
                            fflush(stdin);
                            getchar();
                            system("cls");
                            afficherPlateau(jeu);
                            count++;

                        }
                    }
                    else
                    {
                        count++;
                        if(count==3)
                        {
                            count=0;
                            system("cls");
                            afficherPlateau(jeu);
                            affichageChevalet(Mot,joueur);
                            gotoligcol(1,82);
                            printf("vous avez perdu votre chance\n");
                            if(Mot->tourJ==(Mot->nbr_Joueurs-1))
                            {
                                Mot->tourJ=0;
                            }
                            else
                                Mot->tourJ++;

                            jouer(Mot,joueur,jeu);
                        }
                        else
                        {
                            system("cls");
                            afficherPlateau(jeu);
                            gotoligcol(5,82);
                            printf("mot invalide\n");
                            affichageChevalet(Mot,joueur);

                            continue;
                        }
                    }
                }
            }
            break;


        case 2:
            changerLettre(Mot,joueur,jeu);
            system("cls");
            afficherPlateau(jeu);
            jouer(Mot,joueur,jeu);
            break;
        default:
            system("cls");
            afficherPlateau(jeu);
            if (Mot->tourJ==(Mot->nbr_Joueurs-1))
            {
                Mot->tourJ=0;
            }
            else
            {
                Mot->tourJ++;
            }
            break;
        }
    }
}

void ligColDirection(t_placer *Mot)
{
    gotoligcol(16,82);
    Color(4,0);
    printf("Entrer la ligne et la colone ou vous voulez commencer le mot(premier mot au milieu):\n");
    Color(15,0);
    gotoligcol(18,82);
    printf("Ligne:");
    scanf("%d",&(Mot->ligne));//on demande la saisie de la ligne
    gotoligcol(20,82);
    Mot->ligne=Mot->ligne-1;//on decremente de 1 car 15 ligne de 1 a 15 c'est 15 ligne de 0 a 14 en C

    printf("Colonne(Lettre):");
    fflush(stdin);
    scanf("%c",&Mot->colonne);//on demande la colonne
    if(Mot->colonne>97 && Mot->colonne<122)//si elle est inserée en minuscule en la transforme en majuscule
    {
        Mot->colonne=Mot->colonne-'a'+'A';
    }
    Mot->col=(int)(Mot->colonne)-(int)'A';// on rend la colonne en entier à la place de char sur la dimension du tableau
    fflush(stdin);
    gotoligcol(22,82);
    printf("Horizontale ou verticale(H ou V):");
    scanf("%c",&(Mot->direction));//on demande la direction
}

void saisirMot(t_placer *Mot)
{
    gotoligcol(24,82);
    printf("Entrer un mot:");
    fflush(stdin);
    gets(Mot->mot);//saisie du mot

    for(i=0; i<strlen(Mot->mot); i++)
    {
        if(Mot->mot[i]>=97 && Mot->mot[i]<=122)//on transforme les lettres minuscules en majuscules
        {
            Mot->mot[i]=Mot->mot[i]-'a'+'A';
        }
    }
}
