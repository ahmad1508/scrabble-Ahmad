/**Dans ce fichier on a mis les sous programmes qui concernent le chevalet donc :
    -affichage : c'est la fonction qui va afficher le chevalet.
    -remplissage : c'est la fonction qui remplit le chevalet apres avoir placer des lettres sur le plateau et va les enlever de la pioche.
    -lettrePlateau : va voir les lettres qui sont déjà sur le plateau.
    -check_lettre_Mot : va voir si les lettres qui ne sont pas sur le plateau se trouve dans le chevalet.
    -reste chevalet : va voir combien de lettres il y a dans le chevalet au cas où on arrive a la fin et veux savoir qui a place
     le dernier mot.

on a aussi mis quelques autres fonctions qui peuvent etre en relation :
    -initialiser les 3 struct: pour initialiser les 3 structures
    -vooirfinpartie : va voir si on est arrivé a la fin de la partie
    -finPartie: appeler par voidfinpartie si la pioche est vide et un des joueurs place le dernier mot possible.
*/
#include "Chevalet.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



/**on va mettre notre structure a 0 et alors du debut de programme de sauvegarder on
appelle le programme qui remplit le tableau pour remplir les signes**/
void initialiser_struct(t_placer *Mot , t_joueurs *joueur[Mot->nbr_Joueurs] ,t_donnee *jeu )
{
    int i,j;

    for(i=0;i<NBLIGNE;i++)//plateau a null
    {
        for(j=0;j<NBCOLONNE;j++)
        {
            jeu->plateau[i][j][0]=0;
            jeu->plateau[i][j][1]=0;
        }
    }

    melangePioche(jeu);//melanger la pioche
    //initialisation structure Mot
    Mot->nbrMot=0;
    Mot->colonne=0;
    Mot->col=0;
    Mot->direction=0;
    Mot->ligne=0;
    Mot->tourJ=0;

    //init structure joueurs
    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        for(j=0;j<50;j++)
        {
            joueur[i]->nom[j]=0;
        }
    }
    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        for(j=0;j<7;j++)
        {
            joueur[i]->chevalet[j]=' ';
        }
    }
    for(i=0;i<Mot->nbr_Joueurs;i++)
        joueur[i]->score=0;
}

void affichageChevalet(t_placer *Mot , t_joueurs *joueur[Mot->nbr_Joueurs])
{
    int i, x=104;
    gotoligcol(9,82);
    printf("Chevalet du joueur %d:",Mot->tourJ+1);
    for(i=0;i<7;i++)
    {
        x++;
        gotoligcol(9,x);
        printf(" ");
        Color(6,0);//fonction couleur
        x++;
        gotoligcol(9,x);
        printf("%c",joueur[Mot->tourJ]->chevalet[i]);//affiche la lettre du chevalet du joueur qui joue
        Color(15,0);
        x++;
        gotoligcol(9,x);
        printf("%d ",valeurLettre(joueur[Mot->tourJ]->chevalet[i]));//affiche la valeur de la lettre

    }

}



void rempliChevalet(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs], t_donnee *jeu)
{
    int nb,i,j;
    char tempo;

    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        for(j=0;j<7;j++)
        {
            if((joueur[i]->chevalet[j])==' ') //si dans le chevalet il y a un espace
            {
                do{
                nb=rand()%102;//on va tirer un nombre aleatoire

                if((jeu->pioche[nb])!=' ')//et aller voir si dans la pioche il correspond a une lettre et pas un vide
                {
                    tempo=jeu->pioche[nb];//si oui on met la lettre tirée dans notre chevalet
                    jeu->pioche[nb]=' ';//et on met un vide dans la pioche a la place de la lettre
                    joueur[i]->chevalet[j]=tempo;
                }
                }while((joueur[i]->chevalet[j])==' ');//et on fait ca tant que une place dans le chevalet est vide
            }
        }
    }

}

void vidageChevalet(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs])
{
    int i,j;
    for(i=0;i<strlen(Mot->mot);i++)
    {
        for(j=0;j<7;j++)
        {
            if(Mot->lettrePlateau[i]==0)
            {
                if(Mot->mot[i]==joueur[Mot->tourJ]->chevalet[j])/*si on a placé un mot il faut enlever les lettres du chevalet
                                                            on va enlever les lettres placees du chevalet*/
                {
                joueur[Mot->tourJ]->chevalet[j]=' ';//met un espace a la place pour que remplissage chevalet remet des nouvelles lettres
                break;//pour sortir de la boucle la plus interne si on trouve la lettre et pas l'enlever plusieurs fois
                }
            }
        }
    }
}

int lettre_plateau(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs], t_donnee *jeu)
{
    int i,col=0,count=0,ligne=0;

    col=Mot->col;//on donne la colonne a col pour pas modifier la struct

    Mot->lettrePlateau = malloc(strlen(Mot->mot)*sizeof(int));//on alloue dynamiquement de la memoire au tableau d'entiers


    for(i=0;i<strlen(Mot->mot);i++)//on va initialiser a 0 le tableau
    {
        Mot->lettrePlateau[i]=0;
    }

    if(Mot->direction == 'H' || Mot->direction == 'h')
    {
        for(i=0;i<strlen(Mot->mot);i++)
        {
            if(Mot->mot[i]==(jeu->plateau[Mot->ligne][col+i][1]))// on va voir si on trouve les lettres du mot sur le plateau
            {
                Mot->lettrePlateau[i]=1;//si on trouve on met la valeur du tableau correspondante a 1
                count++;//et on incremente le compteur qui compte combien de lettres du mot sont sur le plateau
            }
        }
    }
    ligne=Mot->ligne;
    if(Mot->direction == 'V' || Mot->direction == 'v')// on fait la meme chose si le mot est placé verticalement
    {
        for(i=0;i<strlen(Mot->mot);i++)
        {
            if(Mot->mot[i]==(jeu->plateau[ligne+i][Mot->col][1]))
            {
                Mot->lettrePlateau[i]=1;
                count++;
            }
        }
    }
    return count;// on retourne le nbr de lettre trouve sur le plateau
}

int check_lettre_mot(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs], t_donnee *jeu)
{
    int i,j,cpt=0,count=0;
    char tempo[8]={0,0,0,0,0,0,0,0};/*ce tableau ou chevalet temporaire va nous permettre de voir si le reste des lettres
                                      du mot sont dans le chevalet et pouvoir faire des changements sans affecter le chevalet initial
                                      dans le cas où on ne peut placer le mot*/

    count = lettre_plateau(Mot,joueur,jeu);//va prendre la valeur rendue par le programme précédent

    for(i=0;i<8;i++)
    {
        tempo[i]=joueur[Mot->tourJ]->chevalet[i];//on copie le chevalet dans le tableau tempo on pouvait utiliser strcpy
    }

    if((strlen(Mot->mot)-count)>7)/*si la longueur du mot - les lettres déjà sur le plateau est plus que 7 cela signifie qu'il a
                                    plus que 7 lettre à fournir du chevalet ce qui est impossible*/
    {
        printf("Vous n'avez que 7 lettres\n");
        return 0;
    }
    else
    {
        for(i=0;i<strlen(Mot->mot);i++)
        {
            for(j=0;j<7;j++)
            {
                if(Mot->lettrePlateau[i]==0 && Mot->mot[i]==tempo[j])/*sinon on cherche dans le chevalet les lettres qui sont a 0 dans
                                                        le tableau lettreplateau */
                {
                    tempo[j]=' ';
                    cpt++;
                    break;
                }
            }
        }
        cpt=cpt+count;
        if (cpt==strlen(Mot->mot))//si les lettres trouvées sur le plateau et dans le chevalet sont de la longueur du mot
            return 1;//on retourne 1
        else//sinon
        {
            printf("Vous n'avez pas les bonnes lettres.\n");
            return 0;//on retourne 0
        }
    }
}

void changerLettre(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu)
{
    int i,cpt=0;
    char carac_a_remplasser;

    affichageChevalet(Mot,joueur);

    srand(time(NULL));
    gotoligcol(16,82);
    printf("Quel lettre voulez-vous changer?");
    gotoligcol(17,82);
    printf("Lettre :");
    fflush(stdin);
    scanf("%c",&carac_a_remplasser);

    if(carac_a_remplasser>=97 && carac_a_remplasser<=122)//on change la lettre en majuscule si elle était minuscule
    {
        carac_a_remplasser=carac_a_remplasser-'a'+'A';
    }

    for(i=0;i<7;i++)
    {
        if(joueur[Mot->tourJ]->chevalet[i]==carac_a_remplasser)
        {
            joueur[Mot->tourJ]->chevalet[i]=' ';//on met un espace à la place de cette lettre
            rempliChevalet(Mot,joueur,jeu);//et on remplit
            cpt++;//et on incremente le compteur
            break;//et on sort de la boucle
        }

    }
    if(cpt==0)
    {
        gotoligcol(17,82);
        printf("vous n'avez pas cette lettre");//si le compteur n'a pas été incrementé c'est qu'on a pas la lettre
    }
    else{
        while(1)//sinon on cherche une place vide dans la pioche aleatoirement pour mettre cette lettre
        {
            i=rand()%102;
            if(jeu->pioche[i]==' ')
            {
                jeu->pioche[i]=carac_a_remplasser;
                break;
            }
        }
    }
    system("cls");
    afficherPlateau(jeu);
    affichageChevalet(Mot,joueur);
    fflush(stdin);
    gotoligcol(11,82);
    printf("presser entrer pour continuer:");
    getchar();
}


void resteChevalet(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],int lettreChevalet[Mot->nbr_Joueurs])
{
    int i, j ;

    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        for(j=0;j<7;j++)
        {
            if(joueur[i]->chevalet[j]>=65 && joueur[i]->chevalet[j]<=90)
            {
                lettreChevalet[i]++;// on fait un tableau pour compter le nombre de lettres dans es chevalet des joueurs
            }
        }
    }
}


void VoirFinPartie(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs],t_donnee * jeu)
{
    int i,cptPioche=0,CPT=0,chevalet=0;
    int lettreChevalet[Mot->nbr_Joueurs];
    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        lettreChevalet[i]=0;
    }
    for(i=0;i<102;i++)
    {
        if (jeu->pioche[i]==' ')
            cptPioche++;//on va voir si la pioche est vide en incrementant le cpt si la case est vide
    }

    resteChevalet(Mot,joueur,lettreChevalet);//on voie le reste dans le chevalet des joueurs
    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        if(lettreChevalet[i]==0)
        {
            CPT++;
            chevalet=i;///A REVOIR//
            break;
        }
    }

    if (cptPioche==102 && CPT==1)// si la pioche est vide et que un des joueurs a placé le dernier mot
    {
        printf("La partie est terminee\n");
        FinPartie(Mot,joueur,lettreChevalet,chevalet);// on appelle fin partie
        printf("presser entrer pour continuer:");
        fflush(stdin);
        getchar();
        menu(Mot,joueur,jeu);
    }

}

void FinPartie(t_placer *Mot,t_joueurs *joueur[Mot->nbr_Joueurs] , int *lettreChevalet , int chevalet)
{
    char carac;
    int i,j,vainqueur=0;

    printf("C'est ");
    for(i=0;joueur[chevalet]->nom[i]!='\0';i++)// va dire qui a placé le dernier mot
    {
        printf("%c",joueur[chevalet]->nom[i]);
    }
    printf(" qui a place le dernier mot.\n");

    for(i=0;i<Mot->nbr_Joueurs;i++)
    {
        for(j=0;j<7;j++)
        {
            carac=joueur[i]->chevalet[j];///A REVOIR///
            joueur[chevalet]->score=joueur[chevalet]->score+valeurLettre(carac);
        }
    }

    affichageScore(Mot,joueur);//on affiche le score

//on compare les score pour voir qui a le plus haut
    for(i=1;i<Mot->nbr_Joueurs;i++)
    {
        if(joueur[vainqueur]->score==joueur[i]->score)// si deux on le meme score
        {
            if(lettreChevalet[vainqueur]>lettreChevalet[i])//c'est celui qui a le moins de lettres dans son chevalet qui gagne
            {
                vainqueur = i;
            }

        }
        else if(joueur[i]->score>joueur[vainqueur]->score)
        {
            vainqueur = i;
        }
    }

    printf("Le vainqueur de cette partie est **** ");///on annonce le vainqueur
    for(i=0;joueur[vainqueur]->nom[i]!='\0';i++)
    {
        if(joueur[vainqueur]->nom[i]>=97 && joueur[vainqueur]->nom[i]<=122)
        {
            joueur[vainqueur]->nom[i]=joueur[vainqueur]->nom[i]-'a'+'A';
        }
        printf("%c",joueur[vainqueur]->nom[i]);
    }
    printf(" ****\n\n");
}
