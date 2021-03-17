#pragma once

#include <iostream>
#include <fstream>
#include "LT.h"
#include "IT.h"
#include "In.h"

#define SPACE ' '
#define VERTICAL_BAR '|'
#define LINE_FEED '\n'
#define POST_PRE_SPACE_SYMBOLS ";,}{()=+-/*"

#define token_size 256

struct flag_type_variable
{
	int LT_posititon = -1;
	enum { DEF = 0, INT = 1, STR = 2 }type = DEF;
};

bool func_var(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, flag_type_variable& flag_type_variable);
void token_divivison(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable);
bool token_analize(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable);
