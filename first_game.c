#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/*One of adventures*/
/*Václav Doleček 18.08.2019*/
/*Pricip je takový, že hrací plocha je
  vytvořena pomocí čísel, které jsou při
  tisknutí nahracení funcki "dispaly" za
  charaktery. Pohyb je uskutečně tak, že
  se přehazují znaky na základě získakého
  znaku od uživatele. Omezení pohybu je 
  v každé hře samostatně implementováno. */
/*Cíle:
  Vytvořit si vlastní hry
  vymyslet AI protihráče
  zabít čas přes noci kdy nemužu spát */
/*Vše je mé a pouze mé dílo (až na RNG funkci) */

/*Generuje nahodne cisla */
int RNG();

int AI_RNG();

void menu();
/*Funkce pro vykresleni hracího pole */
int display(int pozice);
/*Hra bludiste a kod pro ni */
int bludiste();

/*kod pro lov */
int lov();

int had();

int RNG()
{
    int RNG = 0;

    srand(time(0));

    for(int i = 0; i < 1; i++)
    {
        RNG = (rand() % (18 - 2 + 1)) + 2;
        return RNG;
    }
    return RNG;
}

int AI_RNG()
{
   int RNG = 0;

    srand(time(0));

    for(int i = 0; i < 1; i++)
    {
        RNG = (rand() % (4 - 2 + 1)) + 2;
        return RNG;
    }
    return RNG; 
}

void menu()
{
    printf("One of Adventures\n");
    printf("Zadejte první pismeno, hry si chcete zahrát:\n");
    printf("b   Bludiste\n");
    printf("a   AI Bludiste\n");
    printf("l   Lov\n");
    printf("h   Had-nehotový\n"); 

    printf("\nk   Konec\n");
}

int display(int pozice)
{
    if(pozice == 0)
    {
        printf(" ");
    }
    else if(pozice == 1)
    {
        printf("X");
    }
    else if(pozice == 7)
    {
        printf("O");
    }
    else if(pozice == 4)
    {
        printf("Q");
    }
    else if(pozice == 2)
    {
        printf("Y");
    }
    else if(pozice == 3)
    {
        printf("B");
    }

    return 0;
}

int bludiste()
{   
    char pohyb[2];
    int stav = 0;

    int x = 1;
    int y = 1;
    /*Hrací plocha */
    int array[30] [30] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7} ,
        {7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 7} ,
        {7, 0, 4, 4, 4, 0, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 4, 4, 0, 4, 0, 0, 0, 4, 7} ,
        {7, 0, 4, 0, 0, 0, 4, 0, 0, 4, 0, 4, 4, 0, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 0, 4, 0, 4, 7} ,
        {7, 0, 4, 0, 4, 4, 4, 4, 0, 0, 0, 4, 4, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 0, 0, 0, 4, 0, 4, 7} ,
        {7, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 4, 4, 4, 0, 4, 0, 0, 0, 0, 0, 0, 4, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 4, 4, 4, 0, 4, 4, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 7} ,
        {7, 0, 4, 4, 0, 4, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 0, 7} ,
        {7, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 4, 0, 4, 4, 4, 4, 4, 4, 0, 4, 4, 0, 0, 4, 0, 4, 0, 7} ,
        {7, 0, 4, 0, 0, 4, 4, 4, 4, 0, 4, 4, 4, 0, 4, 0, 0, 0, 4, 4, 0, 4, 4, 4, 4, 4, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 7} ,
        {7, 0, 4, 4, 0, 4, 4, 0, 4, 4, 4, 0, 4, 0, 4, 4, 0, 0, 4, 4, 4, 4, 0, 0, 4, 4, 0, 4, 0, 7} ,
        {7, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 0, 4, 0, 4, 0, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 0, 4, 0, 7} ,
        {7, 0, 4, 4, 0, 4, 0, 0, 0, 0, 0, 4, 4, 0, 4, 0, 4, 4, 0, 4, 4, 0, 4, 4, 4, 4, 0, 4, 0, 7} ,
        {7, 0, 4, 4, 0, 4, 0, 4, 4, 4, 0, 4, 4, 0, 4, 0, 4, 2, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 7} ,
        {7, 0, 4, 0, 0, 4, 0, 0, 4, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 4, 0, 0, 0, 4, 4, 4, 0, 4, 0, 7} ,
        {7, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 4, 0, 4, 0, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 4, 4, 0, 4, 0, 4, 4, 4, 0, 4, 0, 7} ,
        {7, 4, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 4, 4, 4, 0, 0, 0, 4, 4, 0, 4, 0, 0, 0, 0, 0, 4, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0, 4, 4, 4, 0, 4, 0, 0, 4, 4, 0, 4, 0, 7} ,
        {7, 0, 4, 4, 0, 0, 4, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 4, 0, 0, 0, 7} ,
        {7, 0, 4, 4, 0, 4, 4, 0, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 4, 4, 0, 4, 4, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 4, 4, 4, 0, 4, 0, 4, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 4, 4, 0, 7} ,
        {7, 0, 4, 4, 0, 4, 0, 4, 4, 0, 4, 0, 4, 4, 0, 0, 0, 0, 0, 0, 4, 4, 0, 4, 4, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 0, 0, 7} ,
        {7, 4, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 0, 4, 0, 0, 7} ,
        {7, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 4, 7} ,
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7} 
    };
    /*cyklus pro vykreslení hracího pole */
    while(stav == 0 || stav == 2)
    {   
        for(int j = 0;j != 30;j++)
        {
            for(int i = 0;i != 30;i++)
            {
                display(array[i][j]);
            }
            printf("\n");
        }

        if(stav == 2)
        {
            printf("stenou se nedá projít.\n");
            stav = 0;
        }

        printf("ready for next move!\n");
        scanf("%s", pohyb);

        switch(pohyb[0])
        {
            case 'w':
                if(array[x][y-1] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if(array[x][y-1] == 4)
                {
                    stav = 2;
                }

                else if(array[x][y-1] == 2)
                {
                    printf("Vyhráli jste!!!!!\n");
                    stav = 1;
                }

                else
                {
                array[x][y] = 0;
                array[x][y-1] = 1;
                y--;
                }
            break;

            case 'd':
                if(array[x+1][y] == 7)
                {
                    printf("game over\n");
                    return 1;
                }
                
                else if(array[x+1][y] == 4)
                {
                    stav = 2;
                }

                else if(array[x+1][y] == 2)
                {
                    printf("Vyhráli jste!!!!!\n");
                    stav = 1;
                }

                else
                {
                array[x][y] =0;
                array[x+1][y] = 1;
                x++;
                }
            break;

            case 'a':
                if(array[x-1][y] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if(array[x-1][y] == 4)
                {
                    stav = 2;
                }

                else if(array[x-1][y] == 2)
                {
                    printf("Vyhráli jste!!!!!\n");
                    stav = 1;
                }

                else
                {
                array[x][y] =0;
                array[x-1][y] = 1;
                x--;
                }
            break;

            case 's':
                if(array[x][y+1] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if(array[x][y+1] == 4)
                {
                    stav = 2;
                }

                else if(array[x][y+1] == 2)
                {
                    printf("Vyhráli jste!!!!!\n");
                    stav = 1;
                }

                else
                {
                array[x][y] =0;
                array[x][y+1] = 1;
                y++;
                }
            break;

            default:
                stav = 1;

        }
        if(stav == 1)
        {
        menu();
        }
    }
    return 0;
}


int lov()
{
    char pohyb[2];
    int stav = 0;

    int score = 0;

    int x = 1;
    int y = 1;

    int RNG_x = 0;
    int RNG_y = 0;

    int old_x = 2;
    int old_y = 4;

    int array[21] [21] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7} ,
        {7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
    };

    while(stav == 0)
    {   
        for(int j = 0;j != 21;j++)
        {
            for(int i = 0;i != 20;i++)
            {
                display(array[i][j]);
            }
            printf("\n");
        }



        printf("ready for next move!\n");
        scanf("%s", pohyb);

        switch(pohyb[0])
        {
            case 'w':
                if(array[x][y-1] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if (array[x][y-1] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;
                }

                else
                {
                array[x][y] = 0;
                array[x][y-1] = 1;
                y--;
                }
            break;

            case 'd':
                if(array[x+1][y] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if (array[x+1][y] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;
                }

                else
                {
                array[x][y] =0;
                array[x+1][y] = 1;
                x++;
                }
            break;

            case 'a':
                if(array[x-1][y] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if (array[x+1][y] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;

                }
                else
                {
                array[x][y] =0;
                array[x-1][y] = 1;
                x--;
                }
            break;

            case 's':
                if(array[x][y+1] == 7)
                {
                    printf("game over\n");
                    return 1;
                }
                
                else if (array[x][y+1] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;
                }
                else
                {
                array[x][y] =0;
                array[x][y+1] = 1;
                y++;
                }
            break;

            default:
                stav = 1;

        }
        if(stav == 1)
        {
            score = score * 100;
            printf("end of game\n");
            printf("Vaše score: %d\n", score);
            printf("\n");
            menu();
        }
    }
    return 0;
}

int had()
{
    char pohyb[2];
    int stav = 0;

    int score = 0;

    int x = 1;
    int y = 1;

    int RNG_x = 0;
    int RNG_y = 0;

    int old_x = 2;
    int old_y = 4;

    int array[21] [21] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7} ,
        {7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
    };

    while(stav == 0)
    {   
        for(int j = 0;j != 21;j++)
        {
            for(int i = 0;i != 20;i++)
            {
                display(array[i][j]);
            }
            printf("\n");
        }



        printf("ready for next move!\n");
        scanf("%s", pohyb);

        switch(pohyb[0])
        {
            case 'w':
                if(array[x][y-1] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if (array[x][y-1] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;
                }

                else
                {
                //array[x][y] = 0;
                array[x][y-1] = 1;
                y--;
                }
            break;

            case 'd':
                if(array[x+1][y] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if (array[x+1][y] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;
                }

                else
                {
                //array[x][y] =0;
                array[x+1][y] = 1;
                x++;
                }
            break;

            case 'a':
                if(array[x-1][y] == 7)
                {
                    printf("game over\n");
                    return 1;
                }

                else if (array[x+1][y] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;

                }
                else
                {
                //array[x][y] =0;
                array[x-1][y] = 1;
                x--;
                }
            break;

            case 's':
                if(array[x][y+1] == 7)
                {
                    printf("game over\n");
                    return 1;
                }
                
                else if (array[x][y+1] == 2)
                {
                    array[old_x][old_y] = 0;
                    RNG_x = RNG();
                    RNG_y = RNG();
                    array[RNG_x][RNG_y] = 2;
                    old_x = RNG_x;
                    old_y = RNG_y;
                    score++;
                }
                else
                {
                //array[x][y] =0;
                array[x][y+1] = 1;
                y++;
                }
            break;

            default:
                stav = 1;

        }
        if(stav == 1)
        {
            score = score * 100;
            printf("end of game\n");
            printf("Vaše score: %d\n", score);
            printf("\n");
            menu();
        }
    }
    return 0;
}





int main()
{
    char vyber[5];
    int chod = 0;

    menu();

    while(chod == 0)
    {


    scanf("%s", vyber);

        switch(vyber[0])
        {
            case 'b':
                chod = bludiste();
            break;

            case 'a':
                chod = AI_bludiste();
            break;

            case 'l':
                chod = lov();
            break;

            case 'h':
                chod = had();
            break;

            case 'k':
                chod = 1;
            break;

            default:
                printf("toto není vyber");
        }
    }
}

