#include <iostream>
#include "gamehex.h"

using namespace std;


void game()
{
	char alphabet[13] = "ABCDEFGHIJKL";
	int size,game_style;
	char** map;
	char column;
	int col,cmp_col;
	int row,cmp_row;
	int control;
	int first_computer_move = 0;
	int flag;

	//Take the Game Of Size
	do
	{
		cout << "\nEnter The Game Of Sıze:";
		cin >> size;
		if (size > 12 || size < 6)
			cout << "Fault ! Enter again ! Size should be between 6 and 12.";
	} while (size>12 || size<6);

	map = new char* [size];
	for (int i = 0;i < size;i++)
	{
		map[i] = new char[size];
	}

	fill_map(map,size);

	// Take The Input From User Type of Game
	do
	{
		cout << "\nEnter The Type Of Game" << endl << "1-P VS P\n2- P VS C \nWrite 1 OR 2:";
		cin >> game_style;
		if (game_style != 1 && game_style != 2)
			cout << "Fault ! Enter again ! Game style should be 1 or 2.";
	} while (game_style != 1 && game_style != 2);

	if (game_style == 1)
		cout << "The Player and Player Game is starting..." << endl;

	if (game_style == 2)
	{
		cout << "The Player and Computer Game is starting..." << endl;
	}

	print_map(map,alphabet, size);

	//STARTING THE GAME
	do{
		//Mover Player 1
		do{
			cout<<"PLAYER 1 // Enter The Column and The Row(EXMP : C7):";
			cin>>column>>row;
			control = control_and_move(map,alphabet,'X',column,row,size);
			if(control == 0)
				cout<<"It is not valid coordinate. Enter valid coordinate."<<endl;
		}while(control == 0);
		print_map(map,alphabet, size);
		//Control MAP For end of the game
		for(int i = 0;i<size;i++)
			if('X' == map[i][0]){
				flag = control_end_of_the_game(map,'X',0,i,0,size);
				if(flag == 1)
					cout<<"\nPlayer 1 win ! \n";
			}
		//if game_style is two put the first move computer
		if(first_computer_move == 0 && game_style == 2 && flag != 1){
			if(map[0][size-1] == '.'){
				map[0][size-1] = 'O';
				cmp_row = 0;
				cmp_col = size-1;
			}

			else{
				map[0][size-2] = 'O';
				cmp_row = 0;
				cmp_col = size-2;
			}
			print_map(map,alphabet, size);
			first_computer_move = 1;
		}
		//Player Two
		else if(game_style == 1 && flag != 1)
		{
			do{
				cout<<"PLAYER 2 // Enter The Column and The Row(EXMP : C7):";
				cin>>column>>row;
				control = control_and_move(map,alphabet,'O',column,row,size);
				if(control == 0)
					cout<<"It is not valid coordinate. Enter valid coordinate."<<endl;
			}while(control == 0);
			print_map(map,alphabet, size);
		}//Computer
		else if(game_style == 2 && flag != 1)
		{
			computer_move(map,cmp_row,cmp_col,size);
			cout<<"\nComputer move : "<<alphabet[cmp_col]<<cmp_row<<endl;
			print_map(map,alphabet, size);
		}

		if(flag != 1)
			for(int i = 0;i<size;i++)
				if('O' == map[0][i]){
					flag = control_end_of_the_game(map,'O',0,0,i,size);
					if(flag == 1&&game_style == 2)
						cout<<"\nComputer win ! \n";
					if(flag == 1&&game_style == 1)
						cout<<"\nPlayer 2 win ! \n";
				}
		//Map is full or not full control
		for(int i=0;i<size && flag != 1;i++){
			for(int j=0 ; j<size; j++)
			{
				if(map[i][j] == '.')
				{
					flag =0;
					break;
				}
				else
					flag =1;
			}
			if(flag == 0)
				break;
		}

	}while(flag != 1);



}

//This Function fill the map with dots.
void fill_map(char** map, int size)
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			map[i][j] = '.';
		}
	}
}

//This Function just print map.
void print_map(char** map,char *alphabet, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << " " << alphabet[i];
	}
	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << i+1;
		for (int k = 0; k < i; k++)
		{
			cout << " ";
		}
		for (int j = 0; j < size; j++)
		{
			cout << map[i][j] <<" ";
		}
		cout << endl;
	}
}

//This function takes the coordionate that are column and row and control whether it is valid and move.
//If This coordinate is true this function return 1 otherwise return 0.
int control_and_move(char**map, char*alphabet,char player,char column, int row, int size)
{
	for(int i=0; i<size; ++i)
	{
		if(alphabet[i] == column && row>=0 && row <= size && map[row-1][i] == '.'){
			map[row-1][i] = player;
			return 1;
		}
	}
	return 0;
}

//This function control end of the game. Flag is one game is finished.
int control_end_of_the_game(char**map,char player,int control,int row,int column,int size)
{
	int flag = 0;

		if(row > 0)
			if(control != 1 && map[row-1][column] == player && flag == 0)
				{
					map[row-1][column] = ',';
					if(player == 'X' && column == size-1){
						map[row-1][column] = player;
						return 1;
					}
					if(player == 'O' && row-1 == size-1){
						map[row-1][column] = player;
						return 1;
					}

					flag = control_end_of_the_game(map,player,4,row-1,column,size);
					if(flag != 1)
						map[row-1][column] = player;
				}

		if(column > 0)
			if(control != 6 && map[row][column-1] == player && flag == 0)
				{
					map[row][column-1] = ',';
					if(player == 'X' && column-1 == size-1){
						map[row][column-1] = player;
						return 1;
					}
					if(player == 'O' && row == size-1){
						map[row][column-1] = player;
						return 1;
					}

					flag = control_end_of_the_game(map,player,3,row,column-1,size);
					if(flag != 1)
						map[row][column-1] = player;
				}

		if(row < size-1)
			if(control != 4 && map[row+1][column] == player && flag == 0)
				{
					map[row+1][column] = ',';
					if(player == 'X' && column == size-1){
						map[row+1][column] = player;
						return 1;
					}
					if(player == 'O' && row+1 == size-1){
						map[row+1][column] = player;
						return 1;
					}

					flag = control_end_of_the_game(map,player,1,row+1,column,size);
					if(flag != 1)
						map[row+1][column] = player;
				}

		if(column < size-1)
			if(control != 3 && map[row][column+1] == player && flag == 0)
				{
				map[row][column+1] = ',';
					if(player == 'X' && column+1 == size-1){
						map[row][column+1] = player;
						return 1;
					}
					if(player == 'O' && row == size-1){
						map[row][column+1] = player;
						return 1;
					}

					flag = control_end_of_the_game(map,player,6,row,column+1,size);
					if(flag != 1)
						map[row][column+1] = player;
				}

		if(row>0 && column<size-1)
			if(control != 2 && map[row-1][column+1] == player && flag == 0)
			{
				map[row-1][column+1] = ',';
				if(player == 'X' && column+1 == size-1){
					map[row-1][column+1] = player;
					return 1;
				}
				if(player == 'O' && row-1 == size-1){
					map[row-1][column+1] = player;
					return 1;
				}
				flag = control_end_of_the_game(map,player,5,row-1,column+1,size);
				if(flag != 1)
					map[row-1][column+1] = player;
			}

		if(row<size-1 && column>0)
			if(control != 5 && map[row+1][column-1] == player && flag == 0)
			{
				map[row+1][column-1] = ',';
				if(player == 'X' && column-1 == size-1){
					map[row+1][column-1] = player;
					return 1;
				}
				if(player == 'O' && row+1 == size-1){
					map[row+1][column-1] = player;
					return 1;
				}

				flag = control_end_of_the_game(map,player,2,row+1,column-1,size);
				if(flag != 1)
					map[row+1][column-1] = player;
			}


	return flag;
}
// Computer move the short length.
int computer_move(char**map,int &row,int &column, int size)
{
	int flag = 0;


	if(row < size-1){

		if(map[row+1][column] == '.'){
			map[row+1][column] = 'O';
			row++;
			return 1;
		}
	}
	if(row<size-1 && column>0){

		if(map[row+1][column-1] == '.'){
			map[row+1][column-1] = 'O';
			row++;
			column--;
			return 1;
		}
	}
	if(column > 0){

		if(map[row][column-1] == '.'){
			map[row][column-1] = 'O';
			column--;
			return 1;
		}
	}
	if(row > 0){

		if(map[row-1][column] == '.'){
			map[row-1][column] = 'O';
			row--;
			return 1;
		}
	}
	if(row>0 && column<size-1){

		if(map[row-1][column+1] == '.'){
			map[row-1][column+1] = 'O';
			row--;
			column++;
			return 1;
		}
	}
	if(column < size-1){

		if(map[row][column+1] == '.'){
			map[row][column+1] = 'O';
			column++;
			return 1;
		}
	}

	return 0;
}



