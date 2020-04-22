#include "Header.h"

Production::Production()
{
}

Production::Production(string)
{
}

void Production::
setType(productionType type)
{
}


map<string, Production> Production::makeGrammar(string grammar)
{
	string wrd = "", last_key = "";
	int cur = 0;
	map<string, Production> ans;
	Production prod;
	vector<Production> seq;
	while (cur < grammar.size())
	{
		
		if (grammar[cur] ==  '(')
		{
			string c = grammar;
			pair<Production, int> res = makeProductionUntil(c.erase(0, cur), ')');
			cur += res.second;
			if (cur + 1 < grammar.size() && grammar[cur + 1] == '*')
			{
				res.first.setType(cycle);
				cur++;
			}
			seq.push_back(res.first);
		}
		else if (grammar[cur] == '[')
		{
			string c = grammar;
			pair<Production, int> res = makeProductionUntil(c.erase(0, cur), ']');
			cur += res.second;
			if (cur + 1 < grammar.size() && grammar[cur + 1] == '*')
			{
				res.first.setType(cycle);
				cur++;
			}
			res.first.setType(additional);
			seq.push_back(res.first);
		}
		else if (grammar[cur] == '|')
		{
			prod.alternatives.push_back(seq);
			seq = {};
		}
		else if (grammar[cur] == ' ' || grammar[cur] == '\n' || grammar[cur] == '\t' || grammar[cur] == '\r')
		{
			if (wrd != "")
			{
				Production a(wrd);
				a.setType(nonterm);

				seq.push_back(wrd);
				wrd = "";
			}
		}
		else if (grammar[cur] == '\'')
		{
			string tokenStr = "";
			while (grammar[cur] != '\'')
			{
				tokenStr += grammar[cur];
				cur++;
			}
			Production a(tokenStr);
			a.setType(term);
		}
		else if (grammar[cur] == ':')
		{
			if (last_key != "")
			{
				prod.alternatives.push_back(seq);
				ans[last_key] = prod;
				prod.clear();
			}
			ans[wrd];
			last_key = wrd;
			wrd = "";
		}
		else
		{
			wrd += grammar[cur];
		}
		cur++;
	}
	return ans;
}

pair<Production, int> Production::makeProductionUntil(string grammar, char end)
{
	string wrd = "";
	int cur = 0; 
	Production prod;
	vector<Production> seq;
	while (grammar[cur] != end)
	{

		if (grammar[cur] == '(')
		{
			string c = grammar;
			pair<Production, int> res = makeProductionUntil(c.erase(0, cur), ')');
			cur += res.second;
			if (cur + 1 < grammar.size() && grammar[cur + 1] == '*')
			{
				res.first.setType(cycle);
				cur++;
			}
			seq.push_back(res.first);
		}
		else if (grammar[cur] == '[')
		{
			string c = grammar;
			pair<Production, int> res = makeProductionUntil(c.erase(0, cur), ']');
			cur += res.second;
			if (cur + 1 < grammar.size() && grammar[cur + 1] == '*')
			{
				res.first.setType(cycle);
				cur++;
			}
			res.first.setType(additional);
			seq.push_back(res.first);
		}
		else if (grammar[cur] == '|')
		{
			prod.alternatives.push_back(seq);
			seq = {};
		}
		else if (grammar[cur] == ' ' || grammar[cur] == '\n' || grammar[cur] == '\t' || grammar[cur] == '\r')
		{
			if (wrd != "")
			{
				Production a(wrd);
				a.setType(nonterm);

				seq.push_back(wrd);
				wrd = "";
			}
		}
		else if (grammar[cur] == '\'')
		{
			string tokenStr = "";
			while (grammar[cur] != '\'')
			{
				tokenStr += grammar[cur];
				cur++;
			}
			Production a(tokenStr);
			a.setType(term);
		}
		else
		{
			wrd += grammar[cur];
		}
		cur++;
	}
	pair<Production, int> ans;
	prod.alternatives.push_back(seq);
	ans.first = prod;
	ans.second = cur;
	return ans;
}

Production::~Production()
{
}
