/*Autor: Václav Doleček*/
/*sifrovací tentonoc*/
/*Verze 0.1*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*deklarace funkci*/
void sifrovac(int klic);

void odsifrovac(int klic);

/*main netreba dalsich infomaci*/
int main()
{
  int klic = 3; //sifrovaci/desifrovaci klic
  char vstup[15];

  /*načítání vstupu a ukladani do promněnné vstup*/
  scanf("%s", vstup);

  if(strcmp(vstup, "zasifrovat") == 0)
    {
      printf("\n");

      /*volání sifrovaci funkce*/
      sifrovac(klic);
    }

  else if(strcmp(vstup, "desifrovat") == 0)
    {
      printf("\n");

      /*volani odsifrovaci funkce*/
      odsifrovac(klic);
    }

  else if(strcmp(vstup, "help") == 0)
    {
      printf("Vítá Vás šifrovač od firmy UniSoftCorn\n");
      printf("\nzašifrování:\n");
      printf("Prikaz ->zasifrovat \"co chci zašifrovat\"<- \n");
      printf("\nDešifrování:\n");
      printf("Přikaz ->desifrovat \"co chci dešifrovat\"<- \n");
      printf("\nPište pouze to co je mezi -><-\n");
      printf(" Děkujeme že využíváte naše produkty a do příště nashledanou\n");
    }

  else
    {
      printf("%s", vstup);
      printf(" je neznamý příkaz\n");
      printf("Nevíte si rady? zkuste ->help<-\n");
      printf("Pište pouze to co je mezi -><-\n");
    }

  return 0;
}

/*implementace funkci*/
void sifrovac(int klic)
{
  int pis = 0; //pismeno
/*projede string az na konec*/
  while((pis = getchar()) != '\n' )
    {
      /*zmeni ASCII cislo*/
      pis = pis + klic;
      /*Vypise pismeno podle noveho ASCII cisla*/
      putchar(pis);
    }
  printf("\n");
}

void odsifrovac(int klic)
{
  int pis = 0; //pismeno
/*projede string az na konec*/
  while((pis = getchar()) != '\n' )
    {
      /*zmeni ASCII cislo*/
      pis = pis - klic;
      /*Vypise pismeno podle noveho ASCII cisla*/
      putchar(pis);
    }
  printf("\n");
}

/*konec*/
