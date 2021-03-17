#include "stdafx.h"

int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "ru");
	Log::LOG	log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест: ", "без ошибок ", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);

		LT::LexTable lexTable;
		IT::IdTable	idTable;

		token_divivison(in, lexTable, idTable);

		lexTable.PrintLexTable(parm.in, L".lex_1.txt");

		for (int iter = 0, lt_position; iter < lexTable.size; iter++)
		{
 			if ((lexTable.table[iter - 1].lexema == LEX_EQUAL_SIGN && lexTable.table[iter].lexema == LEX_ID && lexTable.table[iter + 1].lexema == 'v') || 
				((lexTable.table[iter - 1].lexema == LEX_EQUAL_SIGN && lexTable.table[iter].lexema == LEX_ID && lexTable.table[iter + (idTable.GetEntry(lexTable.table[iter].idxTI).parmQuantity)*2 + 2].lexema == 'v'))||
				lexTable.table[iter].lexema == LEX_LEFTHESIS)
			{
				if (PN::PolishNotation(iter, lexTable, idTable))
				{
					std::cout << iter << ": польская запись построена;строка: " << lexTable.table[iter].sn << std::endl;
					int str = lexTable.table[iter].sn;
					std::cout <<"Результат: ";
					for (iter; str == lexTable.table[iter].sn; iter++)
					{
						std::cout << " ";
						In::IN in_ex;
						if (in_ex.code[lexTable.table[iter].lexema] != in_ex.D)
						{
							if (lexTable.table[iter].operation != '\0')
								std::cout << lexTable.table[iter].operation;
							else if (strcmp(idTable.GetEntry(lexTable.table[iter].idxTI).id, "\0") != 0 && idTable.GetEntry(lexTable.table[iter].idxTI).value.vint != 0)
								std::cout << idTable.GetEntry(lexTable.table[iter].idxTI).value.vint;
							else
								std::cout << idTable.GetEntry(lexTable.table[iter].idxTI).id;	
						}
					}
					std::cout << std::endl;
				}
				else
					std::cout << iter << ": польская запись не построена;строка: " << lexTable.table[iter].sn << std::endl;
			}
		}

		lexTable.PrintLexTable(parm.in);
		idTable.PrintIdTable(parm.in);

		Delete(lexTable);
		Delete(idTable);

		Log::Close(log);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;

}