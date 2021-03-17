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

		lexTable.PrintLexTable(parm.in, L".lex_ver_0.txt");
		MFST_TRACE_START										//отладка
		MFST::Mfst mfst(lexTable, GRB::getGreibach());			//автомат
		mfst.start();											// старт синтаксического анализа

		mfst.savededucation();									//сохранить правила вывода

		mfst.printrules();										//отладка: вывести правила вывода	


		for (int iter = 0, lt_position; iter < lexTable.size; iter++)
		{
			if (lexTable.table[iter - 1].lexema == LEX_EQUAL_SIGN)
			{
				if (PN::PolishNotation(iter, lexTable, idTable))
				{
					std::cout << iter << ": польская запись построена;строка: " << lexTable.table[iter].sn << std::endl;
				}
				else
					std::cout << iter << ": польская запись не построена;строка: " << lexTable.table[iter].sn << std::endl;
			}
		}

		lexTable.PrintLexTable(parm.in, L".lex_ver_PN.txt");
		lexTable.PrintLexTableControle(parm.in, L".lex_ver_Control.txt", idTable);
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