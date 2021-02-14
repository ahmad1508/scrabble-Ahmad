/* ce fichier contient les fonctions du plateau:
    -remplissage plateau qui remplit le plateau avec les caracteres speciaux
    -affichage plateau qui affiche le plateau et le contenu de chaque case
*/
#include "Plateau.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void remplissageplateau(t_donnee *jeu)
{

    int i,j;
    ///initialise le tableau de caracteres
    for (i=0; i<NBLIGNE; i++)
    {
        for(j=0; j<NBCOLONNE; j++)
        {
            jeu->plateau[i][j][0]=0;
            jeu->plateau[i][j][1]=0;
        }
    }

    /// symbol '#' et '§'
    for (i=0; i<NBLIGNE; i++)
    {
        for(j=0; j<NBCOLONNE; j++)
        {
            if(i==0||i==7||i==14)                                         //pour mettre le # et §
            {
                if(j==0||j==7||j==14)
                {
                    if(i==7&&j==7)
                    {
                        jeu->plateau[i][j][0]='#';

                    }
                    else
                    {
                        jeu->plateau[i][j][0]='$';
                    }
                }
            }
        }
    }


    ///symbol '@'
    for(i=1; i<=4; i++)
    {
        for(j=1; j<=4; j++)
        {
            if(i==j)
            {
                jeu->plateau[i][j][0]='@';
            }
        }
        for(j=13; j>=10; j--)
        {
            if(j==NBLIGNE-1-i)
            {
                jeu->plateau[i][j][0]='@';
            }
        }
    }

    ///symbol '@'
    for(i=10; i<=13; i++)
    {
        for(j=10; j<=13; j++)
        {
            if(i==j)
            {
                jeu->plateau[i][j][0]='@';
            }
        }
        for(j=4; j>=1; j--)
        {
            if(j==NBLIGNE-1-i)
            {
                jeu->plateau[i][j][0]='@';
            }
        }
    }

    ///du symbol '%'
    for(i=1; i<=13; i=i+4)
    {
        for(j=1; j<=13; j=j+4)
        {
            if(jeu->plateau[i][j][0]=='@')
                continue;
            else
                jeu->plateau[i][j][0]='%';
        }
    }

    ///symbol '&'
    for(i=0;i<15;i++)
    {
        if(i==7)
        {
            jeu->plateau[i][3][0]='&';
            jeu->plateau[i][11][0]='&';
        }
        if(i==6||i==8)
        {
            jeu->plateau[i][2][0]='&';
            jeu->plateau[i][6][0]='&';
            jeu->plateau[i][8][0]='&';
            jeu->plateau[i][12][0]='&';
        }
        if(i==3||i==11)
        {
            jeu->plateau[i][0][0]='&';
            jeu->plateau[i][7][0]='&';
            jeu->plateau[i][14][0]='&';
        }
        if(i==2||i==12)
        {
            jeu->plateau[i][6][0]='&';
            jeu->plateau[i][8][0]='&';
        }
        if(i==0||i==14)
        {
            jeu->plateau[i][3][0]='&';
            jeu->plateau[i][11][0]='&';
        }
    }

}
///affichage du jeu->plateau
void afficherPlateau(t_donnee *jeu)
{
    printf("\n");
    Color(2,0);
    printf("     |");
    int i,j;

    for(i=0; i<NBLIGNE; i++)
    {
        Color(15,0);
        printf(" %c  ",i+65);
        Color(2,0);
        printf("|");

    }
    Color(2,0);
    printf("\n");
    printf("  ---+");
    for(j=0;j<NBLIGNE;j++)
            printf("----+");

        printf("\n");


    for(i=0; i<NBLIGNE; i++)
    {
        Color(15,0);
        printf("  %2d ",i+1);
        Color(2,0);
        printf("|");
        for(int j=0; j<NBCOLONNE; j++)
        {
            if(jeu->plateau[i][j][0]=='&')//les if pour mettre de couleurs differentes pour chaque caracteres differents
            {
                Color(9,0);
                printf(" %c",jeu->plateau[i][j][0]);
            }
            else if(jeu->plateau[i][j][0]=='@')
            {
                Color(12,0);
                printf(" %c",jeu->plateau[i][j][0]);
            }
            else if(jeu->plateau[i][j][0]=='#')
            {
                Color(12,0);
                printf(" %c",jeu->plateau[i][j][0]);
            }
             else if(jeu->plateau[i][j][0]=='$')
            {
                Color(4,0);
                printf(" %c",jeu->plateau[i][j][0]);
            }
            else if(jeu->plateau[i][j][0]=='%')
            {
                Color(1,0);
                printf(" %c",jeu->plateau[i][j][0]);
            }
            else{
                printf("%c ",jeu->plateau[i][j][0]);
            }

        Color(15,0);
        printf("%c ",jeu->plateau[i][j][1]);

        Color(2,0);
        printf("|");
        }


        Color(2,0);
        printf("\n");
        printf("  ---+");
        for(j=0;j<NBLIGNE;j++)
            printf("----+");

        printf("\n");
    }

    printf("\n");
    Color(15,0);
}
