#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
/*****************************************************************************************************/
        /**structure d'un site (14juillet 10h15)**/

/*un site se voit ici comme un element d'une liste chainée de site
 il est caractérisé par son nom, le nom d'utilisateur et le mot de passe */
 typedef struct Site Site;
 struct Site
 {
    char siteName[50];
    char username[50];
    char password[50];
    Site *next;
 };
        /**structure d'une liste de site**/
        /*il s'agit ici d'une liste chainée dont chaque case sera un site elle est caracterisée par un tete
        et une fin*/
typedef struct ListeSite ListeSite;
struct ListeSite
{
    Site* tete;
    Site* fin;
};
        /**structure d'un utilisateur**/
/*un utilisateur se voit ici comme un element d'une liste chainée d'utilisateur
 il est caracterise par un nom d'utilisateur principal et le mot de passe principal
 et un une liste de site et le l'adresse de l'utilisateur suivant */
 typedef struct User User;
 struct User
 {
    char mainUsername[50];
    char mainPassword[50];
    ListeSite* liste;
    User *next;
 };
        /**structure d'une liste d'utitilisateur**/
        /*il s'agit ici d'une liste chainée dont chaque case sera un utilisteur. elle est caracterisée par un tete
        et une fin*/
typedef struct ListeUser ListeUser;
struct ListeUser
{
    User* tete;
    User* fin;
};
 /** quelques fonctions et procedure pour manipuler la liste des site:
            - initListe() initialiser la liste de site
            -appendSite() pour ajouter un site
            -delSite() supprimer un site
            -searchSite rechercher un site
            -printSites()affichage de la liste
            -freeSites() liberation des espaces alloués**/
ListeSite* initListeSite();
void appendSite(char* siteName, char* username, char* password, ListeSite *liste);
Site* searchSite(char* siteName,ListeSite* liste);
void delSite(char* siteName,ListeSite* liste);
void printSites(ListeSite* liste);
void freeSites(ListeSite* sites);
/** quelques fonctions et procedure pour manipuler la liste des utilisateurs:
            - initListeUser() initialiser la liste des utilisateurs
            -appendUser() pour ajouter un utilisateur
            -delUser() supprimer un utilisateur
            -searchUser rechercher un utilisateur
            -printUsers()affichage de la liste
            -freeUsers() liberation des espaces alloués**/
ListeUser* initListeUser();
void appendUser(char* username, char* password, ListeSite* liste, ListeUser* users);
User* searchUser(char* mainUsername,ListeUser* liste);
void delUser(char* mainUsername,ListeUser* liste);
void printUsers(ListeUser* users);
void freeUsers(ListeUser* users);
#endif // STRUCTURES_H_INCLUDED
