/*
**autor: Václav Doleček -> TrelohnaT
**datum: 2:13 27.01.2020
**motivace: necitit se že prokrastinuju když se neučím na zkoušky
            a touha dělat to, proč jsem šel na VUT FIT
**Název: Dark Lost
**Popis: hra ve které hráč vidí jen to, co mu dovoluje vidět jeho poloha v bludišti a co mu "osvětlí pochodeň"
         některé funkce použity z mých minulých projektů
**Popis pro programátora: Mám rád, když je všecko pohoromadě v jednou soboru. Do not judge me!

**TO DO: AI strašidla, které pujdou po hráči
         Hru samotnou
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*deklarace funkcí*/
void dark_lost();

void display(int pozice);

int RNG();




int main()
{

    dark_lost();

    return 0;
}

void dark_lost()
{
    char input[3];  //zde se ukládá input hráče
    input[0] = 0;

    int state = 1;  //hlavní herní smyčka, dokud 1 tak se hraje, 2 je výhra

    int player_x = 6;   //poloha hráče na X ose
    int player_y = 6;   //poloha hráče na Y ose

    int monster_x = 0;
    int monster_y = 0;

    //int torch_x[3];
    //int torch_y[3];

    int torch_count = 0;
    
    int k = 0;  //koeficient viditelnosti (1 => nevidí / 0 => vidí)

    
    
    int array [13] [13] [2] = {
        {{7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {5, 1}, {0, 1}, {5, 1}, {5, 1}, {0, 1}, {5, 1}, {5, 1}, {0, 1}, {5, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 0}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 0}, {1, 1}, {0, 0}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 0}, {5, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {5, 1}, {0, 1}, {5, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {0, 1}, {0, 1}, {5, 1}, {0, 1}, {7, 1}},
        {{7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}, {7, 1}}
    };

    /*
    Zde se náhodně vygeneruje cíl
    */
    int RNG_number = RNG();
    switch (RNG_number)
    {
    case 0:
        array[2][2][0] = 9;
        array[1][1][0] = 3;
        monster_x = 1;
        monster_y = 1;       
    break;

    case 1:
        array[2][10][0] = 9;
        array[1][11][0] = 3;
        monster_x = 1;
        monster_y = 11;
    break;

    case 2:
        array[10][2][0] = 9;
        array[11][1][0] = 3;
        monster_x = 11;
        monster_y = 1;
    break;

    case 3:
        array[10][10][0] = 9;
        array[11][11][0] = 3;
        monster_x = 11;
        monster_y = 11;
    break;
    
    default:
        printf("Tento stav by neměl nasta, pokud nastal, něco se seriozně podělalo\n");
    break;
    }

    while(state == 1)
    {   
        /*
        **vykreslení hrací mapy
        **parametr k určuje, zda je políčko viditelné či nikoliv (1 => viditelný / 0 => neviditelný)
        */

        for(int j = 0;j != 13;j++)
        {
            for(int i = 0;i != 13;i++)
            {
                if(array[i][j][1] == 0 || array[i][j][0] == 7 || array[i][j][0] == 2 || array[i][j][0] == 1)
                {
                    display(array[i][j][k]);   //tato funkce přetypovává a tiskne jednotlivé znaky
                }
                else
                {
                    printf(" ");
                }                    
            }
            printf("\n");   //po každém řádku následuje mezera
        }

        /*tisk kolik zbývjá pochodní*/
        printf("Used Torches %d of 3\n", torch_count);
        printf("TEST PURPOSE -- RNG: %d\n", RNG_number);

        /*
        **Políčka, která už mohla být viditelná, se opět zneviditelní
        */

        

        scanf("%s", input);

        switch (input[0])
        {
            case 'a':
                if(array[player_x-1][player_y][0] == 7)
                {
                    printf("Can not go out of map\n");  
                }
                else if(array[player_x-1][player_y][0] == 5)
                {
                    printf("Can not pass by wall\n");
                }
                else if(array[player_x-1][player_y][0] == 9)
                {
                    state = 2;
                }
                else if(array[player_x][player_y][0] == 2)
                {
                    array[player_x-1][player_y][0] = 1;
                    player_x--; 
                }
                else
                {
                    /*sbírání pochodní*/
                    if(array[player_x-1][player_y][0] == 2)
                    {
                        torch_count--;
                    }
                    /*změna místa*/
                    array[player_x][player_y][0] = 0;
                    array[player_x-1][player_y][0] = 1;
                    /*změna viditelnosti*/
                    /*zviditelním*/
                    array[player_x-2][player_y][1] = 0;
                    array[player_x-1][player_y+1][1] = 0;
                    array[player_x-1][player_y-1][1] = 0;
                    array[player_x][player_y][1] = 0;
                    /*zneviditelním*/
                    array[player_x+1][player_y][1] = 1;
                    array[player_x][player_y-1][1] = 1;
                    array[player_x][player_y+1][1] = 1;
                    
                    /*počitádlo polohy*/
                    player_x--;
                }
            break;

            case 'd':
                if(array[player_x+1][player_y][0] == 7)
                {
                    printf("Can not go out of map\n");  
                }
                else if(array[player_x+1][player_y][0] == 5)
                {
                    printf("Can not pass by wall\n");
                }
                else if (array[player_x+1][player_y][0] == 9)
                {
                    state = 2;
                }
                else if(array[player_x][player_y][0] == 2)
                {
                    array[player_x+1][player_y][0] = 1;
                    player_x++; 
                }
                else
                {
                    if(array[player_x+1][player_y][0] == 2)
                    {
                        torch_count--;
                    }
                    /*změna polohy*/
                    array[player_x][player_y][0] = 0;
                    array[player_x+1][player_y][0] = 1;
                    /*změna viditelnost*/
                    /*zviditelním*/
                    array[player_x+2][player_y][1] = 0;
                    array[player_x+1][player_y-1][1] = 0;
                    array[player_x+1][player_y+1][1] = 0;
                    array[player_x][player_y][1] = 0;
                    /*zneviditelním*/
                    array[player_x-1][player_y][1] = 1;
                    array[player_x][player_y-1][1] = 1;
                    array[player_x][player_y+1][1] = 1;
                    player_x++;
                }
            break;

            case 's':
                if(array[player_x][player_y+1][0] == 7)
                {
                    printf("Can not go out of map\n");  
                }
                else if(array[player_x][player_y+1][0] == 5)
                {
                    printf("Can not pass by wall\n");
                }
                else if(array[player_x][player_y+1][0] == 9)
                {
                    state = 2;
                }
                else if(array[player_x][player_y][0] == 2)
                {
                    array[player_x][player_y+1][0] = 1;
                    player_y++; 
                }
                else
                {
                    if(array[player_x][player_y+1][0] == 2)
                    {
                        torch_count--;
                    }
                    /*změna polohy*/
                    array[player_x][player_y][0] = 0;
                    array[player_x][player_y+1][0] = 1;
                    /*změna viditelnosti*/
                    /*zviditelním*/
                    array[player_x][player_y+2][1] = 0;
                    array[player_x-1][player_y+1][1] = 0;
                    array[player_x+1][player_y+1][1] = 0;
                    array[player_x][player_y][1] = 0;
                    /*zneviditilením*/
                    array[player_x][player_y-1][1] = 1;
                    array[player_x-1][player_y][1] = 1;
                    array[player_x+1][player_y][1] = 1;
                    player_y++;
                }
            break;

            case 'w':
                if(array[player_x][player_y-1][0] == 7)
                {
                    printf("Can not go out of map\n");  
                }
                else if(array[player_x][player_y-1][0] == 5)
                {
                    printf("Can not pass by wall\n");
                }
                else if(array[player_x][player_y-1][0] == 9)
                {
                    state = 2;
                }
                else if(array[player_x][player_y][0] == 2)
                {
                    array[player_x][player_y-1][0] = 1;
                    player_y--; 
                }
                else
                {
                    if(array[player_x][player_y-1][0] == 2)
                    {
                        torch_count--;
                    }
                    /*změna polohy*/
                    array[player_x][player_y][0] = 0;
                    array[player_x][player_y-1][0] = 1;
                    /*změna viditelnosti*/
                    /*zviditelním*/
                    array[player_x][player_y-2][1] = 0;
                    array[player_x-1][player_y-1][1] = 0;
                    array[player_x+1][player_y-1][1] = 0;
                    array[player_x][player_y][1] = 0;
                    /*zneviditelním*/
                    array[player_x][player_y+1][1] = 1;
                    array[player_x-1][player_y][1] = 1;
                    array[player_x+1][player_y][1] = 1;
                    player_y--;
                }
            break;

            case 'f':
                if(torch_count <= 2)
                {
                   array[player_x][player_y][0] = 2;
                   torch_count++; 
                }
                else
                {
                    printf("You used all your torches\n");
                }
                

            break;

            case 'q':
                state = 0;
            break;

            case 0:
                /*nic nedělej*/
            break;
        
            default:
                printf("Move w s a d\n quit by q\n");
            break;
        }
    
        /*
        **toto je "AI" pro mostrun, funguje na základně náhodných čísel, které udávají směr, kudy se vydat
        */
        RNG_number = RNG();
        printf("Monster direction: %d\n", RNG_number);
        switch (RNG_number)
        {
        case 0:
            if(array[monster_x][monster_y-1][0] == 0)
            {
                array[monster_x][monster_y-1][0] = 3;
                array[monster_x][monster_y][0] = 0;
                monster_y--;
            }
            else if(array[monster_x][monster_y-1][0] == 1)
            {
                state = 3;
            }
        break;

        case 1:
            if(array[monster_x][monster_y+1][0] == 0)
            {
                array[monster_x][monster_y+1][0] = 3;
                array[monster_x][monster_y][0] = 0;
                monster_y++;
            }
            else if(array[monster_x][monster_y+1][0] == 1)
            {
                state = 3;
            }
        break;

        case 2:
            if(array[monster_x+1][monster_y][0] == 0)
            {
                array[monster_x+1][monster_y][0] = 3;
                array[monster_x][monster_y][0] = 0;
                monster_x++;
            }
            else if(array[monster_x+1][monster_y][0] == 1)
            {
                state = 3;
            }
        break;

        case 3:
            if(array[monster_x-1][monster_y][0] == 0)
            {
                array[monster_x-1][monster_y][0] = 3;
                array[monster_x][monster_y][0] = 0;
                monster_x--;
            }
            else if(array[monster_x-1][monster_y][0] == 1)
            {
                state = 3;
            }
        break;
        
        default:
            break;
        }
    }

    if(state == 2)
    {
        printf("Congratulation, you WIN !!!\n");
        return;
    }

    if(state == 3)
    {
        printf("You have been eaten by monster...\n");
        return;
    }
}


/*
**zde se přetypovává a tiskne jednotlivá políčka mapy
*/

void display(int pozice)
{
    /*volné místo*/
    if(pozice == 0)
    {
        printf(".");
    }
    /*hrac*/
    else if(pozice == 1)
    {
        printf("T");
    }
    /*polozena pochoden*/
    else if(pozice == 2)
    {
        printf("i");
    }
    /*strašidlo/monstrun*/
    else if(pozice == 3)
    {
        printf("&");
    }
    /*zničitelná stěna*/
    else if(pozice == 5)
    {
        printf("H");
    }
    /*stena mapy*/
    else if(pozice == 7)
    {
        printf("O");
    }
    /*cíl*/
    else if(pozice == 9)
    {
        printf("V");
    }

}

/*
**Random Number Generátor
**využívá pro rozhodnutí, zda néco padne z rozbité zdi
**tuto funkci jsem si našel na netu a opsal jsem jí
*/
int RNG()
{
    int RNG = 0;    //návratová hodnota
    int range = 3; //range náhodných čísel

    srand(time(0)); //nwm ale je to tu třeba
    
    /*proto tu je for co se provede jen jednou*/
    for(int i = 0; i < 1; i++)
    {
        RNG = (rand() % range);  //toto nějak vyhodí náhodné číslo 
        return RNG;
    }
    return RNG;
}


