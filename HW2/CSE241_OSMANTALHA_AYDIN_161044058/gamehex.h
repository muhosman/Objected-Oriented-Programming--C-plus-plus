/*
 * gamehex.h
 *
 *  Created on: Oct 21, 2020
 *      Author: cse312
 */

#ifndef GAMEHEX_H_
#define GAMEHEX_H_

enum player{player1='X',player2='O',dot='.',comma=','};

void game();
void fill_map(char**,int size=12);
void print_map(char**,const char*,const int &);
int control_and_move(char**,const char*,const enum player,const char &,const int &,const int &);
int control_end_of_the_game(char**,const enum player,const int &,const int &,const int &,const int &);
int computer_move(char**,int &,int &,const int &);
int operation_control(char &,int &,std::string &,std::string &);
int file_operation(int &,std::string &,int &,enum player,int &,char **,int &,int &);


#endif /* GAMEHEX_H_ */
