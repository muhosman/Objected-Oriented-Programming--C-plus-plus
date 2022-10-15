//////////////////////////////////////////////////////////////////////////
////////////// H E X  V E C T O R //////////////////////////

#include "hexClass.h"
using namespace hexClass;


HexArray1D::HexArray1D(const HexArray1D &Object)
{
  size = getSize();

  free(hexCell);
  hexCell = (CELL*) malloc((getSize()*getSize())*sizeof(CELL));

  for (int i = 0; i < getSize(); i++) {
    for (int j = 0; j < getSize(); j++) {
      hexCell[(i*getSize())+j].set_type(Object(i,j));
      hexCell[(i*getSize())+j].set_row(Object.hexCell[(i*getSize())+j].get_row());
      hexCell[(i*getSize())+j].set_column(Object.hexCell[(i*getSize())+j].get_column());
    }
  }

}
HexArray1D::~HexArray1D()
{
  free(hexCell);
}



void HexArray1D::first_computer_move()
{
  if((*this)(0,0) == '.'){
    hexCell[0].set_type('O');
    cmp_row=0;
    cmp_col=0;
  }
  else if ((*this)(0,1) == '.') {
    hexCell[1].set_type('O');
    cmp_row=0;
    cmp_col=1;
  }
}

bool HexArray1D::play_for_computer()
{
	if(get_cmp_row() < getSize()){
		if((*this)(cmp_row+1,cmp_col) == '.'){
			hexCell[((cmp_row+1)*getSize())+cmp_col].set_type('O');
			cmp_row++;
			return 1;
		}
	}
  if(get_cmp_row()<getSize() && get_cmp_col()>0){
    if((*this)(cmp_row+1,cmp_col-1) == '.'){
      hexCell[((cmp_row+1)*getSize())+cmp_col-1].set_type('O');
      cmp_row++;
      cmp_col--;
      return 1;
    }
  }
  if(get_cmp_col() > 0){
    if((*this)(cmp_row,cmp_col-1) == '.'){
      hexCell[(cmp_row*getSize())+cmp_col-1].set_type('O');
      cmp_col--;
      return 1;
    }
  }
  if(get_cmp_col() < getSize()){
    if((*this)(cmp_row,cmp_col+1) == '.'){
      hexCell[(cmp_row*getSize())+cmp_col+1].set_type('O');
      cmp_col++;
      return 1;
    }
  }

  if(get_cmp_row()>0 && get_cmp_col()<getSize()){
		if((*this)(cmp_row-1,cmp_col+1) == '.'){
			hexCell[((cmp_row-1)*getSize())+cmp_col+1].set_type('O');
			cmp_col++;
			cmp_row--;
			return 1;
		}
	}
	if(get_cmp_row() > 0){
		if((*this)(cmp_row-1,cmp_col) == '.'){
			hexCell[((cmp_row-1)*getSize())+cmp_col].set_type('O');
			cmp_row--;
			return 1;
		}
	}
	return 0;
}

int HexArray1D::control_endgame_x()
{
  int op;
  for(int i = 0;i<getSize();i++){
    if('X' == (*this)(i,0)){
      hexCell[(i*getSize())+0].set_type(',');
      op = isEnd('X',0,i,0);
      hexCell[(i*getSize())+0].set_type('X');
      if(op == 1){
        cout<<"\nThis game is finished ! \n";
        break;
      }
    }
  }
  return op;
}

int HexArray1D::control_endgame_y()
{
  int op;
  for(int i = 0;i<getSize();i++){
    if('O' == (*this)(0,i)){
      hexCell[(0*getSize())+i].set_type(',');
      op = isEnd('O',0,0,i);
      hexCell[(0*getSize())+i].set_type('O');
      if(op == 1){
        cout<<"\nThis game is finished ! \n";
        break;
      }
    }
  }
  return op;
}
bool HexArray1D::isEnd(char type,int control,int roww,int column)
{
	int flag1 = 0;
		if(roww > 0)
			if(control != 1 && (*this)(roww-1,column) == type && flag1 == 0)
				{
					hexCell[((roww-1)*getSize())+column].set_type(',');
					if(type == 'X' && column == getSize()-1){
						hexCell[((roww-1)*getSize())+column].set_type('X');
						return 1;
					}
					if(type == 'O' && roww-1 == getSize()-1){
						hexCell[((roww-1)*getSize())+column].set_type('O');
						return 1;
					}
					flag1 = isEnd(type,4,roww-1,column);

						if (type == 'X') {
							hexCell[((roww-1)*getSize())+column].set_type('X');
						}
						if (type == 'O') {
							hexCell[((roww-1)*getSize())+column].set_type('O');
						}
				}

		if(column > 0)
			if(control != 6 && (*this)(roww,column-1) == type && flag1 == 0)
				{
					hexCell[(roww*getSize())+column-1].set_type(',');
					if(type == 'X' && column-1 == getSize()-1){
						hexCell[(roww*getSize())+column-1].set_type('X');
						return 1;
					}
					if(type == 'O' && roww == getSize()-1){
						hexCell[(roww*getSize())+column-1].set_type('O');
						return 1;
					}

					flag1 = isEnd(type,3,roww,column-1);

						if (type == 'X') {
							hexCell[(roww*getSize())+column-1].set_type('X');
						}
						if (type == 'O') {
							hexCell[(roww*getSize())+column-1].set_type('O');
						}
				}

		if(roww < getSize()-1)
			if(control != 4 && (*this)(roww+1,column) == type && flag1 == 0)
				{
					hexCell[((roww+1)*getSize())+column].set_type(',');
					if(type == 'X' && column == getSize()-1){
						hexCell[((roww+1)*getSize())+column].set_type('X');
						return 1;
					}
					if(type == 'O' && roww+1 == getSize()-1){
						hexCell[((roww+1)*getSize())+column].set_type('O');
						return 1;
					}

					flag1 = isEnd(type,1,roww+1,column);

						if (type == 'X') {
							hexCell[((roww+1)*getSize())+column].set_type('X');
						}
						if (type == 'O') {
							hexCell[((roww+1)*getSize())+column].set_type('O');
						}
				}
		if(column < getSize()-1)
			if(control != 6 && (*this)(roww,column+1) == type && flag1 == 0)
				{
					hexCell[(roww*getSize())+column+1].set_type(',');
					if(type == 'X' && column+1 == getSize()-1){
						hexCell[(roww*getSize())+column+1].set_type('X');
						return 1;
					}
					if(type == 'O' && roww == getSize()-1){
						hexCell[(roww*getSize())+column+1].set_type('O');
						return 1;
					}

					flag1 = isEnd(type,3,roww,column+1);

						if (type == 'X') {
							hexCell[(roww*getSize())+column+1].set_type('X');
						}
						if (type == 'O') {
							hexCell[(roww*getSize())+column+1].set_type('O');
						}
				}
		if(roww>0 && column<getSize()-1)
			if(control != 2 && (*this)(roww-1,column+1) == type && flag1 == 0)
				{
					hexCell[((roww-1)*getSize())+column+1].set_type(',');
					if(type == 'X' && column+1 == getSize()-1){
						hexCell[((roww-1)*getSize())+column+1].set_type('X');
						return 1;
					}
					if(type == 'O' && roww-1 == getSize()-1){
						hexCell[((roww-1)*getSize())+column+1].set_type('O');
						return 1;
					}

					flag1 = isEnd(type,5,roww-1,column+1);

						if (type == 'X') {
							hexCell[((roww-1)*getSize())+column+1].set_type('X');
						}
						if (type == 'O') {
							hexCell[((roww-1)*getSize())+column+1].set_type('O');
						}
				}

		if(roww<getSize()-1 && column>0)
			if(control != 5 && (*this)(roww+1,column-1) == type && flag1 == 0)
				{
					hexCell[((roww+1)*getSize())+column-1].set_type(',');
					if(type == 'X' && column-1 == getSize()-1){
						hexCell[((roww+1)*getSize())+column-1].set_type('X');
						return 1;
					}
					if(type == 'O' && roww+1 == getSize()-1){
						hexCell[((roww+1)*getSize())+column-1].set_type('O');
						return 1;
					}

					flag1 = isEnd(type,2,roww+1,column-1);

						if (type == 'X') {
							hexCell[((roww+1)*getSize())+column-1].set_type('X');
						}
						if (type == 'O') {
							hexCell[((roww+1)*getSize())+column-1].set_type('O');
						}
				}


	return flag1;
}

void HexArray1D::readFromFile(string load_name,char player_turn)
{
string line;
string num;
int counter;
int temp=0;
int first,last;
int player;

if(player_turn == 'X')
  player =1;
else if(player_turn == 'O')
  player =2;

  //L O A D  FILE
  ifstream loadfile(load_name);
  if (loadfile.is_open())
  {
    counter = 0;
    while ( getline (loadfile,line) )
  	{
  		counter++;
  		if( (counter<4 && Gamestyle == 1)  || (Gamestyle == 2 && counter < 6))
  		    for(int i =0; line[i] != '\0' ; i++){
  		        if(line[i]==':'){
  							first = i+1;
  						}
  						last = i;
  				}
  				num = line.substr(first,last);
  				stringstream geek(num);
  				if(counter == 1)
  					geek>>Gamestyle;
  				if(counter == 2){
  					geek>>player;
  				}
  				if(counter == 3 && Gamestyle == 2){
  					geek>>cmp_row;
  				}
  				if(counter == 4 && Gamestyle == 2){
  					geek>>cmp_col;
  				}
          if( (counter == 3 && Gamestyle == 1) || (counter == 5 && Gamestyle == 2) ){
            delete[] hexCell;
            geek>>size;
            hexCell = (CELL*) malloc((getSize()*getSize())*sizeof(CELL));
  		    }
  		    else if( (counter > 4 && Gamestyle == 1) || (Gamestyle == 2 && counter > 6) ){
  		    	for(int i=0;line[i] != '\0' ; ++i)
  		    	{
              hexCell[(temp*getSize())+i].set_type(line[i]);
              hexCell[(temp*getSize())+i].set_row(temp);
              hexCell[(temp*getSize())+i].set_column(i);

  		    	}
  		    	temp++;
  		   	}

       }

       loadfile.close();
  	}
  	else {
  		cout << "Unable to open file\n";
  		throw FileError();
  	}
    if (!(control(*this))) {
      throw BoardError();
    }
    else
    {
      cout<<"Size : "<<getSize()<<endl;
      cout<<"Gamestyle : "<<getGamestyle()<<endl;
      print();
    }

}

void HexArray1D::writeToFile(string save_name,char player_turn)
{
  string line;
  string num;
  int counter;
  int temp=0;
  int first,last;
  int player;

  if(player_turn == 'X')
    player =1;
  else if(player_turn == 'O')
    player =2;

  ofstream savefile(save_name);

  if (savefile.is_open())
  {
    savefile << "Game_Style:"<<Gamestyle<<endl;
    savefile << "Player_Turn:"<<player<<endl;
    if(Gamestyle == 2)
    {
      savefile << "CMP_ROW:"<<cmp_row<<endl;
      savefile << "CMP_COL:"<<cmp_col<<endl;
    }
    savefile << "Size:"<<getSize()<<endl;
    savefile << "Board:\n";
    for(int i = 0; i<size ; ++i)
    {
      for(int j = 0; j<size ; ++j)
      {
        savefile<<(*this)(i,j);
      }
      savefile<<endl;
    }

    savefile.close();
  }
  else{
    cerr << "Unable to open file";
    throw FileError();
  }
}

bool HexArray1D::play_for_player(char player,int &row,int &colu)
{
  char alphabet[27] = "ABCDEFGHIJKLMNOPRSQTUVWXYZ";

  if(colu >=0 && colu < getSize() && row >=0 && row < getSize() && (*this)(row,colu) == '.'){
    hexCell[(row*getSize())+colu].set_type(player);
    return 1;
  }
	return 0;
}

void HexArray1D::print()
{
  char alphabet[27] = "ABCDEFGHIJKLMNOPRSQTUVWXYZ";

  cout<<"\n";
  for (int i = 0; i < getSize(); i++)
	{
		cout << " " << alphabet[i];
	}
	cout << endl;
	for (int i = 0; i < getSize(); i++)
	{
		cout << i;
		for (int k = 0; k < i; k++)
		{
			cout << " ";
		}
		for (int j = 0; j < getSize(); j++)
		{
			cout << (*this)(i,j) <<" ";
		}
		cout << endl;
	}
}

void HexArray1D::setsize()
{
  do{
    cout<<"Enter The Size(6-24) : ";
    cin>>size;
  }while(!(getSize()<=24 && getSize()>=6));
  hexCell = (CELL*) malloc((getSize()*getSize())*sizeof(CELL));
}

void HexArray1D::fill_cell()
{
  for (int i = 0; i < getSize(); i++) {
    for (int j = 0; j < getSize(); j++) {
      hexCell[(i*getSize())+j].set_type('.');
      hexCell[(i*getSize())+j].set_row(i);
      hexCell[(i*getSize())+j].set_column(j);
    }
  }
}

void HexArray1D::setGamestyle()
{
  do {
    cout<<"Enter Gamestyle (1-Player vs Player | 2-Computer vs Player) : ";
    cin>>Gamestyle;
  } while(!(getGamestyle()<=2 && getGamestyle()>=1));
}

void HexArray1D::numberOfMoves()
{
  Moves = 0;
  for (int i = 0; i < getSize(); i++) {
    for (int j = 0; j < getSize(); j++) {
      if ((*this)(i,j) != '.' ) {
        Moves++;
      }
    }
  }
}

void HexArray1D::reset()
{
  for (int i = 0; i < getSize(); i++) {
    for (int j = 0; j < getSize(); j++) {
      hexCell[(i*getSize())+j].set_type('.');
    }
  }
  Gamestyle = 0;
  size = 0;
  Moves = 0;
}
