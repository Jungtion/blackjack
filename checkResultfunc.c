#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX_USER			5

extern	int n_user;									//number of users
extern	int dollar[N_MAX_USER];						//dollars that each player has
extern	int bet[N_MAX_USER];						//current betting 
extern	int cardSum[N_MAX_USER];					//sum of the cards
extern	int gameEnd; 								//game end flag


//check result-------------------

int checkResult() {
	int i;
	
	//1. under - server's cardSum
	if(cardSum[n_user]<21)
	{
		for (i=0; i<n_user; i++)
		{
			if(i == 0)
			printf("	-> your result : ");
			
			else
			printf("	-> %d player's result : ', i");
			
			
			// bankruptcy
			if(cardSum[i]>21)				
			printf("Lose due to overflow! ($%d)\n", dollar[i]);
			
			//blackjack
			else if(cardSum[i] == 21)
			printf("BlackJack! Win! ($%d)\n", dollar[i]);
			
			else			//cardSum[i]<21
			{
				//player lose
				if(cardSum[i]<cardSum[n_user])
				{
					dollar[i] = dollar[i] - bet[i];
					printf("Lose! (sum: %d)	--> ($%d)\n", cardSum[i], dollar[i]);
				}
				
				//player win
				else if (cardSum[i] >= cardSum[n_user])
				{
					dollar[i] = dollar[i] + bet[i];
					printf("Win! (sum: %d)	-->	($%d)\n", cardSum[i], dollar[i]);
				}
				
				
			}
		}
	}
	
	//2. server blackjack
	else if(cardSum[n_user] == 21)
	{
		for (i=0; i<n_user; i++)
		{
			if(i==0)
			printf("	-> your result : ");
			
			else
			printf("	-> %d player's result : ', i");
			
			
			// bankruptcy
			if(cardSum[i]>21)				
			printf("Lose due to overflow! ($%d)\n", dollar[i]);
			
			//blackjack
			else if(cardSum[i] == 21)
			printf("BlackJack! Win! ($%d)\n", dollar[i]);
			
			//player lose
			else
			{
				dollar[i] = dollar[i] - bet[i];
				printf("Lose! (sum: %d)	--> ($%d)\n", cardSum[i], dollar[i]);
			}
			
		}
	}
	
	
	//3. server over
	else
	{
		for (i=0; i<n_user; i++)
		{
			if(i==0)
			printf("	-> your result : ");
			
			else
			printf("	-> %d player's result : ', i");
			
			//bankruptcy
			if(cardSum[i]>21)
			printf("Lose due to overflow! ($%d)\n", dollar[i]);
			
			//blackjack
			else if(cardSum[i] == 21)
			printf("BlackJack! Win! ($%d)\n", dollar[i]);
			
			//player win
			else
			{
				dollar[i] = dollar[i] + bet[i];
				printf("Win! (sum: %d)	--> ($%d)\n", cardSum[i], dollar[i]);
			}
		}
		
	}
	
	//no money
	
	for(i=0; i<n_user; i++)
	{
		if (dollar[i]==0)
		{
			gameEnd = 1;
			break;
		}
	}

	
}

int checkWinner() {
	int i;
	int winner_money;
	int winner;
	
	printf("\n\n\n-----------------------------------\n\n\n");
	printf("--------------------------------\n");
	printf("--------------------------------\n");
	printf("--------------------------------\n");
	printf("Game End! Your Money is $%d\n", dollar[0]);
	
	//other player's money
	if(n_user>2)
	{
		for (i=1; i<n_user; i++)
		{
			printf("Player %d's Money is	$%d\n", dollar[i]);
		}
	}
	
	winner_money = dollar[0];
	for(i=0; i<n_user; i++)
	{
		if(winner_money < dollar[i])
		{
			winner_money = dollar[i];
			winner = i;
		}
	}
	
	if (winner == 0)
	printf("You win!\n");
	
	else
	printf("player %d win\n", winner);
	
}
