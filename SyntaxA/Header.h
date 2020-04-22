#pragma once
#include <string>
#include <vector>
#include <stack>
#include "map"
using namespace std;


enum productionType
{
	cycle = 2,
	additional = 4,
	nonterm = 8,
	term = 16
};

class Production
{
	int type;
	string regular_expr;
	vector<vector<Production> > alternatives;
	friend ostream& operator<<(ostream& out, Production a);
public:
	Production();
	Production(string);
	void setType(productionType);
	bool isType(productionType);
	map<string, Production> makeGrammar(string grammar);
	pair<Production,int> makeProductionUntil(string s, char end);
	void clear();
	~Production();
};

ostream& operator<<(ostream& out, Production a)
{
	if (a.regular_expr != "")
	{
		out << a.regular_expr;
		return out;
	}
	for (int i = 0; i < a.alternatives.size();++i)
	{
		for (int j = 0; j < a.alternatives[i].size(); ++j)
		{
			out << a.alternatives[i][j] << " ";
		}
		if (i != int(a.alternatives.size()) - 1)
			out << " | ";
	}
	return out;
}




class Parser
{
	vector<string> tokens;
	map<string, Production> grammar;

};