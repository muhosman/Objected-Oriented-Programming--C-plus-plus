//////////////////////////////////////////////////////////////////////////
////////////// H E X  C E L L //////////////////////////

#include "hexClass.h"
using namespace hexClass;

void CELL::set_column(int input)
{
  column = input;
}
int CELL::get_column()const
{
  return column;
}

int CELL::get_row()const
{
  return row;
}
void CELL::set_row(int input)
{
  row = input;
}

void CELL::set_type(char input)
{
  type = input;
}
char CELL::get_type()const
{
  return type;
}
