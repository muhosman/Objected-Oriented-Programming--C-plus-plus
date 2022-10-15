/*
 * gamehex.h
 *
 *  Created on: Oct 21, 2020
 *      Author: cse312
 */

#ifndef GAMEHEX_H_
#define GAMEHEX_H_


void game();
void fill_map(char**, int);
void print_map(char**,char*, int);
int control_and_move(char**, char*, char,char, int, int);
int control_end_of_the_game(char**,char,int,int,int,int);
int computer_move(char**,int &,int &, int);


#endif /* GAMEHEX_H_ */
