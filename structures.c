#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

//initListeSite
/* elle creer une liste vide et retourne un pointeur sur cette ListeSite*/
ListeSite* initListeSite()
{
    ListeSite* liste=(ListeSite*)malloc(sizeof(ListeSite));
    liste->tete=NULL;
    liste->fin=NULL;
    return (liste);
}



//appendSite
/* elle prend en parametre les informations d'un site et la liste */
void appendSite(char* siteName, char* username, char* password, ListeSite *liste)
{
     // creation du nouveau site
    Site* newSite=(Site*)malloc(sizeof(Site));
    //controle des pointeurs
    if(newSite==NULL ||  liste==NULL)
    {
        puts("ArgumentERROR or AllocationERROR in appendSite");
        exit(EXIT_FAILURE);
    }
    //remplissage des informations du site
    strcpy(newSite->siteName,siteName);
    strcpy(newSite->username,username);
    strcpy(newSite->password,password);
    newSite->next=NULL;
    //insertion dans la liste a la queue
    if(liste->fin==NULL)
    {
        liste->tete=newSite;
        liste->fin=newSite;
    }
    else
    {
        Site *currentSite=liste->fin;
        currentSite->next=newSite;
        liste->fin=newSite;
    }
}
//seachSite
/*searchSite est une fonction qui prend en parametre
-le nom du site
-liste
elle renvoit
-  NULLsi le site n'est pas dans la liste
-  un pointeur vers le site
*/
//delSite prend en parametre le nom du site et la liste
Site* searchSite(char* siteName,ListeSite* liste)
{
    //controle des parametre
    if(siteName==NULL ||liste==NULL)
    {
        puts("ArgumentERROR in searchSite");
        exit(EXIT_FAILURE);
    }
    Site* currentSite=liste->tete;
    while(currentSite!=NULL)
    {
        if(strcmp(siteName,currentSite->siteName)==0)
            return(currentSite);
        currentSite=currentSite->next;
    }
    return NULL;
}
//delSite
/* cette procedure recherche un site dans la liste
-le  supprime si il le trouve
-signale un erreur dns le cas contraire*/
void delSite(char* siteName,ListeSite* liste)
{
     //controle des parametre
    if(siteName==NULL ||liste==NULL)
    {
        puts("ArgumentERROR in delSite");
        exit(EXIT_FAILURE);
    }
    //recherche du site
    Site* currentSite=liste->tete;
    Site* previous=NULL;
    int continuer=1;
    while(currentSite!=NULL && continuer)
    {
        if(strcmp(siteName,currentSite->siteName)==0)
            continuer=0;
        else
            {
                previous=currentSite;
                currentSite=currentSite->next;
            }
    }
    if(continuer==0)
    {
        if(previous==NULL)
            liste->tete=currentSite->next;
        else
            previous->next=currentSite->next;
        free(currentSite);
    }
    else
        puts("ArgumentERROR in delSite");
}
// printSites()
/* cette fonction prends en parametre la liste et l'affiche*/
void printSites(ListeSite* liste)
{
    Site* currentSite=liste->tete;
    while(currentSite!=NULL)
    {
        printf("    %s:\n",currentSite->siteName);
        printf("        -username=%s\n",currentSite->username);
        printf("        -password=%s\n",currentSite->password);
        currentSite=currentSite->next;
    }
}
//freeSites()
/*cette fonction pemet de liberer toute l'espace memoire reserve pour l'implementation de la liste*/
void freeSites(ListeSite* sites)
{
    char *siteName;
    Site* currentsite=sites->tete;
    while(currentsite != NULL)
    {
        siteName=currentsite->siteName;
        currentsite=currentsite->next;
        delSite(siteName,sites);
    }
    free(sites);
}
/******************************************************************************************************/

//initListeUser
/* elle creer une liste vide et retourne un pointeur sur cette ListeUser*/
ListeUser* initListeUser()
{
    ListeUser* liste=(ListeUser*)malloc(sizeof(ListeUser));
    liste->tete=NULL;
    liste->fin=NULL;
    return (liste);
}
//appendSite
/* elle prend en parametre les informations d'un utilisateur et la liste */
void appendUser(char* username, char* password, ListeSite* liste, ListeUser* users)
{
    //controle des parametre
    User* user= (User*)malloc(sizeof(User));
    if(users==NULL || user==NULL|| liste==NULL)
    {
        puts("ArgumentERROR in appendUser");
        exit(EXIT_FAILURE);
    }
    // creation d'un nouvel utilisateur
    user->liste=liste;
    strcpy(user->mainUsername,username);
    strcpy(user->mainPassword,password);
    //insertion dans la liste a la queue
    user->next=NULL;
    if(users->fin!=NULL)
    {
        User* currentUser=users->fin;
        currentUser->next=user;
        users->fin=user;
    }
    else
    {
        users->tete=user;
        users->fin=user;
    }
}
//searchUser
/*searchSite est une fonction qui prend en parametre
-le nom deel'utilisateur
-liste
elle renvoit
-  NULL si l'utiisateur n'est pas dans la liste
-  un pointeur vers le cet utilisateur dans le cas contraire
*/
User* searchUser(char* mainUsername,ListeUser* users)
{
    //controle des parametres
    if(mainUsername==NULL ||users==NULL)
    {
        puts("ArgumentERROR in searchUser");
        exit(EXIT_FAILURE);
    }
    User* currentUser=users->tete;
    while(currentUser!=NULL)
    {
        if(strcmp(mainUsername,currentUser->mainUsername)==0)
           return(currentUser);
        currentUser=currentUser->next;
    }
    return NULL;
}
//delSite
/* cette procedure recherche un site dans la liste
-le  supprime si il le trouve
-signale un erreur dns le cas contraire*/
void delUser(char* mainUsername,ListeUser* users)
{
     //controle des parametre
    if(mainUsername==NULL ||users==NULL)
    {
        puts("ArgumentERROR in searchUser");
        exit(EXIT_FAILURE);
    }
    //recherche de l'utilisateur
    User* currentUser=users->tete;
    User* previous=NULL;
    int continuer=1;
    while(currentUser!=NULL && continuer)
    {
        if(strcmp(mainUsername,currentUser->mainUsername)==0)
            continuer=0;
        else
            {
                previous=currentUser;
                currentUser=currentUser->next;
            }
    }
    if(continuer==0)
    {
        if(previous==NULL)
            users->tete=currentUser->next;
        else
            previous->next=currentUser->next;
        freeSites(currentUser->liste);
        free(currentUser);
    }
    else
        puts("ArgumentERROR in delUser");
}
// printUsers()
/* cette fonction prends en parametre la liste et l'affiche*/
void printUsers(ListeUser* users)
{
    User* currentUser=users->tete;
    while(currentUser!=NULL)
    {
        printf(" main username:::%s\n",currentUser->mainUsername);
        printf(" main password:::%s\n",currentUser->mainPassword);
        printSites(currentUser->liste);
        currentUser=currentUser->next;
    }
}
// freeUsers()
/* cette fonction permet de liberer toutes l'espace memoire utilise pour implementer la liste*/
void freeUsers(ListeUser* users)
{
    User* currentUser=users->tete;
    char mainUsername[50];
    while(currentUser!=NULL)
    {
        strcpy(mainUsername,currentUser->mainUsername);
        currentUser=currentUser->next;
        delUser(mainUsername,users);
    }
    free(users);
}
