#include "hexClass.h"
using namespace hexClass;

AbstractHex::AbstractHex()
{

}
void AbstractHex::Game()
{
  if (get_active() == 0) {
    set_active(1);
    setsize();
    setGamestyle();
    fill_cell();
  }
  set_operation(control_endgame_x());
  if (get_operation() != 1)
    set_operation(control_endgame_y());

  cout<<"Size : "<<getSize()<<endl;
  cout<<"Gamestyle : "<<getGamestyle()<<endl;
  print();
  cout<<endl;

  if (get_operation() != 1) {
    try{
      if (getGamestyle() == 1) {
        do {
          player_move('X');
          print();
          if (get_operation() == 2) {
            break;
          }
          operation = control_endgame_x();
          if (get_operation() == 1) {
            break;
          }

          player_move('O');
          print();
          if (get_operation() == 2) {
            break;
          }
          operation = control_endgame_y();
          if (get_operation() == 1) {
            break;
          }
        } while(1);
      }

      else if (getGamestyle() == 2) {

        do {
          player_move('X');
          print();
          if (get_operation() == 2) {
            break;
          }
          operation = control_endgame_x();
          if (get_operation() == 1) {
            break;
          }

          if (get_first_cmp_move() == 0) {
            first_computer_move();
            set_first_cmp_move(1);
          }
          else if (first_cmp_move == 1) {
            play_for_computer();
          }
          print();
          if (get_operation() == 2) {
            break;
          }
          operation = control_endgame_y();
          if (get_operation() == 1) {
            break;
          }
        } while(1);
      }
    }
    catch(FileError)
    {
      cout<<"File didn't open !\n";
      exit(1);
    }
    catch(BoardError)
    {
      cout<<"File read board that doesn't convenient !\n";
      exit(1);
    }
  }
}

bool AbstractHex::operator== (AbstractHex &Game)
{
  if (getSize() != Game.getSize()) {
    return 0;
  }
  else if (getGamestyle() != Game.getGamestyle()) {
    return 0;
  }

  for (int i = 0; i < getSize(); i++) {
    for (int j = 0; j < getSize(); j++) {
      if ((*this)(i,j) != Game(i,j)) {
        return 0;
      }
    }
  }
  return 1;

}

void AbstractHex::player_move(char player)
{

  do{
    take_operation(player);
  }while(get_operation() == 0);
}

void AbstractHex::take_operation(char player)
{
	string command;
	char save[5] = "SAVE";
	char load[5] = "LOAD";
	char menu[5] = "MENU";
	char txt[4] = "TXT";

  int row,colu;
	int first,last;
	bool flag = 0 ;

  if (player== 'X') {
    cout<<"PLAYER 1 // Enter The Coordinate or LOAD or SAVE or MENU:";
  }
  else if (player == 'O') {
    cout<<"PLAYER 2 // Enter The Coordinate or LOAD or SAVE or MENU:";
  }

	cin>>ws;
	getline(cin,command);

  //CONTROL THE MENU COMMAND THAT TAKEN FROM THE USER
	if(flag == 0){
		flag = menu_operation(command,menu);
		if(flag == 1){
      operation = 2;
      std::cout << "burda" << '\n';
    }

	}
  // CONTROL THE COORDİNATE THAT TAKEN FROM THE USER
	if(flag == 0 && ((command[2]>='0' && command[2]<='9') || command[2] == '\0')
			&& (command[1]>='0' && command[1]<='9') && (command[0]>='A' && command[0]<='Z') ){
		coordinate_operation(command,row,colu);
    flag = play_for_player(player,row,colu);
    if(flag == 1)
			operation = 1;
	}
	//CONTROL THE SAVE COMMAND THAT TAKEN FROM THE USER
	if(flag == 0){
		flag = save_operation(command,save,txt,player);
		if(flag == 1)
			operation = 0;
	}
	//CONTROL THE LOAD COMMAND THAT TAKEN FROM THE USER
	if(flag == 0){
		flag = load_operation(command,load,txt,player);
		if(flag == 1)
			operation = 0;
	}
  if (flag == 0) {
    cout<<"Command is invalid ! ! !\n";
    operation = 0;
  }


}

bool AbstractHex::menu_operation(string command,char menu[5])
{
		int counter = 0;

		for(int i=0;command[i] != ' ' && command[i] != '\0';i++)
		{
			if(menu[i] == command[i])
			{
				counter++;
			}
			else{
				return 0;
			}
		}

		return 1;
}

void AbstractHex::coordinate_operation(string command,int &row,int &colu)
{
	int first,last;
	string roww;
  char col;
  char alphabet[27] = "ABCDEFGHIJKLMNOPRSQTUVWXYZ";

	for(int i =0; command[i] != '\0' ; i++)
		last = i;
	col = command[0];
	first = 1;
	roww = command.substr(first,last);
	stringstream geek(roww);
	geek>>row;

  for (int i = 0; i < 24; i++) {
    if (alphabet[i] == col) {
      colu = i;
    }
  }
	operation = 2;
}

bool AbstractHex::load_operation(string command,char load[5],char txt[4],char player)
{
		int first,last;
		int counter = 0;
		int flag;
    string load_name;

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
			flag = 0;
			for(int i = first,j=0;command[i] !='\0';i++){
				last = i;
				if(command[i] == '.' && flag != 1){
					flag = 1;
					if(!(command[i+1] == txt[0] && command[i+2] == txt[1] && command[i+3] == txt[2] && command[i+4] == '\0')){
						flag = 0;
						break;
					}
				}
			}
			if(flag == 1){
				load_name = command.substr(first+2,last);
        readFromFile(load_name,player);
				return 1;
			}
			else{
				cerr<<"\nThis is not txt file for LOAD.";
				return 0;
			}
		}
}

bool AbstractHex::save_operation(string command,char save[5],char txt[4],char player)
{
		int first,last;
		int counter = 0;
		int flag;
    string save_name;

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
			flag = 0;
			for(int i = first,j=0;command[i] !='\0';i++){
				last = i;
				if(command[i] == '.' && flag != 1){
					flag = 1;
					if(!(command[i+1] == txt[0] && command[i+2] == txt[1] && command[i+3] == txt[2] && command[i+4] == '\0')){
						flag = 0;
						break;
					}
				}
			}
			if(flag == 1){
				cout<<"SAVE NAME"<<endl;
				save_name = command.substr(first+2,last);
        writeToFile(save_name,player);
				return 1;
			}
			else{
				cerr<<"\nThis is not txt file for SAVE.";
				return 0;
			}
		}
}
