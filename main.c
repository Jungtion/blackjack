#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N_CARDSET        	1
#define N_CARD           	52
#define N_DOLLAR         	50


#define N_MAX_CARDNUM     	13
#define N_MAX_USER         	5
#define N_MAX_CARDHOLD      10
#define N_MAX_GO        	17
#define N_MAX_BET        	5

#define N_MIN_ENDCARD     	30


//card tray object
int CardTray[N_CARDSET*N_CARD];
int cardIndex = 0;


//player info
int dollar[N_MAX_USER];                  //dollars that each player has
int n_user;                           //number of users


//play yard information
int cardhold[N_MAX_USER + 1][N_MAX_CARDHOLD];   //cards that currently the players hold
int cardSum[N_MAX_USER];               //sum of the cards
int bet[N_MAX_USER];                  //current betting 
int gameEnd = 0;                      //game end flag

int input;
int turnEnd = 0;
int NumofCard = 2;


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
int getCardNum(int cardnum) {
   int actual_num = cardnum % 13	;
	
	if (actual_num>10 || actual_num==0)			//J, Q, K change to numer
		actual_num = 10	;
	
	if  (actual_num==1 && cardSum[n_user]<11)	// making ACE have actual number 11 when we need
		actual_num=11;
		
	return actual_num	;
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	// define a shape
	if (cardnum/13==0)
	printf("HRT ");
	else if (cardnum/13==1)
	printf("DIA ");
	else if (cardnum/13==2)
	printf("CLV ");
	else if (cardnum/13==3)
	printf("SPD ");
	
	// define a numer
	if (cardnum%13==1)
	printf("A	");
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
	printf("J	");
	else if (cardnum%13==12)
	printf("Q	");
	else if (cardnum%13==0)
	printf("K	");	
}


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


int top = N_CARD-1;

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
	
   int i;
   
   	for (i=0; i<N_MAX_USER; i++)
	dollar[i] = N_DOLLAR + bet[i];

	printf(" -> Your Betting (total: $%d) :", dollar[0]);
	scanf("%d", &bet[0]);

	if (bet[0]>dollar[0])
		printf("You only have $%d! Bet again!", dollar[0]);

	if (bet[0]<=0)
		printf("invalid input for betting $%d", bet[0]);


	for (i=1; i<n_user; i++)						// other user's betting money
		printf(" -> player%d bets %d (out of $%d)\n", i, 1+rand()%N_MAX_BET, dollar[i]); 
}


//offering initial 2 cards
void offerCards(void) {
   int i;
   //1. give two card for each players
   for (i = 0; i < n_user; i++)
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


void printUserCardStatus(int user, int cardcnt) {
   int i;

   printf("   -> card : ");
   for (i = 0; i < cardcnt; i++)
      printCard(cardhold[user][i]);
   printf("\t ::: ");
}




// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(int user) {
int j;
	
	cardSum[user] = 0;
	
	for (j=0; j<NumofCard; j++)
	{						
		cardSum[user] = cardSum[user] + getCardNum(cardhold[user][j]);
	}
	
	   //blackjack
   if (cardSum[user] == 21)
   {
      dollar[user] = dollar[user] + bet[user] *2;
      printf("Black jack! you win!! --> +$%d ($%d)", bet[user]*2, dollar[user]);

      turnEnd = 1;
   }
   //over21
   else if (cardSum[user] > 21)
   {
      dollar[user] = dollar[user] - bet[user];
      printf("Dead (sum:%d) --> -$%d ($%d)", cardSum[user], bet[user], dollar[user]);

      turnEnd = 1;
   }

}


int calcsServerStepResult() {

   int i;

   cardSum[n_user] = 0;

   for (i = 0; i < NumofCard; i++)
      cardSum[n_user] = cardSum[n_user] + getCardNum(cardhold[n_user][i]);


   //black jack
   if (cardSum[n_user] == 21)
   {
      printf("Black jack! server win!!\n");
      printf("[[[[[[[server result is.... Blackjack ]]]]]]]");

      turnEnd = 1;
   }
   
   
   //over 21
   else if (cardSum[n_user] > 21)
   {
      printf("serever Dead (sum:%d)\n", cardSum[n_user]);
      printf("[[[[[[[server result is.... Overflow!! ]]]]]]]");

      turnEnd = 1;
   }

}


//Action

int checkResult() {
   
   int i;
   
   if (cardSum[n_user] > 21)
   {
      for (i = 0; i < n_user; i++)
      {
         if (i == 0)
            printf("    -> your result : ");

         else
            printf("    -> %d player's result : ",i);


         //player over 21
         if (cardSum[i] > 21)
            printf("lose due to overflow! ($%d)\n", dollar[i]);

         //player black jack
         else if (cardSum[i] == 21)
            printf("BlackJack! Win! ($%d)\n", dollar[i]);

         //player under 21
         else
         {
            dollar[i] = dollar[i] + bet[i];
            printf("Win! (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
         }
      }

   }
   
   //server blackjack
   else if (cardSum[n_user] == 21)
   {
      for (i = 0; i < n_user; i++)
      {
         if (i == 0)
            printf("    -> your result : ");

         else
            printf("    -> %d player's result : ", i);

         if (cardSum[i] > 21)
            printf("lose due to overflow! ($%d)\n", dollar[i]);
 
         else if (cardSum[i] == 21)
            printf("BlackJack! Win! ($%d)\n", dollar[i]);

         else
         {
            dollar[i] = dollar[i] - bet[i];
            printf("lose! (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
         }
      }
   }
   //server under 21
   else
   {
      for (i = 0; i < n_user; i++)
      {
         if (i == 0)
            printf("    -> your result : ");

         else
            printf("    -> %d player's result : ", i);

         if (cardSum[i] > 21)
            printf("lose due to overflow! ($%d)\n", dollar[i]);

         else if (cardSum[i] == 21)
            printf("BlackJack! Win! ($%d)\n", dollar[i]);

         //under 21
         else
         {
            //player win
            if (cardSum[i] >= cardSum[n_user])
            {
               dollar[i] = dollar[i] + bet[i];
               printf("Win! (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
            }
            //player lose
            else if (cardSum[i] < cardSum[n_user])
            {
               dollar[i] = dollar[i] - bet[i];
               printf("lose! (sum:%d) --> ($%d)\n", cardSum[i], dollar[i]);
            }


         }
      }
   }

   //no money
   for (i = 0; i < n_user; i++)
   {
      if (dollar[i] == 0)
      {
         gameEnd = 1;
         break;
      }
   }

}

int checkWinner() {
   
   int i;
   printf("\n\n\n--------------------------------------------\n\n");
   printf("--------------------------------------------\n\n");
   printf("--------------------------------------------\n\n");
   printf("--------------------------------------------\n\n");
   printf("game end! your money :$%d, ",dollar[0]);


   if (n_user > 2)
   {
      printf("player's money : ");
      for (i = 1; i < n_user; i++)
      {
         printf("$%d ", dollar[i]);
      }
      printf("\n\n\n");
   }


   int maxValue = dollar[0];
   int maxIndex = 0;


   for (i = 1; i < n_user; i++)
   {
      if (maxValue < dollar[i])
      {
         maxValue = dollar[i];
         maxIndex = i;
      }
   }

 
   if (maxIndex == 0)
      printf("you win!!!\n");

   else
      printf("player %d's win\n", maxIndex);

}



int main(int argc, char *argv[]) {
   int round=1;
   int max_user;
   int i;

   srand((unsigned)time(NULL));
   //set the number of players
   configUser();

   //Game initialization --------
   //1. players' dollar

   //2. card tray
   mixCardTray();

   //Game start --------
   do {

      cardIndex = N_CARD - (top + 1);
      printf("\n-------------------------------------------------\n");
      printf("------------- Round %d (cardIndex:%d) ---------------------------\n",round,cardIndex);
      printf("-------------------------------------------------\n\n");

		round++;

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

      //each player's turn
      for (i = 0; i <= n_user;i++) //each player
      {
         turnEnd = 0;
         //player change->#of card reset
         NumofCard = 2;
         
		 if (i == 0)
		 printf(">>> my turn! -------------\n");

         else if (i == n_user)
         printf(">>> server turn! ---------------------\n");

         else
         printf(">>> player %d turn! -------------\n", i);


         while (turnEnd == 0) //do until the player dies or player says stop
         {

            if (i == 0)
            {
               //print current card status printUserCardStatus();
               printUserCardStatus(i, NumofCard);
               //check the card status ::: calcStepResult()
               calcStepResult(i);
               //GO? STOP? ::: getAction()
               getAction();
            }
            
            
            //server
             if (i == n_user)
            {
               //print current card status printUserCardStatus();
               printUserCardStatus(i, NumofCard);
               calcsServerStepResult();
               getActionServer();
            }


            //others
            else
            {
               //print current card status printUserCardStatus();
               printUserCardStatus(i, NumofCard);
               //check the card status ::: calcStepResult()
               calcStepResult(i);
               getActionplayer(i);
            }

            //만약 gameEnd 플래그가 0이 아니라면
            if (gameEnd != 0)
            {
               printf("Card ran out of the tray!! finishing the game.");
				break;
            }

         }
      }

      //result
      printf("------------------------ Round %d result ....\n", round+1);
      checkResult();


      if (gameEnd != 0)
      break;

   } while (gameEnd == 0);

   checkWinner();


   return 0;
}
