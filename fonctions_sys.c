#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/termios.h>
#include <unistd.h>
#include "structures.h"
#include "fonctions_pieces.h"
#include "fonctionalites.h"
#include "fonctions_sys.h"


// save():
/* cette fonction permet de sauvegarder les  donnees en fin de programme  dans un fichier txt
    elle prends en parametre la liste des users.*/
/* les enregistrement seront comme suit:
##### mainusername1 mainpassword1 ***** siteName1 username1 password1 ***** siteName2 username2 password2 ..... siteNameN usernameN passwordN #####
##### mainusername2 mainpassword2 ***** siteName1 username1 password1 ***** siteName2 username2 password2 ..... siteNameN usernameN passwordN #####
.     .             .             .     .         .         .         .     .         .         .         ..... .         .         .         .
.     .             .             .     .         .         .         .     .         .         .         ..... .         .         .         .
##### mainusernameN mainpasswordN ***** siteName1 username1 password1 ***** siteName2 username2 password2 ..... siteNameN usernameN passwordN #####*/
int save(ListeUser* users)
{
    FILE* fichier = NULL;
    fichier=fopen( "passwordM_data.txt","w");
    // verifions que le fichier a bienété ouvert
    if (fichier == NULL)
    {
        puts(" in save OpenFileERROR: l'ouverture du fichier de sauvegarde en mode écriture a échoué");
        return -1;//le programme s'arrete dans ce cas
    }
    User *currentUser=users->tete ;
    ListeSite* liste= NULL;
    Site *currentSite=NULL;
    // on va parcourir la liste pour enregistrer
    while ( currentUser != NULL)
    {
        fprintf(fichier,"##### ");
        fprintf( fichier, "%s ", currentUser->mainUsername);
        fprintf( fichier, "%s ", currentUser->mainPassword);
        //parcours de la liste des sites pour enregistrer toutes les informmations liées aux sites
        liste= currentUser->liste;
        currentSite = liste->tete;
        while(currentSite != NULL)
        {
            fprintf(fichier,"***** ");
            fprintf(fichier, "%s %s %s ", currentSite->siteName, currentSite->username, currentSite->password);
            currentSite=currentSite->next;
        }
        currentUser=currentUser->next;
        //fin de l'enregistrement pour cet utilisateur
        fprintf(fichier, "#####\n");
    }
    //fin de l'enreigstrement
    fclose(fichier);
    return 0;
}
//read()
/* cette fonction permet de transcrit le contenu du fichier passwordM_data.txt en une ListeUser exploitable aucours du fichier,
elle ne prends pas de prametre et renvoit une ListeUser*/
/* contenu de passwordM_data:

##### mainusername1 mainpassword1 ***** siteName1 username1 password1 ***** siteName2 username2 password2 ..... siteNameN usernameN passwordN #####
##### mainusername2 mainpassword2 ***** siteName1 username1 password1 ***** siteName2 username2 password2 ..... siteNameN usernameN passwordN #####
.     .             .             .     .         .         .         .     .         .         .         ..... .         .         .         .
.     .             .             .     .         .         .         .     .         .         .         ..... .         .         .         .
##### mainusernameN mainpasswordN ***** siteName1 username1 password1 ***** siteName2 username2 password2 ..... siteNameN usernameN passwordN #####*/

ListeUser* readf()
{
    //ouverture du fichier
    FILE *fichier=NULL;
    fichier= fopen("passwordM_data.txt", "r");
    if (fichier == NULL)
    {
        puts("in read() OpenFileERROR le fichier n'a pas pu etre");
        exit(EXIT_FAILURE);
    }
    // creations de la liste des utilisateurs
    ListeUser *users=initListeUser();
    ListeSite* liste=NULL;

    int lire_user=0;
    int lire_site=0;
    /** ceci implique une taille limite **/
    char mainusername[50];
    char mainpassword[50];
    char username[50];
    char siteName[50];
    char password[50];
    char special[6];
    // test si le fichier n'est pas vide
    if(fscanf(fichier, "%s", special)!= EOF )
        {lire_user=1;getc(fichier);}
    while( lire_user )
    {
        fscanf(fichier,"%s", mainusername);
        getc(fichier);
        fscanf(fichier, "%s", mainpassword);
        getc(fichier);
        liste=initListeSite();//creation de la liste des site de cette user
        // on test la liste n'est pas vide

        fscanf(fichier, "%s", special);
        if(strcmp(special,"*****")==0)
            lire_site=1;
        while(lire_site)
        {
            fscanf(fichier,"%s", siteName);
            getc(fichier);
            fscanf(fichier,"%s", username);
            getc(fichier);
            fscanf(fichier,"%s", password);
            getc(fichier);
            appendSite(siteName,username,password,liste);
            //on verifie si c'etait le dernier liste
            fscanf(fichier,"%s",special);
            if(strcmp(special,"#####")==0)
                lire_site=0;
        }
        appendUser(mainusername,mainpassword,liste,users);

        //on teste si ce n'est pas le dernier utilisateur
        if(fscanf(fichier, "%s", special)== EOF )
            {lire_user=0;getc(fichier);}
    }
    fclose(fichier);
    return (users);
}
// print_accueil()
/* cette fonction traite du premier affichage a l'écran*/
void print_accueil()
{
    puts("!=============================================================================!");
    puts("!-----------------------------PASSWORD MANAGERS-------------------------------!");
    puts("!=============================================================================!");
    puts("!________________________1-> SE CONNECTER ____________________________________!");
    puts("!=============================================================================!");
    puts("!________________________2-> CREER UN NOUVEAU COMPTE__________________________!");
    puts("!=============================================================================!");
}
// print_menu()
/* cette fonction traitede l'affichage du menu  a l'écran*/
void print_menu()
{
    puts("!=============================================================================!");
    puts("!-----------------------------PASSWORD MANAGERS-------------------------------!");
    puts("!=============================================================================!");
    puts("!-----------------# 1 - CONSULTER TOUS VOS ENREGISTREMENTS                    !");
    puts("!=============================================================================!");
    puts("!-----------------# 2 - FAIRE UN ENREGISTREMENT                               !");
    puts("!=============================================================================!");
    puts("!-----------------# 3 - MODIFIER UN ENREGITREMENT                             !");
    puts("!=============================================================================!");
    puts("!-----------------# 4 - SUPPRIMER UN ENREGISTREMENT                           !");
    puts("!=============================================================================!");
    puts("!-----------------# 5 - MODIFIER LES INFORMATIONS DE VOTRE COMPTE             !");
    puts("!=============================================================================!");
    puts("!-----------------# 6 - OBTENIR UN MOT DE PASSE                               !");
    puts("!=============================================================================!");
    puts("!-----------------# 7 - ENREGISTRER LES MODIFICATION ET SE DECONNECTER        !");
    puts("!=============================================================================!");
}
//
/* */
User*  subscribe(ListeUser* users)
{
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
        puts("|CREER SON COMPTE                                         CRTL+C POUR QUITTER |");
        puts("!=============================================================================!");
        printf("NOM D'UTILISATEUR: ");
        scanf("%s",username);
        vider_buffer();
        if((searchUser(username,users)!=NULL ) || (strcmp(username,"#####")==0) || (strcmp(password,"*****")==0))
        {
            nonValid=1;
            puts("PASSWORD_MANAGER~~~~~~~~| : CE NOM EXISTE DEJA ");
        }
    }
    while(nonValid!=0);
    do
        {
        system("clear");
        puts("!=============================================================================!");
        puts("|CREER SON COMPTE                                         CRTL+C POUR QUITTER |");
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
                printf("VOTRE MOT DE PASSE EST~~~~~~~~~( : %s\n",passwordA);
                strcpy(password,passwordA);
                free(passwordA);
               break;
            case 2:
                printf("PASSWORD_MANAGER~~~~~~~~( ; ");
                scanf("%s",password);
                if(strcmp(password,"#####")==0 || strcmp(password,"*****")==0)
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
    ListeSite* liste=initListeSite();
    appendUser(username,password,liste,users);
    system("clear");
    puts("!=============================================================================!");
    printf("|----------------------#BIENVENUE %s :)  \n",username);
    puts("!=============================================================================!");
    sleep(2);
    return (searchUser(username,users));
}
//
/* */
//
/* */
User*  connect(ListeUser *users)
{
        char username[50];
        char password[50];
        int Ngranted=1;
        int i=0;
        User* utilisateur=NULL;
        do
        {
            system("clear");
            puts("!=============================================================================!");
            puts("|SE CONNECTER                                             CRTL+C POUR QUITTER |");
            puts("!=============================================================================!");
            printf("--------------------# NOM D'UTILISATEUR :  ");
            scanf("%s",username);
            vider_buffer();
            utilisateur=searchUser(username,users);
            if(utilisateur==NULL)
            puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:::WRONG USERNAME::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
            sleep(1);
        }
        while(utilisateur==NULL);
        while(Ngranted!=0)
        {
            if (i==3)
            {
                puts("!***************************DECONEXION :: WRONG PASSWORD (3 TIMES)************!");
                exit(EXIT_FAILURE);
            }
            system("clear");
            puts("!=============================================================================!");
            puts("|SE CONNECTER                                             CRTL+C POUR QUITTER |");
            puts("!=============================================================================!");
            printf("-----------------------# MOT DE PASSE :  ");
            scanf("%s",password);
            vider_buffer();
            Ngranted=strcmp(password, utilisateur->mainPassword);
            i++;
        }

        system("clear");
        puts("!=============================================================================!");
        printf("|----------------------#BIENVENUE %s :) \n",username);
        puts("!=============================================================================!");
        return utilisateur;
}
User* which_action(ListeUser *users)
{
    int choix;
    int boucle=1;
    User* utilisateur;
    while(boucle)
    {
        print_accueil();
        printf("PASSWORD_MANAGER~~~~~~( : ");
        scanf("%d", &choix);
        vider_buffer();
        switch(choix)
        {
            case 1:
                boucle=0;
                utilisateur=connect(users);
                break;
            case 2:
                boucle=0;
                utilisateur=subscribe(users);
                break;
            default :
                puts("!!!!!!!!!!!!!!!ERROR: YOU SHOULD ENTER 1 OR 2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                sleep(3);
                system("clear");
        }
    }
    return utilisateur;
}
void main_proces(ListeUser* users, User* user)
{
    int choix;
    int continuer=1;
    char *password;
    do
    {
        print_menu();
        puts("!==============================PASSWORD_MANAGER===============================!");
        printf("--:%s-----------#  ",user->mainUsername);
        scanf("%d", &choix);
        vider_buffer();
        switch(choix)
        {
            case 1:
                system("clear");
                puts("!============================VOS ENREGISTREMENTS==============================!");
                printSites(user->liste);
                puts("! ENTER ::MENU                               CTRL C POUR QUITTER!");
                printf("--:%s-----------#  ",user->mainUsername);
                getchar();
                puts("!=============================================================================!");
                break;
            case 2:
                mk_record(user->liste);
                break;
            case 3:
                modify_record(user->liste);
                break;
            case 4:
                destroy(user->liste);
                break;
            case 5:
                change(user,users);
                break;
            case 6:
                password=generatePassword();
                printf("------# VOTRE MOT DE PASSE EST: %s\n", password);
                sleep(2);
                free(password);
                break;
            case 7:
                continuer=0;
                puts("*****************************    DECONNEXION    *******************************");
                break;
            default:
                puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! WRONG    MENU !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
                sleep(2);
        }
        system("clear");
    }
    while(continuer);
}
