#include <iostream>
#include "gamehex.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

enum player;

void game()
{
	char alphabet[13] = "ABCDEFGHIJKL";
	char** map;
	char column;
	string save_name;
	string load_name;
	int size,game_style;
	int first_computer_move = 0;
	int operation;

	auto col = size,cmp_col = size;
	auto row = size,cmp_row = size;
	auto flag = size;
	decltype (size*3) control;


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
			cerr << "Fault ! Enter again ! Game style should be 1 or 2.";
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
			cout<<"PLAYER 1 // Enter The Column and The Row or LOAD or SAVE command line(EXMP : C7):";
			operation = operation_control(column,row,save_name,load_name);
			if(operation == 0){
				cout<<"File is saving... ="<<save_name<<endl;
				control = file_operation(operation,save_name,game_style,player1,size,map,cmp_row,cmp_col);
			}
			else if(operation == 1){
				cout<<"File is loading... ="<<load_name<<endl;
				control = file_operation(operation,load_name,game_style,player1,size,map,cmp_row,cmp_col);
				if(game_style == 2)
					first_computer_move = 1;
				
			}
			else if(operation == 2){
				control = control_and_move(map,alphabet,player1,column,row,size);
				if(control == 0)
					cout<<"It is not valid coordinate. Enter valid coordinate."<<endl;
			}
			else if(operation == 3){
				control= 0;
				cout<<"This command line is not true."<<endl;
			}

		}while(control == 0);
		print_map(map,alphabet, size);
		//Control MAP For end of the game
		for(int i = 0;i<size;i++)
			if(player1 == map[i][0]){
				flag = control_end_of_the_game(map,player1,0,i,0,size);
				if(flag == 1)
					cout<<"\nPlayer 1 win ! \n";
			}
		//if game_style is two put the first move computer
		if(first_computer_move == 0 && game_style == 2 && flag != 1){
			if(map[0][size-1] == dot){
				map[0][size-1] = player2;
				cmp_row = 0;
				cmp_col = size-1;
			}

			else{
				map[0][size-2] = player2;
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
				cout<<"PLAYER 2 //  Enter The Column and The Row or LOAD or SAVE command line(EXMP : C7):";
				operation = operation_control(column,row,save_name,load_name);

				if(operation == 0){
					cout<<"File is saving... ="<<save_name<<endl;
					control = file_operation(operation,save_name,game_style,player2,size,map,cmp_row,cmp_col);
				}
				else if(operation == 1){
					cout<<"File is loading... ="<<load_name<<endl;
					control = file_operation(operation,load_name,game_style,player2,size,map,cmp_row,cmp_col);
				}
				else if(operation == 2){
					control = control_and_move(map,alphabet,player2,column,row,size);
					if(control == 0)
						cout<<"It is not valid coordinate. Enter valid coordinate."<<endl;
				}
				else if(operation == 3){
					control= 0;
					cout<<"This command line is not true.";
				}
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
				if(player2 == map[0][i]){
					flag = control_end_of_the_game(map,player2,0,0,i,size);
					if(flag == 1&&game_style == 2)
						cout<<"\nComputer win ! \n";
					if(flag == 1&&game_style == 1)
						cout<<"\nPlayer 2 win ! \n";
				}
		//Map is full or not full control
		for(int i=0;i<size && flag != 1;i++){
			for(int j=0 ; j<size; j++)
			{
				if(map[i][j] == dot)
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
void fill_map(char** map,int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			map[i][j] = dot;
		}
	}
}

//This Function just print map.
void print_map(char** map,const char *alphabet,const int &size)
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
int control_and_move(char**map,const char*alphabet,const enum player type,const char &column,const int &row,const int &size)
{
	
	for(int i=0; i<size; ++i)
	{
		if(alphabet[i] == column && row>=0 && row <= size && map[row-1][i] == dot){
			map[row-1][i] = type;
			return 1;
		}
	}
	return 0;
}

//This function control end of the game. Flag is one game is finished.
int control_end_of_the_game(char**map,const enum player type,const int &control,const int &row,const int &column,const int &size)
{
	int flag = 0;

		if(row > 0)
			if(control != 1 && map[row-1][column] == type && flag == 0)
				{
					map[row-1][column] = comma;
					if(type == player1 && column == size-1){
						map[row-1][column] = player1;
						return 1;
					}
					if(type == player2 && row-1 == size-1){
						map[row-1][column] = player2;
						return 1;
					}

					flag = control_end_of_the_game(map,type,4,row-1,column,size);
					if(flag != 1)
						map[row-1][column] = type;
				}

		if(column > 0)
			if(control != 6 && map[row][column-1] == type && flag == 0)
				{
					map[row][column-1] = comma;
					if(type == player1 && column-1 == size-1){
						map[row][column-1] = player1;
						return 1;
					}
					if(type == player2 && row == size-1){
						map[row][column-1] = player2;
						return 1;
					}

					flag = control_end_of_the_game(map,type,3,row,column-1,size);
					if(flag != 1)
						map[row][column-1] = type;
				}

		if(row < size-1)
			if(control != 4 && map[row+1][column] == type && flag == 0)
				{
					map[row+1][column] = comma;
					if(type == player1 && column == size-1){
						map[row+1][column] = player1;
						return 1;
					}
					if(type == player2 && row+1 == size-1){
						map[row+1][column] = player2;
						return 1;
					}

					flag = control_end_of_the_game(map,type,1,row+1,column,size);
					if(flag != 1)
						map[row+1][column] = type;
				}

		if(column < size-1)
			if(control != 3 && map[row][column+1] == type && flag == 0)
				{
				map[row][column+1] = comma;
					if(type == player1 && column+1 == size-1){
						map[row][column+1] = player1;
						return 1;
					}
					if(type == player2 && row == size-1){
						map[row][column+1] = player2;
						return 1;
					}

					flag = control_end_of_the_game(map,type,6,row,column+1,size);
					if(flag != 1)
						map[row][column+1] = type;
				}

		if(row>0 && column<size-1)
			if(control != 2 && map[row-1][column+1] == type && flag == 0)
			{
				map[row-1][column+1] = comma;
				if(type == player1 && column+1 == size-1){
					map[row-1][column+1] = player1;
					return 1;
				}
				if(type == player2 && row-1 == size-1){
					map[row-1][column+1] = player2;
					return 1;
				}
				flag = control_end_of_the_game(map,type,5,row-1,column+1,size);
				if(flag != 1)
					map[row-1][column+1] = type;
			}

		if(row<size-1 && column>0)
			if(control != 5 && map[row+1][column-1] == type && flag == 0)
			{
				map[row+1][column-1] = comma;
				if(type == player1 && column-1 == size-1){
					map[row+1][column-1] = player1;
					return 1;
				}
				if(type == player2 && row+1 == size-1){
					map[row+1][column-1] = player2;
					return 1;
				}

				flag = control_end_of_the_game(map,type,2,row+1,column-1,size);
				if(flag != 1)
					map[row+1][column-1] = type;
			}


	return flag;
}
// Computer move the short length.
int computer_move(char**map,int &row,int &column,const int &size)
{
	int flag = 0;

	if(row < size-1){

		if(map[row+1][column] == dot){
			map[row+1][column] = player2;
			row++;
			return 1;
		}
	}
	if(row<size-1 && column>0){

		if(map[row+1][column-1] == dot){
			map[row+1][column-1] = player2;
			row++;
			column--;
			return 1;
		}
	}
	if(column > 0){

		if(map[row][column-1] == dot){
			map[row][column-1] = player2;
			column--;
			return 1;
		}
	}
	if(row > 0){

		if(map[row-1][column] == dot){
			map[row-1][column] = player2;
			row--;
			return 1;
		}
	}
	if(row>0 && column<size-1){

		if(map[row-1][column+1] == dot){
			map[row-1][column+1] = player2;
			row--;
			column++;
			return 1;
		}
	}
	if(column < size-1){

		if(map[row][column+1] == dot){
			map[row][column+1] = player2;
			column++;
			return 1;
		}
	}

	return 0;
}
 // THIS FUNCTION CONTROL THE COMMAND OPERATION
int operation_control(char &character,int &roww,string &save_name,string &load_name)
{
	string command;
	string row;
	char save[5] = "SAVE";
	char load[5] = "LOAD";
	char txt[4] = "TXT";
	int operation = 3;
	int first,last;
	int counter;
	bool flag=1,flag1,flag2;

	cin>>ws;
	getline(cin,command);
	
	//CONTROL THE SAVE COMMON THAT TAKEN FROM THE USER
	if(flag == 1){
		counter = 0;
		for(int i=0;command[i] != ' ' && command[i] != '\0' ;i++)
		{
			if(save[i] == command[i])
			{
				counter++;
				first = i;
			}
			else
				break;
		}
		if(counter == 4)
		{
			flag1 = 0;
			for(int i = first,j=0;command[i] !='\0';i++){
				last = i;
				if(command[i] == '.' && flag1 != 1){
					flag1 = 1;
					if(!(command[i+1] == txt[0] && command[i+2] == txt[1] && command[i+3] == txt[2] && command[i+4] == '\0')){
						flag1 = 0;
						break;
					}
				}
			}
			if(flag1 == 1){
				save_name = command.substr(first+2,last);
				operation = 0;
				flag = 0;
			}
			else{
				cerr<<"\nThis is not txt file.";
				flag = 0;
			}
		}
	}
	//CONTROL THE LOAD COMMAND THAT TAKEN FROM THE USER
	if(flag == 1){
		counter = 0;
		for(int i=0;command[i] != ' ' && command[i] != '\0';i++)
		{
			if(load[i] == command[i])
			{
				counter++;
				first = i;
			}
			else
				break;
		}
		if(counter == 4)
		{
			flag2 = 0;
			for(int i = first,j=0;command[i] !='\0';i++){
				last = i;
				if(command[i] == '.' && flag2 != 1){
					flag2 = 1;
					if(!(command[i+1] == txt[0] && command[i+2] == txt[1] && command[i+3] == txt[2] && command[i+4] == '\0')){
						flag2 = 0;
						break;
					}
				}
			}
			if(flag2 == 1){
				load_name = command.substr(first+2,last);
				operation = 1;
				flag = 0;
			}
			else{
				cerr<<"\nThis is not txt file.";
				flag = 0;
			}
		}
	}

	for(int i =0,counter=0; command[i]!= '\0' ; i++);
	{
		counter++;
	}
	// CONTROL THE COORDİNATE THAT TAKEN FROM THE USER
	if(flag == 1 && counter != 4 && ((command[2]>='1' && command[2]<='9') || command[2] == '\0') 
			&& (command[1]>='1' && command[1]<='9') && (command[0]>='A' && command[0]<='Z') ){
			for(int i =0; command[i] != '\0' ; i++)
				last = i;
			character = command[0];
			first = 1;
			row = command.substr(first,last);
			stringstream geek(row);
			geek>>roww;
			operation = 2;
	}

	return operation;
}

//THIS FUNCTION SAVE AND LOAD FUNCTION
int file_operation(int &operation,string &file_name,int &game_style,enum player player_turn,int &size,char **map,int &cmp_row,int &cmp_col)
{
	string line;
	string num;
	int counter;
	int temp=0;
	int first,last;
	int player;
	
	if(player_turn == player1)
		player =1;
	else if(player_turn == player2)
		player =2;
		
	// S A V E  FILE
	if(operation == 0)
	{
		ofstream savefile(file_name);
	
		  if (savefile.is_open())
		  {
		    savefile << "Game_Style:"<<game_style<<endl;
		    savefile << "Player_Turn:"<<player<<endl;
		    if(game_style == 2)
		    {
			    savefile << "CMP_ROW:"<<cmp_row<<endl;
			    savefile << "CMP_COL:"<<cmp_col<<endl;
		    }
		    savefile << "Size:"<<size<<endl;
		    savefile << "Board:\n";
		    for(int i = 0; i<size ; ++i)
		    {
		    	for(int j = 0; j<size ; ++j)
		    	{
		    		savefile<<map[i][j];
		    	}
		    	savefile<<endl;
		    }
		    
		    savefile.close();
		  }
		  else cerr << "Unable to open file";		
	}
	//L O A D  FILE
	else if(operation == 1)
	{
		ifstream loadfile(file_name);
		
		  if (loadfile.is_open())
		  {counter = 0;
		    while ( getline (loadfile,line) )
		    {	
		    	counter++;
		    	if( (counter<4 && game_style == 1)  || (game_style == 2 && counter < 6)){
					for(int i =0; line[i] != '\0' ; i++){
						if(line[i]==':'){
							first = i+1;
						}
						last = i;
					}
					num = line.substr(first,last);
					stringstream geek(num);
					if(counter == 1)
						geek>>game_style;
					if(counter == 2){
						geek>>player;
					}
					if(counter == 3 && game_style == 2){
						geek>>cmp_row;
					}
					if(counter == 4 && game_style == 2){
						geek>>cmp_col;
					}
					if( (counter == 3 && game_style == 1) || (counter == 5 && game_style == 2) )
						geek>>size;			
		    	}
		    	else if( (counter > 4 && game_style == 1) || (game_style == 2 && counter > 6) ){
		    		for(int i=0;line[i] != '\0' ; ++i)
		    		{
		    			map[temp][i]= line[i];
		    		}
		    		temp++;
		    	}
		    }
		    
		    loadfile.close();
		  }
		  else cout << "Unable to open file\n"; 
		  
	}	
	
	if( (player_turn == player1 && player == 2 )|| (player_turn == player2 && player == 1 ))
		return 1;
	else 
		return 0;
}

