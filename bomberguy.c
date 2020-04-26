/*Autor: Václav Doleček (Trelohnat)*/
/*Datum začátku: 26.12.2019*/
/*Motivace: zjistit jestli to dokážu*/
/*Cíle: naprogramovat střílející "vesmírnou" arkádu*/
/*Společnost: UniSoftCorn*/
/*Datum verze 1.0: 03.01.2020*/

/*Verze: 1.0*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>



int RNG();

void bomberguy();

void display(int pozice);

int bombFlag = 0;

int main()
{   
    char anyKey[3];

    /*
    ** toto je tutorial, slouží pro vysvětlení ovládání a mechanik hry
    */

    printf("Welcome to \n\t ->Bomberguy<- \t\nby Trelohnat\n");
    printf("\tyeah it is like Bomberman...\n");
    printf("\n");
    printf("First thinks first:\n");
    printf("-> Movement by w a s d\n");
    printf("-> Bomb deploy by f\n");
    printf("-> Your objective is get to the V character which is somewhere in game space\n");
    printf("-> Character B is power up and bonus points, but bee carefull\n");
    printf("-> You can exit for game by typing q character\n");
    printf("-> Your command must be confirmed by pressing enter\n");
    printf("\n");
    printf("If you understand, Press any key and confirm it\n");
    scanf("%s", anyKey);

    printf("Now you are in the game, enjoy!\n");
    bomberguy();
   
}

/*
**Random Number Generátor
**využívá pro rozhodnutí, zda néco padne z rozbité zdi
**tuto funkci jsem si našel na netu a opsal jsem jí
*/
int RNG()
{
    int RNG = 0;    //návratová hodnota
    int range = 42; //range náhodných čísel

    srand(time(0)); //nwm ale je to tu třeba
    
    /*proto tu je for co se provede jen jednou*/
    for(int i = 0; i < 1; i++)
    {
        RNG = (rand() % range);  //toto nějak vyhodí náhodné číslo 
        return RNG;
    }
    return RNG;
}
/*
**Toto je hra samotná
**mám v plánu přidělat další, proto je to takto rozhozené
*/
void bomberguy()
{
    /*
    **zde je deklarováno všecko potřebné
    */
    char input[3];
    int stav = 0;

    int hrac_x = 1;
    int hrac_y = 1;

    int bomba_x = 0;
    int bomba_y = 0;

    int odpocet = 0;

    int RNG_number = 0;
    int lvl_PowerUp = 0;
    int score = 0;
    /*
    **toto je hrací mapa, char se mi sral, takže pozice jsou zadány pomocí čísel
    **které jsou pak přetypovaný přislušnými znaky
    **takto mapa vypadá pouze na při prvním vypsání, při pohybu se přepisují
    */
    int array[21] [21] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7} ,
        {7, 1, 0, 0, 5, 0, 0, 0, 5, 0, 0, 5, 5, 5, 0, 0, 5, 0, 5, 0, 7} ,
        {7, 0, 0, 5, 5, 0, 5, 0, 5, 0, 5, 0, 0, 0, 0, 5, 7, 5, 7, 5, 7} ,
        {7, 0, 5, 5, 0, 0, 5, 0, 5, 7, 0, 0, 5, 5, 5, 0, 5, 4, 5, 0, 7} ,
        {7, 5, 5, 5, 5, 0, 5, 0, 0, 5, 5, 0, 0, 0, 0, 5, 7, 5, 7, 5, 7} ,
        {7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 5, 0, 5, 0, 7} ,
        {7, 5, 0, 0, 0, 5, 5, 7, 7, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 0, 5, 0, 0, 5, 0, 0, 7, 7, 0, 5, 5, 5, 5, 5, 5, 5, 5, 7} ,
        {7, 0, 0, 5, 0, 5, 5, 5, 0, 0, 0, 7, 5, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 7, 5, 7, 0, 5, 0, 0, 7, 7, 0, 5, 5, 7, 5, 7, 5, 7, 5, 7} ,
        {7, 5, 5, 5, 0, 0, 5, 7, 5, 7, 7, 7, 5, 5, 0, 5, 0, 5, 0, 5, 7} ,
        {7, 5, 5, 5, 5, 0, 5, 7, 5, 4, 5, 7, 5, 0, 0, 0, 0, 0, 0, 0, 7} ,
        {7, 0, 5, 0, 5, 5, 5, 0, 7, 7, 7, 0, 5, 0, 0, 5, 0, 5, 0, 5, 7} ,
        {7, 5, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 0, 5, 7, 5, 0, 7} ,
        {7, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 0, 0, 0, 5, 5, 5, 5, 5, 7} ,
        {7, 5, 7, 5, 7, 5, 0, 5, 0, 7, 0, 5, 0, 5, 0, 5, 7, 0, 7, 5, 7} ,
        {7, 0, 5, 4, 5, 0, 5, 0, 5, 0, 5, 0, 0, 5, 7, 5, 0, 9, 0, 5, 7} ,
        {7, 5, 7, 5, 7, 5, 0, 5, 0, 7, 0, 0, 5, 0, 0, 5, 7, 0, 7, 5, 7} ,
        {7, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 0, 0, 5, 0, 5, 5, 5, 5, 5, 7} ,
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
    };

    /*
    **Hlavní while hry
    */
    while(stav == 0 || stav == 1)
    {
        /*
        **Tyto dva FORy tisknou hrací mapu
        */
        for(int j = 0;j != 21;j++)
        {
            for(int i = 0;i != 21;i++)
            {
                display(array[i][j]);   //tato funkce přetypovává a tiskne jednotlivé znaky
            }
            printf("\n");   //po každém řádku následuje mezera
        }
        /*
        **zde se načítá vstup od hráče
        **pak následují už jednotlivá pravidla hry
        */
        if(bombFlag != 2)
        {
            printf("Waiting for input\n");  
            scanf("%s", input);
        }
        else
        {
            sleep(1);
            input[0] = 'n';
        }
        
        /*
        **pokud se hráč nachází v explozi, tak umře
        */
        if(array[hrac_x][hrac_y] == 3)
        {
            printf("You died in expolosion\n");
            stav = 2;
        }
        /*
        **bombFlat == 2 => bomba vybuchla
        **Grafika výbucu muže být přepsána na prázdné políčko, nenachází-li se tam stěna mapy
        */
        if(bombFlag == 2)
        {
            RNG_number = RNG();
            if(RNG_number == 1)
            {
                array[bomba_x][bomba_y] = 4;
            }
            else
            {
                array[bomba_x][bomba_y] = 0;
            }
            if(lvl_PowerUp == 0)
            {
                if(array[bomba_x+1][bomba_y] != 7)
                {
                    array[bomba_x+1][bomba_y] = 0;
                }
                if(array[bomba_x-1][bomba_y] != 7)
                {
                    array[bomba_x-1][bomba_y] = 0;
                }
                if(array[bomba_x][bomba_y+1] != 7)
                {
                    array[bomba_x][bomba_y+1] = 0;
                }
                if(array[bomba_x][bomba_y-1] != 7)
                {
                    array[bomba_x][bomba_y-1] = 0;
                }
            }
            else
            {
                if(array[bomba_x+1][bomba_y] != 7)
                {
                    array[bomba_x+1][bomba_y] = 0;
                }
                if(array[bomba_x+2][bomba_y] != 7)
                {
                    array[bomba_x+2][bomba_y] = 0;
                }

                if(array[bomba_x-1][bomba_y] != 7)
                {
                    array[bomba_x-1][bomba_y] = 0;
                }
                if(array[bomba_x-2][bomba_y] != 7)
                {
                    array[bomba_x-2][bomba_y] = 0;
                }

                if(array[bomba_x][bomba_y+1] != 7)
                {
                    array[bomba_x][bomba_y+1] = 0;
                }
                if(array[bomba_x][bomba_y+2] != 7)
                {
                    array[bomba_x][bomba_y+2] = 0;
                }

                if(array[bomba_x][bomba_y-1] != 7)
                {
                    array[bomba_x][bomba_y-1] = 0;
                }
                if(array[bomba_x][bomba_y-2] != 7)
                {
                    array[bomba_x][bomba_y-2] = 0;
                }
            }
            bombFlag = 0;
        }

        /*
        **Zde je naprogramován pohyb postavičky
        **podle zadaného písmena se určí směr a následně se přepíše
        **aktualní políčko a políčko ve směru pohybu, tedy pokud to
        **mapa dovoluje (pokud tam je volné místo)
        **taky je zde implementovano pokládání bomby
        */

        switch(input[0])
        {
            
            case'a':    //posun do leva
                if(array[hrac_x-1][hrac_y] == 7)
                {
                    stav = 1;  
                }
                else if(array[hrac_x][hrac_y] == 2)
                {
                    array[hrac_x-1][hrac_y] = 1;
                    hrac_x--;
                }
                else if(array[hrac_x-1][hrac_y] == 4)
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x-1][hrac_y] = 1;
                    hrac_x--;
                    lvl_PowerUp++;
                }
                else if(array[hrac_x - 1][hrac_y] == 5)
                {
                    printf("Can not do that\n");
                }
                else if(array[hrac_x-1][hrac_y] == 9)
                {
                    printf("Congratulation, you win!!!\n");
                    stav = 2;
                }
                else
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x-1][hrac_y] = 1;
                    hrac_x--;
                }
            break;

            case'd':    //posun do prava
                if(array[hrac_x+1][hrac_y] == 7)
                {
                    stav = 1;
                }
                else if(array[hrac_x][hrac_y] == 2)
                {
                    array[hrac_x+1][hrac_y] = 1;
                    hrac_x++;
                }
                else if(array[hrac_x+1][hrac_y] == 4)
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x+1][hrac_y] = 1;
                    hrac_x++;
                    lvl_PowerUp++;
                }
                else if(array[hrac_x + 1][hrac_y] == 5)
                {
                    printf("Can not do that\n");
                }
                else if(array[hrac_x+1][hrac_y] == 9)
                {
                    printf("Congratulation, you win!!!\n");
                    stav = 2;
                }
                else
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x+1][hrac_y] = 1;
                    hrac_x++;
                }
            break;

            case 's':   //posun dolů
                if(array[hrac_x][hrac_y + 1] == 7)
                {
                    stav = 1;
                }
                else if(array[hrac_x][hrac_y] == 2)
                {
                    array[hrac_x][hrac_y+1] = 1;
                    hrac_y++;
                }
                else if(array[hrac_x][hrac_y+1] == 4)
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x][hrac_y+1] = 1;
                    hrac_y++;
                    lvl_PowerUp++;
                }
                else if(array[hrac_x][hrac_y + 1] == 5)
                {
                    printf("Can not do that\n");
                }
                else if(array[hrac_x][hrac_y + 1] == 9)
                {
                    printf("Congratulation, you win!!!\n");
                    stav = 2;
                }
                else
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x][hrac_y+1] = 1;
                    hrac_y++;
                }
            break;

            case 'w':   //posun nahoru
                if(array[hrac_x][hrac_y - 1] == 7)
                {
                    stav = 1;
                }
                else if(array[hrac_x][hrac_y] == 2)
                {
                    array[hrac_x][hrac_y-1] = 1;
                    hrac_y--;
                }
                else if(array[hrac_x][hrac_y-1] == 4)
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x][hrac_y-1] = 1;
                    hrac_y--;
                    lvl_PowerUp++;
                }
                else if(array[hrac_x][hrac_y - 1] == 5)
                {
                    printf("Can not do that\n");
                }
                else if(array[hrac_x][hrac_y - 1] == 9)
                {
                    printf("Congratulation, you win!!!\n");
                    stav = 2;
                }
                else
                {
                    array[hrac_x][hrac_y] = 0;
                    array[hrac_x][hrac_y-1] = 1;
                    hrac_y--;
                }
            break;

            case 'f':   //položení bomby
                array[hrac_x][hrac_y] = 2;
                bomba_x = hrac_x;
                bomba_y = hrac_y;
                bombFlag = 1;
                score++;
            break;

            case 'n':
                /*
                **toto je case pro kolo ale bez žádné akce
                **používá se to počas exploze bomby
                */
            break;

            default:    //neznámý příkaz
                printf("I am in default input: %c\n", input[0]);
                if(input[0] != '\n')
                {
                    stav = -1;
                }
            break;
        }

        /*
        **Bomba byla položena, takže začíná odpočet
        **odpocet == 3 => bomba muže vybuchnout
        **radius výbucu se přepíše na 0, pouze pokud není políčko 7 (stěna mapy)
        */
        if(bombFlag == 1)
        {
            odpocet++;
            if(odpocet == 3)
            {
                bombFlag = 2;
                odpocet = 0;
                array[bomba_x][bomba_y] = 3;
                if(lvl_PowerUp == 0)
                {
                    if(array[bomba_x+1][bomba_y] != 7)
                    {
                        array[bomba_x+1][bomba_y] = 3;
                    }   
                    if(array[bomba_x-1][bomba_y] != 7)
                    {
                        array[bomba_x-1][bomba_y] = 3;
                    }
                    if(array[bomba_x][bomba_y+1] != 7)
                    {
                        array[bomba_x][bomba_y+1] = 3;
                    }
                    if(array[bomba_x][bomba_y-1] != 7)
                    {
                        array[bomba_x][bomba_y-1] = 3;
                    }
                }
                else
                {
                    if(array[bomba_x+1][bomba_y] != 7)
                    {
                        array[bomba_x+1][bomba_y] = 3;
                    }
                    if(array[bomba_x+2][bomba_y] != 7)
                    {
                        array[bomba_x+2][bomba_y] = 3;
                    }

                    if(array[bomba_x-1][bomba_y] != 7)
                    {
                        array[bomba_x-1][bomba_y] = 3;
                    }
                    if(array[bomba_x-2][bomba_y] != 7)
                    {
                        array[bomba_x-2][bomba_y] = 3;
                    }

                    if(array[bomba_x][bomba_y+1] != 7)
                    {
                        array[bomba_x][bomba_y+1] = 3;
                    }
                    if(array[bomba_x][bomba_y+2] != 7)
                    {
                        array[bomba_x][bomba_y+2] = 3;
                    }

                    if(array[bomba_x][bomba_y-1] != 7)
                    {
                        array[bomba_x][bomba_y-1] = 3;
                    }
                    if(array[bomba_x][bomba_y-2] != 7)
                    {
                        array[bomba_x][bomba_y-2] = 3;
                    }
                }
            }
        }
    }
    lvl_PowerUp = lvl_PowerUp * 100;
    score = score + lvl_PowerUp;
    printf("Your score: %d\n", score);
    return;
}

/*
**zde se přetypovává a tiskne jednotlivá políčka mapy
*/

void display(int pozice)
{
    /*volné místo*/
    if(pozice == 0)
    {
        printf(" ");
    }
    /*hrac*/
    else if(pozice == 1)
    {
        printf("T");
    }
    /*polozena bomba*/
    else if(pozice == 2)
    {
        printf("A");
    }
    /*efect*/
    else if(pozice == 3)
    {
        printf("X");
    }
    /*powe up*/
    else if(pozice == 4)
    {
        printf("B");
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
