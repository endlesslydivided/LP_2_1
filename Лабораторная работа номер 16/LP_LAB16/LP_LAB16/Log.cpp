#include "stdafx.h"	
#include "Log.h"	
#include <time.h>

#pragma warning(disable : 4996)
using namespace std;

namespace Log
{
	LOG getlog(wchar_t logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile);
		if (log.stream->fail())
			throw ERROR_THROW(112);
		wcscpy_s(log.logfile, logfile);
		return log;
	}
	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr = &c;
		int i = 0;
		while (ptr[i] != "")
			*log.stream << ptr[i++];
		*log.stream << endl;
	}
	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr = &c;
		char temp[100];
		int i = 0;
		while (ptr[i] != L"")
		{
			wcstombs(temp, ptr[i++], sizeof(temp));
			*log.stream << temp;
		}
		*log.stream << ptr[i++];
		*log.stream << endl;
	}
	void WriteLog(LOG log)
	{
		tm* timeinf;
		time_t timet;
		time(&timet);
		timeinf = localtime(&timet);
		char temp[100];
		strftime(temp, sizeof(temp), "\n----------- ÏÐÎÒÎÊÎË -----------\n ----------- %d.%m.%y %T -----------\n ", timeinf);
		*log.stream << temp;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "\n----------- ÈÑÕÎÄÍÛÅ ÄÀÍÍÛÅ -----------\n";
		int line = 1;
		*log.stream << line++ << '\t';
		for (int iter = 0; iter < in.size; iter++)
		{
			*log.stream << in.text[iter];
			if (in.text[iter] == '\n')
			{
				*log.stream << line++ << '\t';
			}
		}
		*log.stream << "\n\nÂñåãî ñèìâîëîâ: " << in.size;
		*log.stream << "\nÂñåãî ñòðîê: " << in.lines;
		*log.stream << "\nÏðîïóùåíî: " << in.ignor << endl;
	}
	void WriteParm(LOG log, Parm::PARM parm)
	{
		char in_text[PARM_MAX_SIZE];
		char out_text[PARM_MAX_SIZE];
		char log_text[PARM_MAX_SIZE];
		wcstombs(in_text, parm.in, PARM_MAX_SIZE);
		wcstombs(out_text, parm.out, PARM_MAX_SIZE);
		wcstombs(log_text, parm.log, PARM_MAX_SIZE);
		*log.stream << "\n ----------- ÏÀÐÀÌÅÒÐÛ ----------- \n\n-in: " << in_text
			<< "\n-out: " << out_text
			<< "\n-log: " << log_text << endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream)
		{
			*log.stream << "\nÎøèáêà " << error.id
				<< ": " << error.message
				<< "\nÑòðîêà " << error.inext.line
				<< " ïîçèöèÿ " << error.inext.col << endl;
			Close(log);
		}
		cout << "\nÎøèáêà " << error.id
			<< ": " << error.message
			<< "\nÑòðîêà " << error.inext.line
			<< " ïîçèöèÿ " << error.inext.col << endl;
	}
	void Close(LOG log)
	{
		log.stream->close();
	}

}
