#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_MAX_USER			5

extern	int cardSum[N_MAX_USER];					//sum of the cards


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum, int user) { 		//card num=modeling number
	int actual_num = cardnum % 13	;
	
	if (actual_num>10 || actual_num==0)			//J, Q, K change to numer
		actual_num = 10	;
	
	if  (actual_num==1 && cardSum[user]<11)	// making ACE have actual number 11 when we need
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
