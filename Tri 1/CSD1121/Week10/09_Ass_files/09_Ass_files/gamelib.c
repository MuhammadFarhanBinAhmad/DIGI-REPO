// TODO: Add file-level documentation.

#include <stdio.h>
#include "gamelib.h"
#include "cardlib.h"



// TODO: Add function-level documentation.
void del_card(Card game[], CardIndex position)
{

	for(;;++position)
	{
		//remove card
		game[position].suit = game[position+1].suit;
		game[position].rank = game[position+1].rank;
		if (game[position].suit == '0')//
		{
			break;
		}

	}
	// TODO
}

// TODO: Add function-level documentation.
void load_game(const char str[], Card game[])
{

	int i = 0;

	for (int j =0 ;;++i,++j)
	{
			game[i].suit = str[i];//set suit
			game[i].rank = str[i+1];//set rank
			i++;//ignore space
			if (game[i].suit == '0')//
			{
				break;
			}
	}

	// TODO
}

// TODO: Add function-level documentation.
void play_game(Card game[])
{
	for (int i =0;game[i].suit == '0';i++)
	{
		if(game[i].suit == game[i+3].suit||game[i].rank == game[i+3].rank)
		{
			game[i].suit = game[i+3].suit;
			game[i].rank = game[i+3].rank;
			del_card(game,(unsigned char)(i+1));
			i--;
		}
		else if(game[i].suit == game[i+1].suit||game[i].rank == game[i+1].rank)
		{
			game[i].suit = game[i+1].suit;
			game[i].rank = game[i+1].rank;
			del_card(game,(unsigned char)(i+1));
			i--;
		}
	}
	// TODO
}

// TODO: Add function-level documentation.
void display_game(const Card game[])
{
	// TODO
	for (int i =0;game[i].suit == '0';i++)
	{
		printf("%c",game[i].suit);
		printf("%c ",game[i].rank);
	}
	printf("\n");
}
