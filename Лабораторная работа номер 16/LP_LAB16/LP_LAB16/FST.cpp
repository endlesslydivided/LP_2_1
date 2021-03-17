#include <iostream>
#include "FST.h"

FST::RELATION::RELATION(char c, short ns)
{
	this->symbol = c;
	this->nnode = ns;
}

FST::NODE::NODE()
{
	this->n_relation = 0;
	this->relations = NULL;
}

FST::NODE::NODE(short n, RELATION rel, ...)
{
	this->n_relation = n;
	this->relations = new RELATION[n];

	RELATION* ptr = &rel;
	for (short i = 0; i < n; i++)
		this->relations[i] = *ptr++;
}

FST::FST::FST(const char* s, short ns, NODE n, ...)
{
	this->string = s;
	this->nstates = ns;
	this->nodes = new NODE[ns];

	NODE* p = &n;
	for (int k = 0; k < ns; k++)
		this->nodes[k] = *p++;

	this->rstates = new short[ns];
	memset(rstates, -1, sizeof(short) * this->nstates);
	this->rstates[0] = 0;
	this->position = -1;
}

bool FST::step(FST& fst, short* rstates)
{
	std::swap(rstates, fst.rstates);
	bool real = false;
	for (short i = 0; i < fst.nstates; i++)
	{
		if (rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; j++)
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					real = true;
				}
	}
	return real;
}

bool FST::execute(FST& fst)
{
	short* rstates = new short[fst.nstates];
	memset(rstates, -1, sizeof(short) * fst.nstates);
	short lstring = strlen(fst.string);
	bool rc = true;
	for (short i = 0; (i < lstring) && rc; i++)
	{
		fst.position++;
		rc = step(fst, rstates);
	}
	rc = (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	delete[] rstates;
	return rc;
}