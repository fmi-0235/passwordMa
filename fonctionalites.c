#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "fonctions_pieces.h"
#include "structures.h"
#include "fonctionalites.h"
// foncionalité 6 du menu
char* generatePassword()
{
	int lenpassword=0, compteur;
	char* tableCaractere="0123456789azertyuiopmlkjhgfdsqwxcvbnQSDFGHJKLMNBVCXWAZERTYUIOP";
	char* password=NULL;
	srand(time(NULL));
	lenpassword=lire_int("LONGUEUR DU MOT DE PASSE------|");
	password=(char*)malloc((lenpassword)*sizeof(char));
	for(compteur=0;compteur<lenpassword;compteur++)
		*(password+compteur)=tableCaractere[rand()%62];
	//*(password+(lenpassword+1))='\0';
	return password;
}
// mk_record()
int mk_record(ListeSite* sites)
{
    char siteName[50];
    char username[50];
    char password[50];
    char *passwordA;
    int nonValid=0;
    int choix;
    do
    {
        system("clear");
        nonValid=0;
        puts("!=============================================================================!");
        puts("|FAIRE UN ENREGISTREMENT                                  #####: MENU         |");
        puts("!=============================================================================!");
        printf("------------------# NOM DU SITE: ");
        scanf("%s",siteName);
        vider_buffer();
        if((searchSite(siteName,sites)!=NULL ) || (strcmp(siteName,"*****")==0))
        {
            nonValid=1;
            puts("PASSWORD_MANAGER~~~~~~~~| : CE NOM EXISTE DEJA ");
        }
        if(strcmp(siteName,"#####")==0 )
            return -1;
    }
    while(nonValid!=0);
    nonValid=0;
    do
    {
        system("clear");
        nonValid=0;
        puts("!=============================================================================!");
        puts("|FAIRE UN ENREGISTREMENT                                  #####: MENU         |");
        puts("!=============================================================================!");
        printf("------------------# NOM DE L'UTILISATEUR: ");
        scanf("%s",username);
        vider_buffer();
        if(strcmp(username,"*****")==0)
        {
            nonValid=1;
            puts("PASSWORD_MANAGER~~~~~~~~| : CE NOM EXISTE DEJA ");
        }
        if(strcmp(username,"#####")==0 )
            return -1;
    }
    while(nonValid!=0);
    nonValid=0;
    do
        {
        system("clear");
        nonValid=0;
        puts("!=============================================================================!");
        puts("|FAIRE UN ENREGISTREMENT                                  #####: MENU         |");
        puts("!=============================================================================!");
        puts("------------# 1 MOT DE PASSE ALEATOIRE");
        puts("------------# 2 ENTRER SON MOT DE PASSE");
        scanf("%d",&choix);
        vider_buffer();
        switch(choix)
        {
            case 1:
                nonValid=0;
                passwordA=generatePassword();
                strcpy(password,passwordA);
                printf("VOTRE MOT DE PASSE EST~~~~~~~~~( : %s\n",password);
                free(passwordA);
               break;
            case 2:
                printf("PASSWORD_MANAGER~~~~~~~~( ; ");
                scanf("%s",password);
                if( strcmp(password,"*****")==0)
                {
                    nonValid=1;
                    puts("PASSWORD_MANAGER~~~~~~~~| : MOT DE PASSE NON AUTORISE ");
                }
                else
                    nonValid=0;
                if(strcmp(siteName,"#####")==0 )
                    return -1;
                break;
             default:
                nonValid=1;
                puts("!!!!!!!!!!!!!!!ERROR: YOU SHOULD ENTER 1 OR 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        }
        sleep(2);
        }
    while(nonValid!=0);
    appendSite(siteName,username,password,sites);
    puts("!=============================================================================!");
    puts("--------------------------ENREGISTREMENT EFFECTUE-----------------------------!");
    puts("!=============================================================================!");
    sleep(2);
    return 0;
}
int modify_record(ListeSite* sites)
{
       char siteName[50];
    char username[50];
    char password[50];
    char *passwordA;
    int nonValid=0;
    int choix;
    Site* site=NULL;
    do
    {
        system("clear");
        nonValid=0;
        puts("!=============================================================================!");
        puts("|MODIFIER UN ENREGISTREMENT                               ##### :MENU         |");
        puts("!=============================================================================!");
        printf("------------------# NOM DU SITE: ");
        scanf("%s",siteName);
        vider_buffer();
        site=searchSite(siteName,sites);
        if(site==NULL )
        {
            nonValid=1;
            puts("PASSWORD_MANAGER~~~~~~~~| : SITE INEXISTANT ");
        }
    }
    while(nonValid!=0);
    if(strcmp(username,"#####")==0 )
            return-1;
    nonValid=0;
    do
    {
        system("clear");
        nonValid=0;
        puts("!=============================================================================!");
        puts("|MODIFIER UN ENREGISTREMENT                               ##### :MENU         |");
        puts("!=============================================================================!");
        printf("------------------# NOM DE L'UTILISATEUR: ");
        scanf("%s",username);
        vider_buffer();
        if( strcmp(username,"*****")==0)
        {
            nonValid=1;
            puts("PASSWORD_MANAGER~~~~~~~~| : NOM RESERVE AU SYSTEME ");
        }
    }
    while(nonValid!=0);
    if(strcmp(siteName,"#####")==0 )
            return-1;
    nonValid=0;
    do
        {
        system("clear");
        puts("!=============================================================================!");
        puts("|MODIFIER UN ENREGISTREMENT                               ##### :MENU         |");
        puts("!=============================================================================!");
        puts("------------# 1 MOT DE PASSE ALEATOIRE");
        puts("------------# 2 ENTRER SON MOT DE PASSE");
        scanf("%d",&choix);
        vider_buffer();
        switch(choix)
        {
            case 1:
                nonValid=0;
                passwordA=generatePassword();
                strcpy(password,passwordA);
                printf("VOTRE MOT DE PASSE EST~~~~~~~~~( : %s\n",password);
                free(passwordA);
               break;
            case 2:
                printf("PASSWORD_MANAGER~~~~~~~~( ; ");
                scanf("%s",password);
                if(strcmp(password,"*****")==0)
                {
                    nonValid=1;
                    puts("PASSWORD_MANAGER~~~~~~~~| : MOT DE PASSE NON AUTORISE ");
                }
                else
                    nonValid=0;
                break;
             default:
                nonValid=1;
                puts("!!!!!!!!!!!!!!!ERROR: YOU SHOULD ENTER 1 OR 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        }
        sleep(2);
        }
    while(nonValid!=0);
    if(strcmp(password,"#####")==0 )
            return-1;
    strcpy(site->username, username);
    strcpy(site->password, password);
    puts("!=============================================================================!");
    puts("----------------------------MODIFICATION TERMINE------------------------------!");
    puts("!=============================================================================!");
    sleep(2);
    return 0;
}
int destroy(ListeSite* sites)
{
    int nonValid=0;
    char siteName[50];
     do
    {
        nonValid=0;
        system("clear");
        puts("!=============================================================================!");
        puts("|SUPPRIMER UN ENREGISTREMENT                              ##### :MENU         |");
        puts("!=============================================================================!");
        printf("------------------# NOM DU SITE: ");
        scanf("%s",siteName);
        vider_buffer();
        if(searchSite(siteName,sites)==NULL )
        {
            nonValid=1;
            puts("PASSWORD_MANAGER~~~~~~~~| : SITE INEXISTANT ");
        }
        if(strcmp(siteName,"#####")==0 )
            return -1;
        sleep(2);
    }
    while(nonValid!=0);
    delSite(siteName, sites);
    puts("!=============================================================================!");
    puts("----------------------------SUPPRESSION   TERMINE-----------------------------!");
    puts("!=============================================================================!");
    return 0;
}
int change(User *user, ListeUser* users)
{
    int nonValid=0;
    char username[50];
    char password[50];
    char *passwordA;
    int choix;
     do
    {
        system("clear");
        nonValid=0;
        puts("!=============================================================================!");
        puts("|MODIFIER MES INFORMATIONS                                ##### :MENU         |");
        puts("!=============================================================================!");
        printf("------------------# NOUVEAU NOM D'UTILISATION: ");
        scanf("%s",username);
        vider_buffer();
        if((searchUser(username,users)!=NULL )|| strcmp(username,"*****")==0)
        {
            if((strcmp(username,user->mainUsername)!=0 )||( strcmp(username, "*****")==0 ))
            {
                nonValid=1;
                puts("PASSWORD_MANAGER~~~~~~~~| : CE NOM EXISTE DEJA ");
            }
        }
        if(strcmp(username,"#####")==0 )
            return -1;
        sleep(2);
    }
    while(nonValid!=0);
    nonValid=0;
    do
        {
        system("clear");
        puts("!=============================================================================!");
        puts("|MODIFIER MES INFORMATIONS                                ##### :MENU         |");
        puts("!=============================================================================!");
        puts("------------# 1 MOT DE PASSE ALEATOIRE");
        puts("------------# 2 ENTRER SON MOT DE PASSE");
        scanf("%d",&choix);
        vider_buffer();
        switch(choix)
        {
            case 1:
                nonValid=0;
                passwordA=generatePassword();
                strcpy(password,passwordA);
                printf("VOTRE MOT DE PASSE EST~~~~~~~~~( : %s",password);
                free(passwordA);
               break;
            case 2:
                printf("PASSWORD_MANAGER~~~~~~~~( ; ");
                scanf("%s",password);
                if(strcmp(password,"*****")==0)
                {
                    nonValid=1;
                    puts("PASSWORD_MANAGER~~~~~~~~| : MOT DE PASSE NON AUTORISE ");
                }
                else
                    nonValid=0;
                break;
             default:
                nonValid=1;
                puts("!!!!!!!!!!!!!!!ERROR: YOU SHOULD ENTER 1 OR 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        }
        sleep(2);
        }
    while(nonValid!=0);
    if(strcmp(password,"#####")==0 )
            return-1;
    strcpy(user->mainUsername,username);
    strcpy(user->mainPassword, password);
    return 0;
}
