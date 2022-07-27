#ifndef FONCTIONS_SYS_H_INCLUDED
#define FONCTIONS_SYS_H_INCLUDED
/** il s'agit des fonction lies au systeme uniquement et non aux fonctionnalités que le systeme offre**/
/** -la connection
    -l'affichage de l'interface de connection
    -affichage des fonctionnalités
    -l'enregistrement des donnees
    -lectures de donnees
    **/
void vider_buffer();
int save(ListeUser* users);
ListeUser* readf();
void print_accueil();
void print_menu();
User*  subscribe(ListeUser* users);
User*  connect(ListeUser *users);
User* which_action(ListeUser *users);
void main_proces(ListeUser* users, User* user);
#endif // FONCTIONS_SYS_H_INCLUDED
