#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_DOLLAR			50
#define N_MAX_USER			5
#define N_MAX_BET			5

//playing game functions -----------------------------

extern	int n_user;
extern	int dollar[N_MAX_USER];						//dollars that each player has
extern	int bet[N_MAX_USER];						//current betting 

//player settiing
int configUser(void) {
	do{
		printf("Input the number of player (Max: 5):");
		scanf("%i", &n_user);

		if (n_user<1)
			printf("invalid input players (%d)\n", n_user);

		else if (n_user>5)
			printf("Too many players!\n");
	}
	while (n_user<1 || n_user>5);
}


//betting
int betDollar(void) {
	int i	;				//!!!!!!!!!!!!!!!!How can I control player's money??????!!!!!!!!!!
	
	for (i=0; i<N_MAX_USER; i++)
	dollar[i] = N_DOLLAR + bet[i];
	
	printf(" -> Your Betting (total: $%d) :", dollar[0]);
	scanf("%d", &bet[0]);
	if (bet[0]>dollar[0])
		printf("You only have $%d! Bet again!", dollar[0]);
	if (bet[0]<=0)
		printf("invalid input for betting $%d", bet[0]);
	srand((unsigned) time(NULL));
	
	for (i=1; i<n_user; i++)						// other user's betting money
		printf(" -> player%d bets %d (out of $%d)\n", i, 1+rand()%N_MAX_BET, dollar[i]);  
}
