#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user;									//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards
int bet[N_MAX_USER];						//current betting 
int gameEnd = 0; 							//game end flag
int turnEnd = 0;							//turn end flag
int Num_of_Card;							//number of cards each player has

//some utility functions

//get an integer input from standard input (keyboard)
//return : input integer value
//         (-1 is returned if keyboard input was not integer)
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}


////card processing functions ----------------------



////card array controllers -------------------------------


int top = N_CARD-1	;

//get one card from the tray
int pullCard(void) {
	if (top <= 0)
	{
		gameEnd = 1;
		return -1;
	}
	
	return CardTray[top--];
}


////playing game functions -----------------------------

//configUser();

//betDollar();






//offering initial 2 cards
void offerCards(void) {
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int i	;
	
	printf("---------- CARD OFFERING ----------\n");
	printf("	server\t: X	");					//server's card
	printCard(cardhold[n_user][1]);
	printf("\n");
	
	
	printf("	you\t: ");						//your card
	printCard(cardhold[0][0]);
	printCard(cardhold[0][1]);
	printf("\n");
	
	
	if (n_user>1)								//user's card
		for(i=1; i<n_user; i++)
		{
			printf("	player%d\t: ", i);
			printCard(cardhold[i][0]);
			printCard(cardhold[i][1]);
			printf("\n");
		}
}

int getAction(void) {
	int i;
	
	if (cardSum[i]>=17)
	{
		printf("STAY!\n");
		
		turnEnd = 1;
	}

	else
	{
		printf("GO!\n");
		cardhold[i][Num_of_Card] = pullCard();
		Num_of_Card++;
	}	
}

int getActionServer(){
	
	if(cardSum[n_user] >= 17)
	{
		printf("STAY!\n");
		printf("[[[[[[[server result is.... %d ]]]]]]]", cardSum[n_user]);
		printf("\n\n\n");
	}
	
	else 
	{
		printf("GO!\n");
    	cardhold[n_user][Num_of_Card] = pullCard();
	}
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0; i<cardcnt; i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user) {
	int j;
	
	cardSum[user] = 0;
	
	for (j=0; j<Num_of_Card; j++)
	{						
		cardSum[user] = cardSum[user] + getCardNum(cardhold[user][j], user);
	}
	
	if (user==n_user)			//server turn
	{
		//3. cardSum blackjack
		if(cardSum[n_user] == 21)
		{
			printf("Black jack! server win!!\n");
			printf("[[[[[[[server result is.... Blackjack ]]]]]]]");
			
			turnEnd = 1;
		}
		
		//2. cardSum over
		else if (cardSum[n_user] > 21)
		{
			printf("serever Dead (sum:%d)\n", cardSum[n_user]);
			printf("[[[[[[[server result is.... Overflow!! ]]]]]]]");
			
			turnEnd = 1;
		}
	}
	
	else if (user != 0)			//user turn
	{
		//3. cardSum blackjack
		if(cardSum[user] == 21)
		{
    	  dollar[user] = dollar[user] + bet[user] *2;
		  printf("Black jack! congratulation, you win!! --> +$%d ($%d)", bet[user]*2, dollar[user]);
		  
		  turnEnd = 1;
   		}
   
		//2. cardSum over
   		 else if (cardSum[user] > 21)
  		{
  			dollar[user] = dollar[user] - bet[user];
			printf("Dead (sum:%d) --> -$%d ($%d)", cardSum[user], bet[user], dollar[user]);
      
    	  turnEnd = 1;
  		}
	}
}

////check result-------------------------



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;

	int action;
	int round=1;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();
	
//	for (i=0;i<N_CARDSET*N_CARD;i++)								//this is for test************
//		printf("card %i : %i\n",i, CardTray[i]);		



	//Game start --------
	do {
		printf("----------------------------------------------\n");
		printf("------------Round %d----------------------\n", round);
		printf("----------------------------------------------\n\n");
		round++;
		
		cardSum[i] = 0;
		turnEnd = 0;
		
		printf("-----BETTING STEP-----\n");
		betDollar();
		offerCards(); //1. give cards to all the players
		
		if (gameEnd != 0)
      	{
      		printf("Card ran out of the tray!! finishing the game.");
        	continue;
      	}

		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		
		printf(">>> my turn --------\n");
		while (turnEnd == 0)
		{
			for(Num_of_Card=2; cardSum[0]<21; Num_of_Card++)
			{
				printUserCardStatus(0, Num_of_Card);
				calcStepResult(0);
			
					//printf("card sum is %d\t", cardSum[0]);			//This is for test*******Check cardSum
			
				if(cardSum[0] == 21)
				{
					dollar[0] = dollar[0] + bet[0] *2;
		 	 		printf("Black jack! congratulation, you win!! --> +$%d ($%d)", bet[0]*2, dollar[0]);
			  
		  			turnEnd = 1;
				}
					
				else if(cardSum[0]>21)		//cardSum is over 21
				{
					printf("DEAD (sum: %d) --> -$%d ($%d)\n", cardSum[0], bet[0], dollar[0]-bet[0]);
					bet[0] = -bet[0];
					
					turnEnd = 1;
				}
			
			
				else						//cardSum is under 21
				{
					printf("Action? (0 - go, others - stay) : ");
					scanf("%d", &action);
					
					if(action == 0)
						cardhold[0][Num_of_Card] = pullCard();
					else
					{
						turnEnd = 1;
						cardSum[0] = 100;		//escape 'for' which is a grammar
					}
				
				}
			Num_of_Card++;
			//printf("card sum is %d\t\n", cardSum[0]);
			}
		}
		
		turnEnd = 0;
		
		//each player's turn
		for (i=1;i<n_user;i++) //each player
		{
			printf("\n\n>>> player %i turn! ----------\n", i);
			
			
			while (turnEnd == 0) //do until the player dies or player says stop
			{
				Num_of_Card = 2;
				printUserCardStatus(i, Num_of_Card);	//print current card status printUserCardStatus();
				calcStepResult(i);						//check the card status ::: calcStepResult()
				
				//printf("card sum is %d\t", cardSum[i]);			//This is for test*******Check cardSum
				
				getAction();							//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		
		//server's turn
		printf("\n\n>>> server turn! ----------\n");
		for(Num_of_Card=2; cardSum[n_user]<17; Num_of_Card++)
		{
			printUserCardStatus(n_user, Num_of_Card);
			calcStepResult(n_user);
			
			//printf("card sum is %d\t", cardSum[n_user]);			//This is for test*******Check cardSum
			
			getActionServer();
		}
		
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();

	
	return 0;
}
