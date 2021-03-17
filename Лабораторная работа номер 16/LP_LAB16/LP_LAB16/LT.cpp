#include "LT.h"
#include "IT.h"
#include "Error.h"
#include <fstream>
namespace LT
{
	LT::LexTable::LexTable()
	{
		this->maxsize = LT_MAXSIZE;
		this->size = 0;
		this->table = new Entry[LT_MAXSIZE];
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size < lextable.maxsize)
			lextable.table[lextable.size++] = entry;
		else
			throw ERROR_THROW(120);
	}
	Entry LexTable::GetEntry(int n)
	{
		if (n < this->maxsize && n >= 0)
			return this->table[n];
	}
	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
		lextable.table = nullptr;
	}
	void LexTable::PrintLexTable(const wchar_t* in)
	{
		int i = 0;
		wchar_t lex[500];
		for (; in[i] != '\0'; i++)
			lex[i] = in[i];
		lex[i] = '\0';
		wcscat_s(lex, PARM_LEX);

		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(lex);

		if (lex_stream->is_open())
		{
			int num_string = 0;
			for (int i = 0; i < this->size;)
			{
				if (num_string == this->table[i].sn)
					(*lex_stream) << this->table[i++].lexema;
				else
				{
					num_string++;
					if (this->table[i].sn != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << '\t';

					if (num_string == this->table[i].sn)
						(*lex_stream) << this->table[i++].lexema;
				}
			}
		}
		else
			throw ERROR_THROW(128);
		lex_stream->close();
		delete lex_stream;

	}
	void LexTable::PrintLexTable(const wchar_t* in, const wchar_t* name)
	{
		int i = 0;
		wchar_t lex[500];
		for (; in[i] != '\0'; i++)
			lex[i] = in[i];
		lex[i] = '\0';
		wcscat_s(lex, name);

		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(lex);

		if (lex_stream->is_open())
		{
			int num_string = 0;
			for (int i = 0; i < this->size;)
			{
				if (num_string == this->table[i].sn)
					(*lex_stream) << this->table[i++].lexema;
				else
				{
					num_string++;
					if (this->table[i].sn != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << '\t';

					if (num_string == this->table[i].sn)
						(*lex_stream) << this->table[i++].lexema;
				}
			}
		}
		else
			throw ERROR_THROW(128);
		lex_stream->close();
		delete lex_stream;

	}

	void LexTable::PrintLexTableControle(const wchar_t* in, const wchar_t* name, IT::IdTable it)
	{
		int i = 0;
		wchar_t lex[500];
		for (; in[i] != '\0'; i++)
			lex[i] = in[i];
		lex[i] = '\0';
		wcscat_s(lex, name);

		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(lex);

		if (lex_stream->is_open())
		{
			int num_string = 0;
			for (int i = 0; i < this->size;)
			{
				if (num_string == this->table[i].sn)
				{
					if(this->table[i].lexema == 'v')
						(*lex_stream) << it.table[this->table[i++].idxTI].value.operation;
					else
					(*lex_stream) << this->table[i++].lexema;
				}
				else
				{
					num_string++;
					if (this->table[i].sn != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << '\t';

					if (num_string == this->table[i].sn)
					{
						if (this->table[i].lexema == 'v')
							(*lex_stream) << it.table[this->table[i++].idxTI].value.operation;
						else
							(*lex_stream) << this->table[i++].lexema;
					}
				}
			}
		}
		else
			throw ERROR_THROW(128);
		lex_stream->close();
		delete lex_stream;

	}
	LT::Entry::Entry()
	{
		this->lexema = '\0';
		this->sn = LT_TI_NULLXDX;
		this->idxTI = LT_TI_NULLXDX;
	}

	LT::Entry::Entry(const char lex, int str_n, int idxTI)
	{
		this->lexema = lex;
		this->sn = str_n;
		this->idxTI = idxTI;
	}
}