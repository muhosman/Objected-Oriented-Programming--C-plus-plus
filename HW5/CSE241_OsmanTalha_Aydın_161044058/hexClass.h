#ifndef Hex_Class
#define Hex_Class

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <list>
#include <queue>
#include <deque>

using namespace std;

namespace hexClass{

  class FileError
  {};
  class BoardError
  {};

  class AbstractHex
  {
  public:

    AbstractHex();

    friend bool control(class AbstractHex &Game){
      if(Game.getSize() < 6 || Game.getSize()>24)
      {
        return 0;
      }
      if(Game.getGamestyle() !=1 && Game.getGamestyle() != 2)
      {
        return 0;
      }
      for (int i = 0; i < Game.getSize(); i++) {
        for (int j = 0; j < Game.getSize(); j++) {
          if (Game(i,j) != '.' && Game(i,j) != 'X' && Game(i,j) != 'O') {
            return 0;
          }
        }
      }
      return 1;
    }

    virtual void print() = 0;

    virtual void setsize() = 0;
    virtual int getSize()const = 0;

    virtual void fill_cell() = 0;

    virtual void setGamestyle() = 0;
    virtual int getGamestyle()const = 0;

    virtual void numberOfMoves() = 0;
    virtual int get_numberOfMoves()const = 0;

    virtual bool play_for_player(char player,int &row,int &colu) = 0;
    virtual bool play_for_computer() = 0;
    virtual void first_computer_move() = 0;

    virtual void readFromFile(string load_name,char player_turn) = 0;
    virtual void writeToFile(string save_name,char player_turn) = 0;

    virtual bool isEnd(char type,int control,int roww,int column) = 0;

    virtual int control_endgame_x() = 0;
    virtual int control_endgame_y() = 0;
    virtual char operator() (int i,int j)const = 0;

    bool operator==(AbstractHex &Game);

    void player_move(char player);
    void take_operation(char player);

    void set_operation(int input)
    {operation = input;}
    int get_operation()const
    {return operation;}

    bool menu_operation(string command,char menu[5]);
    void coordinate_operation(string command,int &row,int &colu);
    bool load_operation(string command,char load[5],char txt[4],char player);
    bool save_operation(string command,char save[5],char txt[4],char player);

    void set_active(int input)
    {active = input;}
    int get_active()
    {return active;}

    void set_first_cmp_move(int input)
    {first_cmp_move = input;}
    int get_first_cmp_move()const
    {return first_cmp_move;}

    void Game();

    virtual void reset() = 0;

  private:
    int operation;
    int active;
    int first_cmp_move;

  };

  class CELL{
  public:

    void set_column(int input);
    int get_column()const;

    void set_row(int input);
    int get_row()const;

    void set_type(char input);
    char get_type()const;


  private:
    int column;
    int row;
    char type;

  };

  class HexVector:public AbstractHex{
  public:
    HexVector(){ }

    void print();
    void setsize();
    int getSize()const
    {return size;}

    void fill_cell();

    void setGamestyle();
    int getGamestyle()const
    {return Gamestyle;}

    void numberOfMoves();
    int get_numberOfMoves()const
    {return Moves;}

    bool play_for_player(char player,int &row,int &colu);
    bool play_for_computer();
    void first_computer_move();

    void reset();

    void readFromFile(string load_name,char player_turn);
    void writeToFile(string save_name,char player_turn);

    bool isEnd(char type,int control,int roww,int column);

    int control_endgame_x();

    int control_endgame_y();


    char operator() (int i,int j)const
    {return hexCell[i][j].get_type();}

    int get_cmp_row()const
    {return cmp_row;}
    int get_cmp_col()const
    {return cmp_col;}

    vector<vector<CELL>> hexCell;

  private:
    int size;
    int Gamestyle;
    int Moves;
    int cmp_row;
    int cmp_col;
  };

  class HexArray1D:public AbstractHex{
  public:
    HexArray1D(){ }

    HexArray1D(const HexArray1D &Object);
    ~HexArray1D();

    void print();
    void setsize();
    int getSize()const
    {return size;}

    void fill_cell();

    void setGamestyle();
    int getGamestyle()const
    {return Gamestyle;}

    void numberOfMoves();
    int get_numberOfMoves()const
    {return Moves;}

    bool play_for_player(char player,int &row,int &colu);
    bool play_for_computer();
    void first_computer_move();

    void reset();

    void readFromFile(string load_name,char player_turn);
    void writeToFile(string save_name,char player_turn);

    bool isEnd(char type,int control,int roww,int column);

    int control_endgame_x();

    int control_endgame_y();


    char operator() (int i,int j)const
    {return hexCell[(getSize()*i)+j].get_type();}

    int get_cmp_row()const
    {return cmp_row;}
    int get_cmp_col()const
    {return cmp_col;}

    CELL *hexCell;

  private:
    int size;
    int Gamestyle;
    int Moves;
    int cmp_row;
    int cmp_col;
  };


}

#endif
