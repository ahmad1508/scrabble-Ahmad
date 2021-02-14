/* ce fichier contient les fonctions qui demandent le dictionnaire:
    -dictio: qui cherhche la validitée d'un mot dans le dictio.
    -contestation mot: qui va demander au joueur si ils veulent contester le mot.
*/

#include "dictionnaire.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int dictio(t_placer *Mot)
{
    FILE *search;
    char motDictio[15];

    search=fopen("dictio.TXT","r");
    if(search==NULL)
    {
        printf("---echec d'ouverture---\n");
        exit(EXIT_FAILURE);
    }
    else{
        while(!feof(search))
        {
            fflush(stdin);
            fscanf(search,"%s",motDictio);
            if (strcmp(Mot->mot,motDictio)==0)
            {
                fclose(search);
                return 1;
            }
        }
        printf("1");
        }
    fclose(search);
    return 0;
}

int contestationMot(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs])
{
    int x=114,lig=27;
    int i=0,*reponse,n=0,dictionnaire=0;

    reponse = malloc((Mot->nbr_Joueurs)*sizeof(int));// allocation dynamique du tableau qui prend les reponses
    for(i = 0;i<Mot->nbr_Joueurs;i++)//et le met a 0
    {
        reponse[i]=0;
    }
    gotoligcol(26,82);
    printf("Voulez-vous contester le mot de ");
    gotoligcol(26,x++);
    printf("%s",joueur[Mot->tourJ]->nom);
    gotoligcol(26,x+strlen(joueur[Mot->tourJ]->nom));
    printf(" (1-oui/2-non):\n");

    for(i=0;i<Mot->nbr_Joueurs;i++)//pour demander a tous les joueurs sauf celui qui place le mot
    {
        if (i!=Mot->tourJ)
        {
            gotoligcol(lig,82);
            printf("%s",joueur[n]->nom);
            gotoligcol(lig++,82+strlen(joueur[n]->nom));
            printf("?:");
            scanf("%d",&reponse[n]);
        }
        if(reponse[n]==1)// si un joueur demande de contester on sort
        {
            printf("\n");
            gotoligcol(lig,82);
            printf("%s",joueur[n]->nom);
            gotoligcol(lig++,82+strlen(joueur[n]->nom));
            printf(" conteste le mot.");
            break;
        }
        n++;
    }
    if (reponse[0]==1 || reponse[1]==1 || reponse[2]==1 || reponse[3]==1 )// si il lig a contestion de 1 des joueurs
    {

        dictionnaire=dictio(Mot);//on cherche le mot dans le dictionnaire

        if(dictionnaire==1)//si on trouve le mot dans le dictionnaire le joueur qui a contesté perd 10 points
        {
            gotoligcol(lig++,82);
            printf("Le mot est dans le dictionnaire");
            gotoligcol(lig,82);
            printf("%s",joueur[n]->nom);
            gotoligcol(lig++,82+strlen(joueur[n]->nom));
            printf(" a perdu 10 point");
            joueur[n]->score=joueur[n]->score-10;
            return 1;//et on rend 1
        }
        else if(dictionnaire==0)//sinon on rend 0
        {
            gotoligcol(lig,82);
            printf("Le mot n'est pas dans le dictionnaire");
            return 0;
        }
    }
    //si aucun joueur n'a contesté on rend 1
    gotoligcol(lig,82);
    printf("continuer le jeu\n");
    return 1;

}

void Aide()
{

    int choix;

    printf("\t\t*******AIDE SCRABBLE********\n\n");
    do{

    printf("Quel aide voulez vous?\n");
    printf(" 1 - Deroulement d'une partie.\n");
    printf(" 2 - Valeur et nombres des lettres du scrabble.\n");
    printf(" 3 - Fin d'une partie\n");
    printf(" 4 - Quitter\n");

    do{
        scanf("%d",&choix);
    }while(choix<1 || choix>4);


    switch(choix)
    {
    case 1:
        printf("Il vous faut:\n -Le plateau de jeu du Scrabble.\n -Les lettres au nombre de 102 pieces.\n -Le sac pour contenir les lettres\n -Les chevalet pour support.\n -Etre au minimum 2 joueurs (maximum 4 joueurs)\n\n");
        printf("Le joueur choisi parmi les lettres qu’il a tirees et pose a tour de role une horizontalement \n");
        printf("ou plusieurs lettres de maniere a former de nouveaux mots sur la grille,ou verticalement.\n");
        printf("Il n'est pas admis de poser un mot en diagonale. Le premier mot doit faire au moins deux lettres\n");
        printf("et recouvrir la case centrale (materialisee parle caractere '&') et les mots suivants doivent\n");
        printf(" s'appuyer sur des mots deja places, a la maniere des mots croises.\n\n");

        printf("Le score d'un coup est calcule en additionnant la valeur de toutes les lettres des nouveaux \n");
        printf("mots formes (y compris celles deja posees sur la grille). Si une nouvelle lettre posee recouvre \n");
        printf("une case 'lettre comptedouble' ( caractère '&' ) ou  'lettre compte triple' ( caractere pourcent ),\n");
        printf("sa valeur est multipliee par 2 ou par 3 ; si cette case fait partie de 2 nouveaux mots formes,\n");
        printf("horizontalement et verticalement, elle compte double ou triple dans les deux sens.Si une case \n");
        printf("'mot compte double' (caractere '@')ou 'mot compte triple' (caractère '§') a ete recouverte, la\n");
        printf("valeur du mot entier est doublee ou triplee. Si en recouvrant cette case, cela forme deux mots \n");
        printf("horizontalement et verticalement, la valeur des deux mots est multipliee par 2 ou par 3. Les cases\n");
        printf("multiplicatrices ne servent plus une fois recouvertes.\n\n");

        printf("Placer ses sept lettres sur la grille apporte une prime de 50 points. Ce genre de coup est appele\n");
        printf("'scrabble' en français. Le joueur qui « fait un scrabble », a « scrabbler ».Apres avoir posé ses \n");
        printf("lettres et annonce son score, le tour est terminé. Il est alors possible de demander a verifier la \n");
        printf("présence d'un mot joue dans un dictionnaire de reference, convenu entre les joueurs : sans bonus,\n");
        printf("la vérification est manuelle avec le bonus, le programme vérifiera lui-même la validite du mot tel \n");
        printf("que defini plus bas..\n\n");

        printf("Si un mot conteste n'est pas valable, le joueur reprend ses lettres et marque zero point pour le coup.\n");
        printf("Par contre si le mot conteste est valable, le demandeur qui a contesté perd dix points.\n");
        printf("Les actions possibles sont :\n");
        printf(" - passer son tour\n");
        printf(" - changer une ou plusieurs lettres de son jeu (dans ce cas il est impossible de poser un nouveau mot).\n\n");

        break;

    case 2 :
        printf("Valeurs et nombres de lettres du Scrabble :\n");
        printf("La lettre A	Valeur : 1 point	Nombre : 9 pieces\n");
        printf("La lettre B	Valeur : 3 points	Nombre : 2 pieces\n");
        printf("La lettre C	Valeur : 3 points	Nombre : 2 pieces\n");
        printf("La lettre D	Valeur : 2 points	Nombre : 3 pieces\n");
        printf("La lettre E	Valeur : 1 point	Nombre : 15 pieces\n");
        printf("La lettre F	Valeur : 4 points	Nombre : 2 pieces\n");
        printf("La lettre G	Valeur : 2 points	Nombre : 2 pieces\n");
        printf("La lettre H	Valeur : 4 points	Nombre : 2 pieces\n");
        printf("La lettre I	Valeur : 1 point	Nombre : 8 pieces\n");
        printf("La lettre J	Valeur : 8 points	Nombre : 1 piece\n");
        printf("La lettre K	Valeur : 10 points	Nombre : 1 piece\n");
        printf("La lettre L	Valeur : 1 point	Nombre : 5 pieces\n");
        printf("La lettre M	Valeur : 2 points	Nombre : 3 pieces\n");
        printf("La lettre N	Valeur : 1 point	Nombre : 6 pieces\n");
        printf("La lettre O	Valeur : 1 point	Nombre : 6 pieces\n");
        printf("La lettre P	Valeur : 3 points	Nombre : 2 pieces\n");
        printf("La lettre Q	Valeur : 8 points	Nombre : 1 piece\n");
        printf("La lettre R	Valeur : 1 point	Nombre : 6 pieces\n");
        printf("La lettre S	Valeur : 1 point	Nombre : 6 pieces\n");
        printf("La lettre T	Valeur : 1 point	Nombre : 6 pieces\n");
        printf("La lettre U	Valeur : 1 point	Nombre : 6 pieces\n");
        printf("La lettre V	Valeur : 4 points	Nombre : 2 pieces\n");
        printf("La lettre W	Valeur : 10 points	Nombre : 1 piece\n");
        printf("La lettre X	Valeur : 10 points	Nombre : 1 piece\n");
        printf("La lettre Y	Valeur : 10 points	Nombre : 1 piece\n");
        printf("La lettre Z	Valeur : 10 points	Nombre : 1 piece\n");
        printf("Jokers	Valeur : 0 point	Nombre : 2 pieces\n\n");
        break;

    case 3:
        printf("La partie s'acheve quand le sac est vide et qu'un joueur place ses dernieres lettres sur la grille.\n");
        printf("Il ajoute a son score la valeur des lettres restant a ses adversaires, qui dans le meme temps,doivent\n");
        printf("deduire de leur score la valeur des lettres qui leur restent. Le vainqueur est celui qui totalise\n") ;
        printf("le plus de points a la fin de la partie.\n\n");

    default:break;
    }

    }while(choix<4);
}
