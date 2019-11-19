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


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) { 		//card num=modeling number
	int actual_num = cardnum % 13	;
	
	if (actual_num>10)			//J, Q, K change to numer
		actual_num = 10	;
	
	else if  (actual_num==1);	// making ACE have actual number 11
		{
		actual_num=11;
		}

	if (actual_num==11 && cardSum[N_MAX_USER]>21)	// making ACE have actual number 1 if it needs	//[Error] 'else' without a previous 'if'
		actual_num=1;
		
	return actual_num	;
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	
	if (cardnum/13==0)
	printf("HRT");
	else if (cardnum/13==1)
	printf("DIA");
	else if (cardnum/13==2)
	printf("CLV");
	else if (cardnum/13==3)
	printf("SPD");
	
	if (cardnum%13==1)
	printf("ACE	");
	else if (cardnum%13==2)
	printf("2	");
	else if (cardnum%13==3)
	printf("3	");
	else if (cardnum%13==4)
	printf("4	");
	else if (cardnum%13==5)
	printf("5	");
	else if (cardnum%13==6)
	printf("6	");
	else if (cardnum%13==7)
	printf("7	");
	else if (cardnum%13==8)
	printf("8	");
	else if (cardnum%13==9)
	printf("9	");
	else if (cardnum%13==10)
	printf("10	");
	else if (cardnum%13==11)
	printf("JACK	");
	else if (cardnum%13==12)
	printf("QUEEN	");
	else if (cardnum%13==0)
	printf("KING	");		
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	int i	;
	int j=-1	;
	
	for (i=0;i<N_CARDSET*N_CARD;i++)
	{
		do {
		CardTray[i]==rand()%(N_CARDSET*N_CARD);
		j = j+1;
		}
		while (CardTray[i]==CardTray[j]);
		
	}
	
	printf(" --> card is mixed and put into the tray\n");
}

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


//playing game functions -----------------------------

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
	if (bet[0]<0)
		printf("invalid input for betting $%d", bet[0]);
	srand((unsigned) time(NULL));
	
	for (i=1; i<n_user; i++)						// other user's betting money
		printf(" -> player%d bets %d (out of $%d)\n", i, 1+rand()%N_MAX_BET, dollar[i]);  
}


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
	printf("	server	: X		");				//server's card
	printCard(cardhold[n_user][0]);
	printf("\n");
	
	
	printf("	you	: ");						//your card
	printCard(cardhold[0][0]);
	printCard(cardhold[0][1]);
	printf("\n");
	
	
	if (n_user>1)								//user's card
		for(i=1; i<n_user; i++)
		printf("	player%d : ", i);
		printCard(cardhold[i][0]);
		printCard(cardhold[i][1]);
		printf("\n");
}

int getAction(void) {
	
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	
}

int checkWinner() {
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	int total_num;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		printf("-----BETTING STEP-----\n");
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		for (i=1;i==n_user;i++) //each player
		{
			while (total_num<18) //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
