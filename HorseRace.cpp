//Let's Win at the Races 1.66 RELASE VERSION
//By Josh Miller
//4-4-01 - Added Title Screen
//         Added generate_odds
//         Added get_cash
//         Added bet
//         Added disp_odds
//4-9-01 - Added move_horse
//         Added movement loop
//4-11-01- Added payoff
//       - Added repetition till one player looses all thier money
//       - Added disp_race
//       - Final Debugging - Program was causeing FATAL ERROR message in OS
//4-12-01- Added final results and improved end of race and end game

#include<iostream.h>
#include<stdlib.h>
#include<time.h>

void title_screen();
void generate_odds(int odds[],int size);
void get_cash(int stats[], int pl_num);
void bet(int stats[],int pl_num, int odds[]);
void disp_odds(int odds[]);
int move_horse(int odds[], int horse);
int payoff(int winner, int player[], int pl_num);
void disp_race(int positions[]);
void final_results(int player1[],int player2[]);

int main()
{
	int odds[8];
	int player1[5], player2[5];
	int position[8]={0,0,0,0,0,0,0,0};
	int count;
	int winner;
	char more_race='Y';

//Player array, slot0=money total, slot1=horse bet on, slot2=bet amount, slot3=odds of bet
//slot4=original cash level.
	srand(time(0));

	title_screen();
	get_cash(player1,1);
	get_cash(player2,2);

	do
	{
	for(count=0;count<8;count++)
		position[count]=0;
	winner=6000;
	generate_odds(odds,8);
    disp_odds(odds);
	bet(player1,1,odds);
    disp_odds(odds);
	bet(player2,2,odds);

	do
	{
	for(count=0;count<8;count++)
		{	
		position[count]+=move_horse(odds, count);
		if(position[count]>=50)
			winner=count;
		}
	disp_race(position);
	}
	while(winner==6000);
	
	cout<<"\nThe winning horse is horse "<<winner+1<<endl;
	player1[0]+=payoff(winner, player1,1);
	player2[0]+=payoff(winner, player2,2);

	if((player1[0]<=0)||(player2[0]<=0))
		more_race='n';
	else
		{
		cout<<"\nWould you like another race? (Y/N)\n";
		cin>>more_race;
		}
	}
	while((more_race=='Y')||(more_race=='y'));

	final_results(player1,player2);

	return 0;
}

void title_screen()
{
//Generates a simple title image
cout<<"       ___/\\_     LET'S WIN AT    _/\\___\n";
cout<<"      _/ /  \\\\     THE RACES     //    \\_\n";
cout<<"     _/     o \\                 / o     \\_\n";
cout<<"    _/     _   \\   PROGRAMED   /   _     \\_\n";
cout<<"   _/     / \\   |     BY      |   / \\     \\_\n";
cout<<"  _/     |   \\_/  JOSH MILLER  \\_/   |     \\_\n";
cout<<" _/     /                             \\     \\_\n";
cout<<"                   HOMEPAGE AT\n";
cout<<"http://www.geocities.com/Tokyo/Pagoda/6098/HorsRace\n\n";
}

void generate_odds(int odds[], int size)
{
//This function calculates the odds for each horse at the begining of each race
	int count;

	for(count=0;count<size;count++)
		{
		odds[count]=((rand()%5)+1)*2;
		}
}

void get_cash(int stats[], int pl_num)
{
//Gets the player's initial cash fund.
//This function may eventually be replaced by a set amount of cash.
	cout<<"How much money will player "<<pl_num<<" start with?\n";
	cin>> stats[0];
	stats[4]=stats[0];
}

void bet(int stats[],int pl_num, int odds[])
{
//This function takes bets at the begining of a race.  It is designed to
//Only allow bets on real horses and to only let pleyers bet within thier bank accout
	int horse_num;
	cout<<"\nPlayer "<<pl_num<<", you have "<<stats[0]<<" dollars.\n";
	
	do
	{
	cout<<"Which horse will you bet on?\n";
	cin>> horse_num;

	stats[1]=horse_num;

	if((stats[1]<=0)||(stats[1]>=9))
		cout<<"That is an invalid choice\n\n";

	}
	while((stats[1]<=0)||(stats[1]>=9));

	stats[3]=odds[horse_num-1];

	do
	{
	cout<<"\nHow much will you bet on that horse?\n";
	cin>> stats[2];

	if(stats[2]>stats[0])
		cout<<"\nYou can't bet more then you have!\n\n";
	else if(stats[2]<=0)
		cout<<"\nYou must bet at least 1 dollar.\n\n";

	}
	while((stats[2]>stats[0])||(stats[2]<=0));
	
	stats[0]-=stats[2];

	cout<<endl;
}

void disp_odds(int odds[])
{
//This function displays the odds for each horse at the begining of each race
	int count;
	
	cout<<endl;

	for(count=0;count<8;count++)
		{
		cout<<"The odds on Horse "<<count+1<<" are: 1 in "<<odds[count]<<endl;
		}
}

int move_horse(int odds[], int horse)
{
//This function will move a horse based on it's odds of winning
	int move;
	move=5-(odds[horse])/2+(rand()%6);
	return move;
}

int payoff(int winner, int player[], int pl_num)
{
//This function pays out any winning bets
	int amount=0;

	if((player[1]-1)==winner)
		{
		cout<<"\nCongratulations player "<<pl_num<<", you are a winner.\n";
		amount+=player[3]*player[2];
		cout<<"\nYou've won "<<amount<<" dollars!\n";
		}
	else
		cout<<"\nSorry player "<<pl_num<<", your horse lost.\n";

	return amount;
}

void disp_race(int positions[])
{
//This function displays the race as a series of Xs for each horse's movement
	int count, count2;
	char nothing;

	cout<<"\nHorse       Distance                                          |FIN\n";

	for(count=0;count<8;count++)
		{
		cout<<"Horse "<<count+1<<"     ";
		
		for(count2=0;count2<positions[count];count2++)
			cout<<"X";

		cout<<endl;
		}

	cout<<"\n Type 'C' to continue\n";
	cin>>nothing;

	if(nothing=='E')
		cout<<"\nEASTER EGG!  ARRAYS SHOULD BE NUMBERED STARTING AT 1! THINGS WOULD BE EASIER!\n";
	if(nothing=='G')
		cout<<"\nWhat are you trying to prove?\n";

	return;
}

void final_results(int player1[],int player2[])
{
//This function should calculate the winner based on who gained the most.
//It should be altered to figure based on percentage gained and not actual gain
//As a person with 10000 to bet will surely be able to gain more then a person with 100.
	cout<<"\nPlayer 1 ended up with "<<player1[0]<<" dollars for a gain of: ";
	cout<<(player1[0]-player1[4])<<".\n";
	cout<<"\nPlayer 2 ended up with "<<player2[0]<<" dollars for a gain of: ";
	cout<<(player2[0]-player2[4])<<".\n";

	if((player1[0]-player1[4])>(player2[0]-player2[4]))
		cout<<"\nPlayer 1 is the winner.\n";
	else if((player2[0]-player2[4])>(player1[0]-player1[4]))
		cout<<"\nPlayer 2 is the winner.\n";
	else
		cout<<"\nIt's a tie!\n";
}