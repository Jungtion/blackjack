#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52

extern	int CardTray[N_CARDSET*N_CARD];

//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {							
	int i	;
	int j=-2	;
	
	for (i=0;i<N_CARDSET*N_CARD;i++)
	{
		CardTray[i]=rand()%(N_CARDSET*N_CARD);
		for (j=0;j<i;j++)
		{
			//if jth cardtray == ith cardtray
			if (CardTray[i] == CardTray[j])
			{
				i--;
				break;
			}
		}		
	}
	
	printf(" --> card is mixed and put into the tray\n");
}

