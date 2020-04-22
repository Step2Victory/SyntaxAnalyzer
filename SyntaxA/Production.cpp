#include "Production.h"

Production::Production()
{
	type = 0;
	value = "";
}

Production::Production(string _value, ProductionType _type)
{
	value = _value;
	type = _type;
}

void Production::addAlt(Production *altP)
{
	vector<Production*> v;
	v.push_back(altP);
	if (int(alt.size()) == 0)
	{
		Production *p = new Production(value, ProductionType(type));
		vector<Production*> pr;
		pr.push_back(p);
		alt.push_back(pr);
		delType(terminal);
		delType(nonterminal);
		setType(sequence);
	}
	alt.push_back(v);
}

void Production::addAlt(vector<Production*> v)
{
	if (int(alt.size() == 0))
	{
		Production *p = new Production(value, ProductionType(type));
		vector<Production*> pr;
		pr.push_back(p);
		alt.push_back(pr);
		delType(terminal);
		delType(nonterminal);
		setType(sequence);
	}
	alt.push_back(v);
}

string Production::getValue()
{
	if (int(alt.size()) == 0)
		return value;
	throw "This is a sequence of symbols";
}

vector<vector<Production*>> Production::getAlts()
{
	return alt;
}

void Production::setType(ProductionType _type)
{
	if (!isType(_type))
		type += _type;
}

void Production::delType(ProductionType _type)
{
	if (isType(_type))
		type -= _type;
}

void Production::clearType()
{
	type = 0;
}



bool Production::isType(ProductionType _type)
{
	if (type / _type % 2)
		return true;
	return false;
}


Production::~Production()
{
	for (int i = 0; i < alt.size(); ++i)
	{
		for (int j = 0; j < alt[i].size(); ++j)
			delete alt[i][j];
	}
}
