#include <stdio.h>
#include <stdlib.h>
#include "fonctions_pieces.h"

void vider_buffer()
{
	while(getchar()!='\n');
}
int lire_int(char* message)
{
	int nbre,good1=0,good;
	do
	{
        system("clear");
		printf("%s",message);
		good=scanf("%d",&nbre);
		good1=(getchar()=='\n');
		if (good1==0)
		{
			vider_buffer();
			puts("INVALID INPUT");
			sleep(2);
		}
	}
	while(!(good && good1));
	return nbre;
}
