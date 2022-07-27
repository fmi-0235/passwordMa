#ifndef FONCTIONALITES_H_INCLUDED
#define FONCTIONALITES_H_INCLUDED
char* generatePassword();
int mk_record(ListeSite* sites);
int modify_record(ListeSite* sites);
int destroy(ListeSite* sites);
int change(User *user, ListeUser* users);
#endif // FONCTIONALITES_H_INCLUDED
