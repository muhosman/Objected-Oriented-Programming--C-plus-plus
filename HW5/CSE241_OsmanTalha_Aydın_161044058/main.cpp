#include <iostream>
#include "hexClass.h"

using namespace std;
using namespace hexClass;

void choice_game_board_type();
void HexVector_game();
void HexArray1D_game();


int main()
{
  choice_game_board_type();

  return 0;
}

void choice_game_board_type()
{
  int choice;
  do {
    cout<<"--BOARD TYPE--\n";
    cout<<"1-Vector\n2-Array\n3-Adaptor\n4-Exit\n";
    cout<<"Enter Choice with Number 1-2-3-4: ";
    cin>>choice;
    cout<<"\n\n";
    switch (choice) {
      case 1:
        HexVector_game();
      break;
      case 2:
        HexArray1D_game();
      break;
      case 3:
      break;
      case 4:
      break;
      default:
      cout<<"Enter Again False Select ! ! !\n\n";
      break;
    }


  } while(choice !=4);
}

void HexArray1D_game()
{
  int game_counter=0;
  int input,input1,input2;
  vector<HexArray1D> GAME;


  do {
    cout<<"MENU\n";
    cout<<"1.New Game\n";
    cout<<"2.Choice Active Game\n";
    cout<<"3.Game Compare\n";
    cout<<"4.Exit\n";
    cout<<"\nYour choice (EXMP:1-2-3):";
    if (!(cin >> input)) {
      cin.clear();
      cin.ignore(10000,'\n');
    }
    switch (input) {
      case 1:

        game_counter++;
        GAME.resize(game_counter);
        GAME[game_counter-1].set_first_cmp_move(0);
        GAME[game_counter-1].set_active(0);
        GAME[game_counter-1].Game();
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
            GAME[input1].Game();
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
            if(GAME[input1] == GAME[input2])
              cout<<"Result: Game["<<input1<<"]=Game["<<input2<<"]"<<endl;
            else
              cout<<"They are not equal !\n";
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
}
void HexVector_game()
{
  int game_counter=0;
  int input,input1,input2;
  vector<HexVector> GAME;


  do {
    cout<<"MENU\n";
    cout<<"1.New Game\n";
    cout<<"2.Choice Active Game\n";
    cout<<"3.Game Compare\n";
    cout<<"4.Exit\n";
    cout<<"\nYour choice (EXMP:1-2-3):";
    if (!(cin >> input)) {
      cin.clear();
      cin.ignore(10000,'\n');
    }
    switch (input) {
      case 1:

        game_counter++;
        GAME.resize(game_counter);
        GAME[game_counter-1].set_first_cmp_move(0);
        GAME[game_counter-1].set_active(0);
        GAME[game_counter-1].Game();
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
            GAME[input1].set_active(1);
            GAME[input1].Game();
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
            if(GAME[input1] == GAME[input2])
              cout<<"Result: Game["<<input1<<"]=Game["<<input2<<"]"<<endl;
            else
              cout<<"They are not equal !\n";
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
}
