#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "fonctions_sys.h"
#include "fonctionalites.h"

int main()
{
    //declaration des variables
    ListeUser *users;
    User* utilisateur;
   //chargement des donnee en memoire vive
    users=readf();
   //authentification et connexion|| subscription
    utilisateur=which_action(users);
   //procurer des services
    main_proces(users,utilisateur);
   // sauvegarde des donnéé
    save(users);
   //liberation de l'espace memoire
   freeUsers(users);
}
