/*ce fichier contient les fonctions qui donnent et affichent des donnees au jeu
    -affichagescore:pour afficher le score des joueur quand il le demande.
    -score du mot des joueurs : calcule le score d'un mot et les prime des case et l'ajoute au score du joueur
    -placer mot :qui va placer des mot si ils sont valider
    -espace horizentale : va voir si le mot peut etre placé dans un emplacement donne
    -espace verticale : meme chose que espace horizentale mais verticalement.
    -nom joueur: qui demande au joueur de saisir leur nom
    -tableau struct qui va allouer de la place dynamiquement a un tableau de struct
*/


#include "donnee.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void affichageScore(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs] )//affiche le score des joueurs quand demandé
{
    int i ;
    printf("\n");
    for(i=0; i<Mot->nbr_Joueurs; i++)
    {
        printf("score joueur %s:%d\n",joueur[i]->nom,joueur[i]->score);
    }
}


void scoreMot_JOUEUR(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu)
{
    int i,scoreLettre=0,scoreMot=0,colon=0,lig = 0,cpt=0;
    char carac;

    for(i=0;i<strlen(Mot->mot);i++)
    {
        if(Mot->lettrePlateau[i]==0)/*va compter combien de lettre du chevalet on ete utilisées pour un mot en utilisant
                                    le tableau de la fonction lettre_plateau*/
        {
            cpt++;
        }
    }
    if(cpt==7)//si les 7 lettres du chevalet on ete placées c'est que le joueur a scrabblé et qu il gagne 50 pts
    {
        joueur[Mot->tourJ]->score=joueur[Mot->tourJ]->score+50;
        Color(4,0);
        gotoligcol(33,82);
        printf("****VOUS AVEZ SCRABBLE VOUS GAGNEZ 50 POINTS****\n");
        Color(15,0);
    }

    colon=Mot->col;
    lig=Mot->ligne;
    for(i=0; i<strlen(Mot->mot); i++)
    {
        carac = Mot->mot[i];
        scoreLettre = valeurLettre(carac);
        if (Mot->direction=='H' || Mot->direction=='h')//va chercher les primés des cases pour un mot horizental
        {
            if((jeu->plateau[Mot->ligne][colon][0])=='&')//lettre double
            {
                scoreLettre = scoreLettre*2;
            }
            if((jeu->plateau[Mot->ligne][colon][0])=='%')//lettre triple
            {
                scoreLettre = scoreLettre*3;
            }
            colon++;
        }

        if (Mot->direction=='V' || Mot->direction=='v')//va chercher les primes des case pour un mot vertical
        {
            if((jeu->plateau[lig][Mot->col][0])=='&')//mot double
            {
                scoreLettre = scoreLettre*2;
            }
            if((jeu->plateau[lig][Mot->col][0])=='%')//mot triple
            {
                scoreLettre = scoreLettre*3;
            }
            lig++;
        }
        scoreMot = scoreMot + scoreLettre;

    }
    colon=Mot->col;
    lig=Mot->ligne;
    for(i=0; i<strlen(Mot->mot); i++)
    {
        if (Mot->direction=='H' || Mot->direction=='h')//ensuite va cherche les primés des mots horizentaux
        {
            if((jeu->plateau[lig][colon][0])=='@')//mot double
            {
                scoreMot = scoreMot*2;
            }
            if((jeu->plateau[lig][colon][0])=='§')//mot triple
            {
                scoreMot = scoreMot*3;
            }
            colon++;
        }

        if (Mot->direction=='V' || Mot->direction=='v')//ensuite va chercher les primés des mots verticaux
        {
            if((jeu->plateau[lig][colon][0])=='@')//mot double
            {
                scoreMot = scoreMot*2;
            }
            if((jeu->plateau[lig][colon][0])=='§')//mot triple
            {
                scoreMot = scoreMot*3;
            }
            lig++;
        }
    }
    gotoligcol(34,82);
    printf("La score du votre mot est <%d> POINTS\n",scoreMot);
    joueur[Mot->tourJ]->score=joueur[Mot->tourJ]->score + scoreMot;// ajoute le score du mot au score du joueur
    //printf("Le score de votre mot est %d\n",scoreMot);
}

void placerMot( t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu )
{
    int i,longueur=0;

    if((Mot->direction)=='H' || (Mot->direction)=='h' )// placer le mot horizentalement
    {
        longueur = Mot->col + strlen(Mot->mot);/**si le mot commence a la colonne 7 on veut faire toujours un nbr de boucle
                                        egale a la longueur du mot par rapport au plateau**/
        for(i=Mot->col; i<longueur; i++)
        {
            jeu->plateau[Mot->ligne][i][1]=Mot->mot[i-Mot->col];
        }
    }
    if((Mot->direction)=='V' || (Mot->direction)=='v' )//place les mots verticalement
    {
        longueur = Mot->ligne + strlen(Mot->mot);
        for(i=Mot->ligne; i<longueur; i++)
        {
            jeu->plateau[i][Mot->col][1]=Mot->mot[i-Mot->ligne];
        }
    }
    vidageChevalet(Mot,joueur);//vide les lettres du chevalet
    rempliChevalet( Mot,joueur,jeu );// rempli le chevalet
}


int espaceHorizentale(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee *jeu,int motPossible)
{
    int i,longueur,cpt=0,croisementPossible=0,croisementImpossible=0;
    //char tempo[15],carac[1],caractempo;

    longueur = strlen(Mot->mot)+ Mot->col;

    if((Mot->col+strlen(Mot->mot)-1)>14)/*si le mot deborde on rend 0(ex: colonne 12 et mot 3 lettres donc ligne 12 13 14
                                        or 12+3=15 donc on fait -1 qui est la ligne de debut*/
    {
        system("cls");
        afficherPlateau(jeu);
        affichageChevalet(Mot,joueur);
        printf("Ne peut pas etre mit horizentalement\n");
        return 0;
    }
    if(Mot->nbrMot==0)//pour le premier mot
    {
        for(i=Mot->col; i<longueur; i++)
        {
            if(jeu->plateau[Mot->ligne][i][0]=='#')//on voit si il coincide avec le centre
            {
                cpt=1;//si oui le cpt vaut 1 sinon il reste a zero
            }
        }
    }
    if(Mot->nbrMot!=0)
    {
        for(i=Mot->col;i<longueur;i++)
        {
            if(jeu->plateau[Mot->ligne][i][1]!=0 && jeu->plateau[Mot->ligne][i][1]==Mot->mot[i-Mot->col])
            {
                croisementPossible++;
            }
            if(jeu->plateau[Mot->ligne][i][1]!=0 && jeu->plateau[Mot->ligne][i][1]!=Mot->mot[i-Mot->col])
            {
                croisementImpossible++;
            }
            if(croisementImpossible!=0)
            {
                printf("Le mot que vous avez mis n'a pas la meme lettre que le mot sur le plateau\n");
                return 0;
            }
        }
    }

    if(Mot->nbrMot==0 && cpt!=0)//si c'est le premier mot et qu'il est au centre
    {
        if(motPossible==1)
        {
            Mot->nbrMot++;//on incremente nbrMot pour le prochain tour
        }

        return 1;//on rend 1
    }
    else if(cpt==0 && Mot->nbrMot!=0 && croisementPossible!=0)//si ce n'est pas le premier mot et qu'il peut etre placer
    {
        Mot->nbrMot++;

        return 1;//on rend 1
    }
    else
    {
        return 0;
    }
}

/*Dans le programme espace horizental il fonctionne exactement de la meme facon que espace verticale*/
int espaceVerticale(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu,int motPossible)
{
    int i,longueur,cpt=0,croisementPossible=0,croisementImpossible=0;

    longueur = strlen(Mot->mot)+Mot->ligne;
    if((Mot->ligne+strlen(Mot->mot)-1)>14)
    {
        system("cls");
        afficherPlateau(jeu);
        affichageChevalet(Mot,joueur);
        printf("Ne peut pas etre mit verticalement\n");
        return 0;
    }

    if(Mot->nbrMot==0)
    {
        for(i=Mot->ligne; i<longueur; i++)
        {
            if(jeu->plateau[i][Mot->col][0]=='#')
                cpt++;
        }
    }


    if(Mot->nbrMot==0)
    {
        croisementPossible = 1;
    }
    else
    {
        for(i=Mot->ligne;i<longueur;i++)
        {
            if(jeu->plateau[i][Mot->col][1]!=0 && jeu->plateau[i][Mot->col][1]==Mot->mot[i-Mot->ligne])
            {
                croisementPossible++;
            }
            if(jeu->plateau[i][Mot->col][1]!=0 && jeu->plateau[i][Mot->col][1]!=Mot->mot[i-Mot->ligne])
            {
                croisementImpossible++;
            }
            if(croisementImpossible!=0)
            {
                printf("Le mot que vous avez mis n'a pas la meme lettre que le mot sur le plateau\n");
                return 0;
            }
        }
    }

    if(Mot->nbrMot==0 && cpt!=0)
    {
        if(motPossible==1)
        {
            Mot->nbrMot++;
        }
        return 1;
    }
    else if(cpt==0&& Mot->nbrMot!=0 && croisementPossible!=0)
    {
        Mot->nbrMot++;
        return 1;
    }
    else
        return 0;

}

void nomJoueur(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs])/* pour demander aux joueurs de saisir leurs noms*/
{
    int i,x=3;
    gotoligcol(x++,82);
    printf("Mettez vos nom:\n");
    for(i=0; i<Mot->nbr_Joueurs; i++)
    {
        fflush(stdin);
        gotoligcol(x++,82);
        printf("Joueur %d:",i+1);
        scanf("%s",joueur[i]->nom);
    }
    printf("\n");
}

t_joueurs ** tableauStruct(t_placer *Mot)//peut etre appelé par le main()
{
    int i;
    t_joueurs **joueur;
    gotoligcol(1,82);
    printf("Combien de joueurs?:");
    scanf("%d",&(Mot->nbr_Joueurs));

    joueur=(t_joueurs**)malloc((Mot->nbr_Joueurs)*sizeof(t_joueurs*));//on alloue dynamiquement de la memoire et au tableau de structure

    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        joueur[i]=(t_joueurs*)malloc(sizeof(t_joueurs));//on alloue de la memoire a chaque structure selon le nbr de joueur
    }
    return joueur;//on rend la structure
}

