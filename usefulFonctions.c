/*#include <stdio.h>
#include <stdlib.h>
typedef struct Carac Carac;
struct Carac
{
   char c;
   Carac* next;
};
typedef struct Chaine Chaine;
struct Chaine
{
    Carac* first;
    int taille;
    Carac* fin;
};
Chaine* init()
{
    Chaine* text=(Chaine*)malloc(sizeof(Chaine*));
    text->first=NULL;
    text->fin=NULL;
    text->taille=0;
    return text;
}
void append(Chaine* text,char ch)
{
    Carac* letter=(Carac*)malloc(sizeof(Carac*));
    if(carac==NULL || chaine==NULL)
    {
        puts("ERROR in append");
        exit(EXIT_FAILURE);
    }
    letter->c=ch;
    letter->next=NULL;
    if(text->fin==NULL)
    {
        text->fin=letter;
        text->first=letter;
    }
    else
    {
        Carac* actuel=text->fin;
        actuel->next=letter;
        text->fin=letter;
    }
    text->taille++;
}
void popchar(chaine* text)
{
    Carac *actuel=text->first;
    Carac *previously=NULL;
    while(actuel!=NULL)
    {
        previously=actuel;
        actuel=actuel->next;    }
    previously->next=NULL;
    free(actuel);
    text->taille--;
}
//sread()
/*il s'agit d'une fonction qui permert de lire de recupere une chaine de caractere
elle ne tient pas en compte les espaces et a une une taille limité pour eviter les buffer overflow
elleretourne un pointeur sur une chaine de caractere */
/*char* sread()
{
    char ch;
    int i;
    char *chaine;
    int good=1;
    ch=getchar();
    Chaine *text=init();
    while((ch!='\n') && good)
    {
        if(ch=' '|| ch='    ')
            good=0;
        else
        {
            append(text,ch);
            ch=getchar()
        }
    }
    chaine=(char*)malloc(((text->taille)+1)*sizeof(char*));
    Carac *actuel=text->first;
    for(i=0; i<(text->taille);i++)
    {
        *(chaine+i)=actuel->c;
        actuel=actuel->next;
    }
    while(text->taille!=0)
            popchar(text);
    return chaine;
}*/
        /**structure d'une donnee pour la lecture des chaines de caractere**/
typedef struct Carac Carac;
struct Carac
{
   char c;
   Carac* next;
};
typedef struct Chaine Chaine;
struct Chaine
{
    Carac* first;
    int taille;
    Carac* fin;
};
