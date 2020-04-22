#pragma once
#include <vector>
#include <string>
using namespace std;

enum ProductionType
{
	terminal = 1,
	nonterminal = 2,
	optional = 4,
	cycle = 8,
	sequence = 16
};


class Production
{
	int type;
	vector<vector<Production*> > alt;
	string value;
public:
	Production();
	Production(string, ProductionType);
	void addAlt(Production*);
	void addAlt(vector<Production*>);
	string getValue();
	vector<vector<Production*>> getAlts();
	void setType(ProductionType);
	void delType(ProductionType);
	void clearType();
	bool isType(ProductionType);
	~Production();
};

ostream& operator<<(ostream& out, Production a)
{
	if (a.isType(terminal) || a.isType(nonterminal))
		out << a.getValue();
	else
	{
		vector<vector<Production*>> b = a.getAlts();
		for (int i = 0; i < b.size(); ++i)
		{
			for (int j = 0; j < b[i].size(); ++j)
			{
				if (b[i][j]->isType(optional))
					out << "[" << *b[i][j] << "]";
				else if (b[i][j]->isType(sequence))
					out << "(" << *b[i][j] << ")";
				if (b[i][j]->isType(cycle))
					out << "*";
			}
			if (i != int(b.size()) - 1)
			{
				out << '|';
			}
		}
	}
	return out;
}