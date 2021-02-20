/*
Reyadath Ullah
*/
#include <bits/stdc++.h>
using namespace std;

#ifdef IHAVETOPEE
#include "debug.h"
#else
#define debug(args...)
#endif


#define pb push_back
#define pii pair<int, int>
#define mp make_pair
#define fi first
#define se second

bool comp(const pii &a, const pii &b){
    return a.fi < b.fi;
}
//variables
char cards[] = {'A','K','Q','J','2','3','4','5','6','7','8','9','T'};
int value[] = {11,10,10,10,2,3,4,5,6,7,8,9,10};

map<char,string>cardsToShow;
int initialBalance;
int cardCount[15];

//printing the current hand of dealer and player
void printHand(vector<int>cardList,int total,string whos){
    cout<<"\n"<<whos<<" Hand : \n";
    for(int i = 0;i < (int)cardList.size();i++){
        cout<<cardsToShow[cards[cardList[i]]]<<" \n"[i == (int)cardList.size() - 1];
    }
    cout<<whos<<" Total :"<<total<<"\n";
}
//taking a valid bet as input
int takeBet(){
    int bet;
    printf("How much do you want to bet?\n");
    cin>>bet;
    while(true){
        if(bet < 69){
            printf("Minimum bet is 69$. Bet higher.\n");
        }
        else if(bet > initialBalance){
            printf("You don't have enough money. Bet lower\n");
        }
        else {
            printf("\n");
            break;
        }
        cin>>bet;
    }
    return bet;
}
//returns 4 random numers for the first draw
pair<pii,pii> randomNumber(){
    int card1 = rand()%13;
    int card2;
    cardCount[card1]--;
    while(true){
        card2 = rand()%13;
        if(cardCount[card2])break;
    }
    cardCount[card2]--;
    int card3,card4;
    while(true){
        card3 = rand()%13;
        if(cardCount[card3] > 0)break;
    }
    cardCount[card3]--;
    while(true){
        card4 = rand()%13;
        if(cardCount[card4] > 0)break;
    }
    cardCount[card4]--;
    return mp(mp(card1,card2),mp(card3,card4));
}
//returns a single random number
int singleRandom(){
    int card;
    while(true){
        card = rand()%13;
        if(cardCount[card] > 0)break;
    }
    return card;

}
void start(){
    if(initialBalance < 69){
        printf("You're broke\n");
        return;
    }
    //Taking input for bet
    pair<pii,pii>hand = randomNumber();
    int dealerTotal = 0, playerTotal = 0,bet = 0;
    bet = takeBet();
    //first draw
    vector<int>dealerCard,playerCard;
    dealerCard.pb(hand.fi.fi),dealerCard.pb(hand.fi.se);
    playerCard.pb(hand.se.fi),playerCard.pb(hand.se.se);


    if(hand.fi.fi == 0 && hand.fi.fi == 0)dealerTotal += value[hand.fi.fi] + 1;
    else dealerTotal += value[hand.fi.fi] + value[hand.fi.se];
    if(hand.se.fi == 0 && hand.se.se == 0)playerTotal += value[hand.se.fi] + 1;
    else playerTotal += value[hand.se.fi] + value[hand.se.se];
   
    //if the player gets 21 on the first draw
    if(playerTotal == 21){
        if(dealerTotal == 21){
            printf("\nDraw\n");
            return;
        }
        printHand(dealerCard,dealerTotal,"Dealers");
        printHand(playerCard,playerTotal,"Your");
        initialBalance += bet;
        return;
    }
    printf("Dealers Hand : \n");
    cout<<cardsToShow[cards[hand.fi.fi]]<<" "<<"?\n";
    printHand(playerCard,playerTotal,"Your");

    int userMove;
    while(true){
        printf("\nWhat do you want to do? Enter 1 to hit and 2 to stand\n");
        cin>>userMove;
        if(userMove == 2)break;
        else if(userMove == 1){
            int card = singleRandom();
            if(card == 0){
                if(playerTotal + value[card] <= 21){
                    playerTotal += value[card];
                }else{
                    playerTotal += 1;
                }
                playerCard.pb(card);
            }
            else{
                playerCard.pb(card);
                playerTotal += value[card];
                if(playerTotal >= 21)break;
            }
            printHand(playerCard,playerTotal,"Your");
        }
        else printf("Enter 1 to hit and 2 to stand\n");
    }
    //player busts

    if(playerTotal > 21){
        printHand(dealerCard,dealerTotal,"Dealers");
        printHand(playerCard,playerTotal,"Your");
        printf("\nYou lost haha\n");
        initialBalance -= bet;
        return;
    }
    //dealer takes card until he's reached 17 or higher
    while(dealerTotal < 17){
        int card = singleRandom();
        if(card == 0){
            if(dealerTotal + value[card] <= 21){
                dealerTotal += value[card];
            }else{
                dealerTotal += 1;
            }
                dealerCard.pb(card);
        }else{
            dealerCard.pb(card);
            dealerTotal += value[card];
            if(dealerTotal >= 21)break;
        }
    }

    printHand(dealerCard,dealerTotal,"Dealers");
    printHand(playerCard,playerTotal,"Your");

    if(dealerTotal > 21 || (playerTotal > dealerTotal)){
        printf("\nYou Win\n");
        initialBalance += bet;
    }
    else if(dealerTotal == playerTotal){
        printf("\nDraw\n");
    }
    else{
        printf("\nYou lost haha\n");
        initialBalance -= bet;
    }

}
int main()
{
    time_t t;
	srand((unsigned)time(&t));
    
    printf("++++++++++++++++++++++++++++++++++\n");
    printf("\tB L A C K J A C K\n");
    printf("++++++++++++++++++++++++++++++++++\n");
    FILE *fp = fopen("balance","r");
    fscanf(fp,"%d",&initialBalance);
    cardsToShow['A'] = "A";
    cardsToShow['K'] = "K";
    cardsToShow['Q'] = "Q";
    cardsToShow['J'] = "J";
    cardsToShow['2'] = "2";
    cardsToShow['3'] = "3";
    cardsToShow['4'] = "4";
    cardsToShow['5'] = "5";
    cardsToShow['6'] = "6";
    cardsToShow['7'] = "7";
    cardsToShow['8'] = "8";
    cardsToShow['9'] = "9";
    cardsToShow['T'] = "10";
    
    while(true){
         if(initialBalance < 69){
            printf("\n+++++++++++\n69$ Added to your account.\n+++++++++++\n");
            initialBalance += 69;
        }
        for(int i = 0;i < 13;i++)cardCount[i] = 4;
        cout<<"\nYOUR CURRENT BALANCE : "<<initialBalance<<"\n\n";
        printf("\n1-Start\n0-Exit\n");
        int cmd;
        cin>>cmd;
        if(cmd == 0)break;
            start();
       
    }
    FILE *fp2 = fopen("balance","w");
    fprintf(fp2,"%d",initialBalance);
    return 0;
}
