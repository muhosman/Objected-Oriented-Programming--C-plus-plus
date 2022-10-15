 //============================================================================
// Name        : main.cpp
// Author      : Osman
// Description : Homework 3
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

char alphabet[27] = "ABCDEFGHIJKLMNOPRSQTUVWXYZ";

class CELL{
public:
	enum type_cell{
		player1='X',player2='O',dot='.',comma=','
	};
	void set_cell(int input)
	{
		if (input == 1) {
			type = dot;
		}
		else if (input == 2) {
			type = comma;
		}
		else if (input == 3) {
			type = player1;
		}
		else if (input == 4) {
			type = player2;
		}
	}
	void set_row(int x)
	{
		row = x;
	}
	void set_column(char y)
	{
		column = y;
	}

	char get_type() const
	{
		return type;
	}

	char get_column() const
	{
		return column;
	}
	char get_row() const
	{
		return row;
	}

private:

	char type;
	char column;
	int row;
};


class HEX{
public:
	CELL **hexCells;

	explicit HEX(int size_Value,int flag_value);
	explicit HEX(int size_Value);
	explicit HEX();
	explicit HEX(const HEX& OBJECT);

	void deleteCELL();
	void makeCELL();

	void play_Game();

	void print_bord() const;
	void fill_CELL();

	bool player_move(int input,int &row,char &col);
	bool computer_move();

	bool control_end_of_Game(char type,int control,int roww,int column);
	bool control_score(char type,int control,int roww,int column);

	void operation_control(int &row,char &col);
	bool load_operation(std::string command,char load[5],char txt[4]);
	bool save_operation(std::string command,char save[5],char txt[4]);
	bool menu_operation(std::string command,char menu[5]);
	bool coordinate_operation(std::string command,int &row,char &col);
	bool file_operation(char player_turn);
	friend bool operator ==(const HEX& Game1,const HEX& Game2);
	void test_value();
	friend ostream& operator<<(ostream& outputstream,const HEX& hexGame);
	friend istream& operator>>(istream& inputstream,HEX& hexGame);

	friend ifstream& operator>>(ifstream& inputstream,HEX& hexGame);
	friend ofstream& operator<<(ofstream& outputstream,HEX& hexGame);

	void set_size(int input);
	void set_game_style(int input);
	void set_score(int input)
	{
		score = (input+1)*10;
	}
	void set_score2(int input)
	{
		score2 = (input+1)*10;
	}
	void set_active()
	{
		active = 1;
	}
	void set_marked_specific()
	{
		marked_specific++;
	}
	int get_marked_specific()
	{
		return marked_specific;
	}
	char get_alphabet(const int input) const
	{
		return alphabet[input];
	}
	int get_Width() const
	{
		return size;
	}
	int get_height() const
	{
		return size;
	}
	int get_game_style() const
	{
		return game_style;
	}
	int get_size() const
	{
		return size;
	}
	int get_operation() const
	{
		return operation;
	}
	int get_cmp_row() const
	{
		return cmp_row;
	}
	int get_cmp_col() const
	{
		return cmp_col;
	}
	int get_active() const
	{
		return active;
	}
	int get_flag() const
	{
		return flag;
	}
	int get_score() const
	{
		return score;
	}
	int get_score2() const
	{
		return score2;
	}
	static int get_marked()
	{
		marked++;
		return marked;
	}
	~HEX();

private:

	static int marked;
	int marked_specific;
	int flag;
	int active;
	int first_computer_move;
	int player;

	int score;
	int score2;
	int size;
	int game_style;
	int cmp_row;
	int cmp_col;
	int operation;
	string save_name;
	string load_name;
};

int HEX::marked = 0;


ostream& operator<<(ostream& outputstream,const HEX& hexGame)
{
	for (int i = 0; i < hexGame.get_size(); i++)
	{
		outputstream << " " << hexGame.get_alphabet(i);
	}
	outputstream << endl;
	for (int i = 0; i < hexGame.get_size(); i++)
	{
		outputstream << i+1;
		for (int k = 0; k < i; k++)
		{
			outputstream << " ";
		}
		for (int j = 0; j < hexGame.get_size(); j++)
		{
			outputstream << hexGame.hexCells[i][j].get_type() <<" ";
		}
		outputstream << endl;
	}
	return outputstream;
}
istream& operator>>(istream& inputstream,HEX& hexGame)
{
	int input;
	do
	{
		cout << "\nEnter The Game Of Sıze:";
		if (!(inputstream >> input)) {
			inputstream.clear();
			inputstream.ignore(10000,'\n');
		}
		hexGame.set_size(input);
		if (hexGame.get_size() > 26 || hexGame.get_size() <= 5)
			cout << "Fault ! Enter again ! Size should be between 6 and 26.";
	} while (hexGame.get_size()>26 || hexGame.get_size()<=5);
}

ifstream& operator>>(ifstream& inputstream,HEX& hexGame)
{
	string line;
	string num;
	int counter;
	int temp=0;
	int first,last;

	counter = 0;
		while ( getline (inputstream,line) )
		{
			counter++;
			if( (counter<4 && hexGame.game_style == 1)  || (hexGame.game_style == 2 && counter < 6)){
				for(int i =0; line[i] != '\0' ; i++){
					if(line[i]==':'){
						first = i+1;
					}
					last = i;
				}
				num = line.substr(first,last);
				stringstream geek(num);
				if(counter == 1)
					geek>>hexGame.game_style;
				if(counter == 2){
					geek>>hexGame.player;
				}
				if(counter == 3 && hexGame.game_style == 2){
					geek>>hexGame.cmp_row;
				}
				if(counter == 4 && hexGame.game_style == 2){
					geek>>hexGame.cmp_col;
				}
				if( (counter == 3 && hexGame.game_style == 1) || (counter == 5 && hexGame.game_style == 2) ){
					hexGame.deleteCELL();
					geek>>hexGame.size;
					hexGame.makeCELL();
				}
			}
			else if( (counter > 4 && hexGame.game_style == 1) || (hexGame.game_style == 2 && counter > 6) ){
				for(int i=0;line[i] != '\0' ; ++i)
				{
					if (line[i] == '.') {
						hexGame.hexCells[temp][i].set_cell(1);
					}
					else if (line[i] == 'X') {
						hexGame.hexCells[temp][i].set_cell(3);
					}
					else if (line[i] == 'O') {
						hexGame.hexCells[temp][i].set_cell(4);
					}
				}
				temp++;
			}
		}

		return inputstream;
}
ofstream& operator<<(ofstream& outputstream,HEX& hexGame)
{
	string line;
	string num;
	int counter;
	int temp=0;
	int first,last;

	outputstream << "Game_Style:"<<hexGame.game_style<<endl;
	outputstream << "Player_Turn:"<<hexGame.player<<endl;
	if(hexGame.game_style == 2)
	{
		outputstream << "CMP_ROW:"<<hexGame.cmp_row<<endl;
		outputstream << "CMP_COL:"<<hexGame.cmp_col<<endl;
	}
	outputstream << "Size:"<<hexGame.get_size()<<endl;
	outputstream << "Board:\n";
	for(int i = 0; i<hexGame.get_size() ; ++i)
	{
		for(int j = 0; j<hexGame.get_size() ; ++j)
		{
			outputstream<<hexGame.hexCells[i][j].get_type();
		}
		outputstream<<endl;
	}
	return outputstream;
}


int main()
{
	int game_counter=0;
	int input,input1,input2;
	vector<HEX> GAME;

	do {
		cout<<"MENU\n";
		cout<<"1.New Game\n";
		cout<<"2.Choice Active Game\n";
		cout<<"3.Game Compare\n";
		cout<<"4.EXIT\n";
		cout<<"\nYour choice (EXMP:1-2-3):";
		if (!(cin >> input)) {
			cin.clear();
			cin.ignore(10000,'\n');
    }
		switch (input) {
			case 1:
				game_counter++;
				GAME.resize(game_counter);
				GAME[game_counter-1].play_Game();
			break;
			case 2:
				do {
					if (game_counter==0) {
						cout<<"There are not any active game.\n\n";
						break;
					}
					for (int i = 0; i < game_counter; i++) {
						cout<<i<<"-GAME\n";
					}
					cout<<"\nChoice(EXMP:0OR1OR2):";
					if (!(cin >> input1)) {
						cin.clear();
						cin.ignore(10000,'\n');
					}
					if (input1>=0 && input1<game_counter) {
						GAME[input1].play_Game();
					}
					else
						cout<<"Did not find any game!\n\n";
				}while(!(input1>=0 && input1<game_counter));
			break;
			case 3:
				do {
					if (game_counter==1 || game_counter == 0) {
						cout<<"There are not enough any active game.\n\n";
						break;
					}
					for (int i = 0; i < game_counter; i++) {
						cout<<i<<"-GAME\n";
					}
					cout<<"\nFirst Choice(EXMP:0OR1OR2):";
					if (!(cin >> input1)) {
						cin.clear();
						cin.ignore(10000,'\n');
					}
					cout<<"\nSecond Choice:";
					if (!(cin >> input2)) {
						cin.clear();
						cin.ignore(10000,'\n');
					}
					if (input1>=0 && input1<game_counter && input2>=0 && input2<game_counter && input1 != input2) {
						if(GAME[input1]==GAME[input2])
							cout<<"Result:"<<input1<<">"<<input2<<endl;
						else
							cout<<"Result:"<<input1<<"<="<<input2<<endl<<endl;
					}
					else
						cout<<"Fault Choice!\n\n";
				}while(!(input1>=0 && input1<game_counter));
			break;
			case 4:
			break;
			default:
				cout<<"False choice! Try Again.";
			break;
		}
	} while(input != 4);

	return 0;
}

HEX::HEX(int size_Value,int flag_value):size(size_Value),flag(flag_value)
{
	test_value();
	marked_specific = 0;
	active = 0;
	first_computer_move=0;
}
HEX::HEX(int size_Value):size(size_Value),flag(0)
{
	test_value();
	marked_specific = 0;
	active = 0;
	first_computer_move=0;
}
HEX::HEX():size(0),flag(0)
{
	marked_specific = 0;
	active = 0;
	first_computer_move=0;
}
HEX::HEX(const HEX& OBJECT):size(OBJECT.get_size())
{
	hexCells = new CELL*[size];
	for (int i = 0; i < size; i++) {
		hexCells[i] = new CELL[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			hexCells[i][j].set_row(OBJECT.hexCells[i][j].get_row());
			hexCells[i][j].set_column(OBJECT.hexCells[i][j].get_column());
		}
	}
}

HEX::~HEX()
{
	for (int i = 0; i < get_size(); i++) {
		delete []hexCells[i];
	}
	delete []hexCells;
}
bool operator ==(const HEX& Game1,const HEX& Game2)
{
	if (Game1.marked_specific > Game2.marked_specific )
		return 1;
	else
		return 0;
}


void HEX::deleteCELL()
{
	for (int i = 0; i < get_size(); i++) {
		delete []hexCells[i] ;
	}
	delete []hexCells;
}

void HEX::makeCELL()
{
	hexCells = new CELL*[get_size()];
	for (int i = 0; i < get_size(); i++) {
		hexCells[i] = new CELL[get_size()];
	}
}

//Control board size and flag value
void HEX::test_value()
{
	if (get_size()<6 || get_size()>26 || flag != 0) {
		cerr<<"Program aborted !";
		exit(1);
	}
}

//Main function for playing game
void HEX::play_Game()
{
	int input;
	bool control;
	char col;
	int row;
	int menu=0;

	if (get_active() == 0) {
		//Take the Game Of Size
		cin >> *this;


		// Take The Input From User Type of Game
		do
		{
			cout << "\nEnter The Type Of Game" << endl << "1-P VS P\n2- P VS C \nWrite 1 OR 2:";
			if (!(cin >> input)) {
				cin.clear();
				cin.ignore(10000,'\n');
			}
			set_game_style(input);
			if (get_game_style() != 1 && get_game_style() != 2)
				cerr << "Fault ! Enter again ! Game style should be 1 or 2.";
		} while (game_style != 1 && game_style != 2);

		makeCELL();

		fill_CELL();
		set_active();
		print_bord();
	}
	else
	{
		cout<<"\nSize:"<<get_size();
		cout<<"\nGame Style:"<<get_game_style()<<endl;

		print_bord();

		//Control MAP For end of the game
		for(int i = 0;i<get_size();i++){
			if('X' == hexCells[i][0].get_type()){
				hexCells[i][0].set_cell(2);
				flag = control_end_of_Game('X',0,i,0);
				hexCells[i][0].set_cell(3);
				if(get_flag() == 1){
					cout<<"\nThis game is finished ! \n";
					break;
				}
			}
		}
		if (get_flag() != 1) {
			for(int i = 0;i<get_size();i++){
				if('O' == hexCells[0][i].get_type()){
					hexCells[0][i].set_cell(2);
					flag = control_end_of_Game('O',0,0,i);
					hexCells[0][i].set_cell(4);
					if(flag == 1&&game_style == 2){
						cout<<"\nThis game is finished !\n";
						break;
					}
					if(flag == 1&&game_style == 1){
						cout<<"\nThis game is finished !\n";
						break;
					}
				}
			}
		}

	}

	//STARTING THE GAME
	if (get_flag() != 1) {
		do{
				//Mover Player 1
				do{
					cout<<"\nPLAYER 1 // Enter The Column and The Row or LOAD or SAVE or MENU command line(EXMP : C7):";
					operation_control(row,col);
					control = 1;

					if(get_operation() == 0){
						cout<<"File is saving... ="<<save_name<<endl;
						control = file_operation('X');
					}
					else if(get_operation() == 1){
						cout<<"\nFile is loading... ="<<load_name<<endl;
						control = file_operation('X');
						cout<<"Size:"<<get_size();
						cout<<"\nGame Style:"<<get_game_style()<<endl;
						cout<<"Marked Counter:"<< get_marked() <<endl;
						print_bord();

						if(get_game_style() == 2)
						{
							if (hexCells[0][get_size()-1].get_type() == '.' && hexCells[0][get_size()-2].get_type() == '.' ) {
								first_computer_move = 0;
							}
							else
							{
								first_computer_move = 1;
							}
						}
						if (control == 1 || get_flag() == 1) {
							break;
						}

					}
					else if(get_operation() == 2){
						control = player_move(3,row,col);
						if(control == 0)
							cout<<"It is not valid coordinate. Enter valid coordinate."<<endl;
						else{
							cout<<"Marked Counter:"<< get_marked() <<endl;
							set_marked_specific();
							print_bord();
						}
					}
					else if(get_operation() == 3){
						control= 0;
						cout<<"This command line is not true."<<endl;
					}
					else if (get_operation() == 4) {
						menu=1;
						break;
					}
				}while(control == 0);

				if(menu == 1 || get_flag() == 1)
					break;

				score = 0;
				for (int i = 0; i < get_size(); i++)
				{
					for (int j = get_size()-1; j >= 0; j--)
					{
						if('X' == hexCells[i][j].get_type() && ( get_score() < ((j+1)*10) ))
						{
							if(control_score('X',0,i,j))
							{
								set_score(j);
								break;
							}
							else if(j == 0 && ( get_score() < ((j+1)*10) ) )
							{
								set_score(j);
								break;
							}
						}
					}
				}
				cout<<"Score P1:"<<get_score()<<'\n';
				if(get_score() == get_size()*10)
				{
					cout << "Player1 Win !" << '\n';
					break;
				}

				//if game_style is two put the first move computer
				if(first_computer_move == 0 && game_style == 2 && flag != 1){
					if(hexCells[0][get_size()-1].get_type() == '.'){
						hexCells[0][get_size()-1].set_cell(4);
						cmp_row = 0;
						cmp_col = get_size()-1;
						cout<<"Marked Counter:"<< get_marked() <<endl;
						set_marked_specific();

					}

					else{
						hexCells[0][get_size()-2].set_cell(4);
						cmp_row = 0;
						cmp_col = get_size()-2;
						cout<<"Marked Counter:"<< get_marked() <<endl;
						set_marked_specific();

					}
					print_bord();
					first_computer_move = 1;
				}
				else if(get_game_style() == 1 && get_flag() != 1)
				{
					do{
						cout<<"\nPLAYER 2 //  Enter The Column and The Row or LOAD or SAVE or MENU command line(EXMP : C7):";
						operation_control(row,col);
						if(get_operation() == 0){
							cout<<"File is saving... ="<<save_name<<endl;
							control = file_operation('O');
						}
						else if(get_operation() == 1){
							cout<<"\nFile is loading... ="<<load_name<<endl;
							control = file_operation('O');
							cout<<"Size:"<<get_size();
							cout<<"\nGame Style:"<<get_game_style()<<endl;
							cout<<"Marked Counter:"<< get_marked() <<endl;

							print_bord();

							if(get_game_style() == 2)
							{
								if (hexCells[0][get_size()-1].get_type() == '.' && hexCells[0][get_size()-2].get_type() == '.' ) {
									first_computer_move = 0;
								}
								else
								{
									first_computer_move = 1;
								}
							}
							if (control == 1 || get_flag() == 1) {
								break;
							}

						}
						else if(get_operation() == 2){
							control = player_move(4,row,col);
							if(control == 0)
								cout<<"It is not valid coordinate. Enter valid coordinate."<<endl;
							else{
								cout<<"Marked Counter:"<< get_marked() <<endl;
								set_marked_specific();

								print_bord();
							}
						}
						else if(get_operation() == 3){
							control= 0;
							cout<<"This command line is not true.";
						}
						else if (get_operation() == 4) {
							menu=1;
							break;
						}
					}while(control == 0);
				}//Computer
				else if(get_game_style() == 2 && get_flag() != 1)
				{
					computer_move();
					cout<<"\nComputer move : "<<get_alphabet(cmp_col)<<get_cmp_row()+1	<<endl;
					cout<<"Marked Counter:"<< get_marked() <<endl;
					set_marked_specific();
					print_bord();
				}

				score2 = 0;
				for (int i = 0; i < get_size(); i++)
				{
					for (int j = get_size()-1; j >= 0; j--)
					{
						if('O' == hexCells[j][i].get_type() && ( get_score2() < ((j+1)*10) ))
						{
							if(control_score('O',0,j,i))
							{
								set_score2(j);
								break;
							}
							else if(j == 0 && ( get_score2() < ((j+1)*10) ) )
							{
								set_score2(j);
								break;
							}
						}
					}
				}
				cout<<"Score P2:"<<get_score2()<<'\n';
				if(get_score2() == get_size()*10)
				{
					cout << "Player2 Win !" << '\n';
					break;
				}

					if(menu == 1 || get_flag() == 1)
						break;

		}while(get_flag() != 1);
	}
	else
		cout<<"This game finished.\n";

}
//Take input and assign to game_style
void HEX::set_game_style(int input)
{
	game_style = input;
	if (get_game_style() == 1)
		cout << "The Player and Player Game is starting...\n" << endl;

	else if (get_game_style() == 2)
	{
		cout << "The Player and Computer Game is starting...\n" << endl;
	}
	else{
		cerr << '\n'; "Illegal Game_Style !\n";
	}
}
//Take input and assign to size
void HEX::set_size(int input)
{
	size = input;
	if (size > 27 || size < 6){
		cerr << "Illegal game size !\n";
	}
}
void HEX::fill_CELL()
{
	for (int i = 0; i < get_size(); i++)
	{
		for (int j = 0; j < get_size(); j++)
		{
			hexCells[i][j].set_row(i+1);
			hexCells[i][j].set_column(alphabet[j]);
			hexCells[i][j].set_cell(1);
		}
	}
}
void HEX::print_bord() const
{
	cout<<*this;
}
//LOAD OR MENU OR SAVE OR COORDINATE
void HEX::operation_control(int &row,char &col)
{
	std::string command;
	char save[5] = "SAVE";
	char load[5] = "LOAD";
	char menu[5] = "MENU";
	char txt[4] = "TXT";

	int first,last;
	bool flag1 = 0 ;
	operation = 3;

	cin>>ws;
	getline(std::cin,command);

	//CONTROL THE MENU COMMAND THAT TAKEN FROM THE USER
	if(flag1 == 0){
		flag1 = menu_operation(command,menu);
		if(flag1 == 1)
			operation = 4;
	}
	//CONTROL THE SAVE COMMAND THAT TAKEN FROM THE USER
	if(flag1 == 0){
		flag1 = save_operation(command,save,txt);
		if(flag1 == 1)
			operation = 0;
	}
	//CONTROL THE LOAD COMMAND THAT TAKEN FROM THE USER
	if(flag1 == 0){
		flag1 = load_operation(command,load,txt);
		if(flag1 == 1)
			operation = 1;
	}
	// CONTROL THE COORDİNATE THAT TAKEN FROM THE USER
	if(flag1 == 0 && ((command[2]>='0' && command[2]<='9') || command[2] == '\0')
			&& (command[1]>='1' && command[1]<='9') && (command[0]>='A' && command[0]<='Z') ){
			flag1 =coordinate_operation(command,row,col);
	}
}
bool HEX::menu_operation(std::string command,char menu[5])
{
		int first,last;
		int counter = 0;

		for(int i=0;command[i] != ' ' && command[i] != '\0';i++)
		{
			if(menu[i] == command[i])
			{
				counter++;
				first = i;
			}
			else{
				return 0;
			}
		}
		return 1;
}
bool HEX::load_operation(std::string command,char load[5],char txt[4])
{
		int first,last;
		int counter = 0;
		int flag1;

		for(int i=0;command[i] != ' ' && command[i] != '\0';i++)
		{
			if(load[i] == command[i])
			{
				counter++;
				first = i;
			}
			else{
				return 0;
			}
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
				load_name = command.substr(first+2,last);
				operation = 1;
				return 1;
			}
			else{
				cerr<<"\nThis is not txt file for LOAD.";
				return 0;
			}
		}

}
bool HEX::save_operation(std::string command,char save[5],char txt[4])
{
		int first,last;
		int counter = 0;
		int flag1;


		for(int i=0;command[i] != ' ' && command[i] != '\0';i++)
		{
			if(save[i] == command[i])
			{
				counter++;
				first = i;
			}
			else{
				return 0;
			}
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
			if(flag1 == 1){			std::cout<<"SAVE NAME"<<endl;

				save_name = command.substr(first+2,last);
				operation = 0;
				return 1;
			}
			else{
				cerr<<"\nThis is not txt file for SAVE.";
				return 0;
			}
		}
}

bool HEX::coordinate_operation(string command,int &row,char &col)
{
	int first,last;
	string roww;

	for(int i =0; command[i] != '\0' ; i++)
		last = i;
	col = command[0];
	first = 1;
	roww = command.substr(first,last);
	stringstream geek(roww);
	geek>>row;
	operation = 2;

}

bool HEX::player_move(int input,int &row,char &col)
{
	for (int i = 0; i < get_size(); i++) {
		for (int j = 0; j < get_size(); j++) {
			hexCells[i][j].set_row(i+1);
			hexCells[i][j].set_column(alphabet[j]);

		}
	}
	for(int i=0; i<get_size(); ++i)
	{
		for (int j = 0; j < get_size(); j++) {
			if(col == hexCells[i][j].get_column() && row >=1 && row <= get_size() && row == hexCells[i][j].get_row() && hexCells[i][j].get_type() == '.'){
				hexCells[i][j].set_cell(input);
				return 1;
			}
		}
	}
	return 0;
}

bool HEX::control_end_of_Game(char type,int control,int roww,int column)
{
	int flag1 = 0;
		if(roww > 0)
			if(control != 1 && hexCells[roww-1][column].get_type() == type && flag1 == 0)
				{
					hexCells[roww-1][column].set_cell(2);
					if(type == 'X' && column == get_size()-1){
						hexCells[roww-1][column].set_cell(3);
						return 1;
					}
					if(type == 'O' && roww-1 == get_size()-1){
						hexCells[roww-1][column].set_cell(4);
						return 1;
					}
					flag1 = control_end_of_Game(type,4,roww-1,column);

						if (type == 'X') {
							hexCells[roww-1][column].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww-1][column].set_cell(4);
						}
				}

		if(column > 0)
			if(control != 6 && hexCells[roww][column-1].get_type() == type && flag1 == 0)
				{
					hexCells[roww][column-1].set_cell(2);
					if(type == 'X' && column-1 == get_size()-1){
						hexCells[roww][column-1].set_cell(3);
						return 1;
					}
					if(type == 'O' && roww == get_size()-1){
						hexCells[roww][column-1].set_cell(4);
						return 1;
					}

					flag1 = control_end_of_Game(type,3,roww,column-1);

						if (type == 'X') {
							hexCells[roww][column-1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww][column-1].set_cell(4);
						}
				}

		if(roww < get_size()-1)
			if(control != 4 && hexCells[roww+1][column].get_type() == type && flag1 == 0)
				{
					hexCells[roww+1][column].set_cell(2);
					if(type == 'X' && column == get_size()-1){
						hexCells[roww+1][column].set_cell(3);
						return 1;
					}
					if(type == 'O' && roww+1 == get_size()-1){
						hexCells[roww+1][column].set_cell(4);
						return 1;
					}

					flag1 = control_end_of_Game(type,1,roww+1,column);

						if (type == 'X') {
							hexCells[roww+1][column].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww+1][column].set_cell(4);
						}
				}
		if(column < get_size()-1)
			if(control != 6 && hexCells[roww][column+1].get_type() == type && flag1 == 0)
				{
					hexCells[roww][column+1].set_cell(2);
					if(type == 'X' && column+1 == get_size()-1){
						hexCells[roww][column+1].set_cell(3);
						return 1;
					}
					if(type == 'O' && roww == get_size()-1){
						hexCells[roww][column+1].set_cell(4);
						return 1;
					}

					flag1 = control_end_of_Game(type,3,roww,column+1);

						if (type == 'X') {
							hexCells[roww][column+1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww][column+1].set_cell(4);
						}
				}
		if(roww>0 && column<get_size()-1)
			if(control != 2 && hexCells[roww-1][column+1].get_type() == type && flag1 == 0)
				{
					hexCells[roww-1][column+1].set_cell(2);
					if(type == 'X' && column+1 == get_size()-1){
						hexCells[roww-1][column+1].set_cell(3);
						return 1;
					}
					if(type == 'O' && roww-1 == get_size()-1){
						hexCells[roww-1][column+1].set_cell(4);
						return 1;
					}

					flag1 = control_end_of_Game(type,5,roww-1,column+1);

						if (type == 'X') {
							hexCells[roww-1][column+1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww-1][column+1].set_cell(4);
						}
				}

		if(roww<get_size()-1 && column>0)
			if(control != 5 && hexCells[roww+1][column-1].get_type() == type && flag1 == 0)
				{
					hexCells[roww+1][column-1].set_cell(2);
					if(type == 'X' && column-1 == get_size()-1){
						hexCells[roww+1][column-1].set_cell(3);
						return 1;
					}
					if(type == 'O' && roww+1 == get_size()-1){
						hexCells[roww+1][column-1].set_cell(4);
						return 1;
					}

					flag1 = control_end_of_Game(type,2,roww+1,column-1);

						if (type == 'X') {
							hexCells[roww+1][column-1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww+1][column-1].set_cell(4);
						}
				}


	return flag1;
}

bool HEX::computer_move()
{
	if(get_cmp_row() < get_size()-1){
		if(hexCells[cmp_row+1][cmp_col].get_type() == '.'){
			hexCells[cmp_row+1][cmp_col].set_cell(4);
			cmp_row++;
			return 1;
		}
	}
	if(get_cmp_row()<get_size()-1 && get_cmp_col()>0){
		if(hexCells[cmp_row+1][cmp_col-1].get_type() == '.'){
			hexCells[cmp_row+1][cmp_col-1].set_cell(4);
			cmp_row++;
			cmp_col--;
			return 1;
		}
	}
	if(get_cmp_col() > 0){
		if(hexCells[cmp_row][cmp_col-1].get_type() == '.'){
			hexCells[cmp_row][cmp_col-1].set_cell(4);
			cmp_col--;
			return 1;
		}
	}
	if(get_cmp_row() > 0){
		if(hexCells[cmp_row-1][cmp_col].get_type() == '.'){
			hexCells[cmp_row-1][cmp_col].set_cell(4);
			cmp_row--;
			return 1;
		}
	}
	if(get_cmp_row()>0 && get_cmp_col()<get_size()-1){
		if(hexCells[cmp_row-1][cmp_col+1].get_type() == '.'){
			hexCells[cmp_row-1][cmp_col+1].set_cell(4);
			cmp_row++;
			cmp_row--;
			return 1;
		}
	}
	if(get_cmp_col() < get_size()-1){
		if(hexCells[cmp_row][cmp_col+1].get_type() == '.'){
			hexCells[cmp_row][cmp_col+1].set_cell(4);
			cmp_col++;
			return 1;
		}
	}

	return 0;
}

bool HEX::file_operation(char player_turn)
{

	string line;
	string num;
	int counter;
	int temp=0;
	int first,last;

	if(player_turn == 'X')
		player =1;
	else if(player_turn == 'O')
		player =2;

	// S A V E  FILE
	if(operation == 0)
	{
		ofstream savefile(save_name);

		  if (savefile.is_open())
		  {
				savefile<<*this;
		    savefile.close();
		  }
		  else
			 cerr << "Unable to open file";
	}
	//L O A D  FILE
	else if(operation == 1)
	{
		ifstream loadfile(load_name);

		  if (loadfile.is_open())
		  {
				loadfile>>*this;
		    loadfile.close();
		  }
		  else {
				cout << "Unable to open file\n";
				exit(1);
			}
	}

	//Control MAP For end of the game
	for(int i = 0;i<get_size();i++){
		if('X' == hexCells[i][0].get_type()){
			hexCells[i][0].set_cell(2);
			flag = control_end_of_Game('X',0,i,0);
			hexCells[i][0].set_cell(3);
			if(get_flag() == 1){
				cout<<"\nThis game is finished ! \n";
				break;
			}
		}
	}
	if (get_flag() != 1) {
		for(int i = 0;i<get_size();i++){
			if('O' == hexCells[0][i].get_type()){
				hexCells[0][i].set_cell(2);
				flag = control_end_of_Game('O',0,0,i);
				hexCells[0][i].set_cell(4);
				if(flag == 1&&game_style == 2){
					cout<<"\nThis game is finished !\n";
					print_bord();
					break;
				}
				if(flag == 1&&game_style == 1){
					cout<<"\nThis game is finished !\n";
					break;
				}
			}
		}
	}

	//Map is full or not full control

	marked = marked - marked_specific;
	marked_specific = 0;

	for(int i=0;i<size;i++){
		for(int j=0 ; j<size; j++)
		{
			if( hexCells[i][j].get_type() != '.')
			{
				set_marked_specific();
			}
		}
	}
	marked = marked + marked_specific -1;

	if( (player_turn == 'X' && player == 2 )|| (player_turn == 'O' && player == 1 ))
		return 1;
	else
		return 0;
}

bool HEX::control_score(char type,int control,int roww,int column)
{
	int flag1 = 0;
		if(roww > 0)
			if(control != 1 && hexCells[roww-1][column].get_type() == type && flag1 == 0)
				{
					hexCells[roww-1][column].set_cell(2);

					if(type == 'O' && roww-1 == 0){
						hexCells[roww-1][column].set_cell(4);
						return 1;
					}
					flag1 = control_score(type,4,roww-1,column);

						if (type == 'X') {
							hexCells[roww-1][column].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww-1][column].set_cell(4);
						}
				}

		if(column > 0)
			if(control != 6 && hexCells[roww][column-1].get_type() == type && flag1 == 0)
				{
					hexCells[roww][column-1].set_cell(2);

					if(type == 'X' && column-1 == 0){
						hexCells[roww][column-1].set_cell(3);
						return 1;
					}

					flag1 = control_score(type,3,roww,column-1);

						if (type == 'X') {
							hexCells[roww][column-1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww][column-1].set_cell(4);
						}
				}

		if(roww < get_size()-1)
			if(control != 4 && hexCells[roww+1][column].get_type() == type && flag1 == 0)
				{
					hexCells[roww+1][column].set_cell(2);

					flag1 = control_score(type,1,roww+1,column);

						if (type == 'X') {
							hexCells[roww+1][column].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww+1][column].set_cell(4);
						}
				}
		if(column < get_size()-1)
			if(control != 6 && hexCells[roww][column+1].get_type() == type && flag1 == 0)
				{
					hexCells[roww][column+1].set_cell(2);

					flag1 = control_score(type,3,roww,column+1);

						if (type == 'X') {
							hexCells[roww][column+1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww][column+1].set_cell(4);
						}
				}
		if(roww>0 && column<get_size()-1)
			if(control != 2 && hexCells[roww-1][column+1].get_type() == type && flag1 == 0)
				{
					hexCells[roww-1][column+1].set_cell(2);

					if(type == 'O' && roww-1 == 0){
						hexCells[roww-1][column+1].set_cell(4);
						return 1;
					}

					flag1 = control_score(type,5,roww-1,column+1);

						if (type == 'X') {
							hexCells[roww-1][column+1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww-1][column+1].set_cell(4);
						}
				}

		if(roww<get_size()-1 && column>0)
			if(control != 5 && hexCells[roww+1][column-1].get_type() == type && flag1 == 0)
				{
					hexCells[roww+1][column-1].set_cell(2);

					if(type == 'X' && column-1 == 0){
						hexCells[roww+1][column-1].set_cell(3);
						return 1;
					}

					flag1 = control_score(type,2,roww+1,column-1);

						if (type == 'X') {
							hexCells[roww+1][column-1].set_cell(3);
						}
						if (type == 'O') {
							hexCells[roww+1][column-1].set_cell(4);
						}
				}


	return flag1;
}
