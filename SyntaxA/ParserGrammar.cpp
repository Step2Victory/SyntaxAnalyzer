#include "ParserGrammar.h"

GrammarParser::GrammarParser()
{
	description = "";
	iter = 0;
}

GrammarParser::GrammarParser(string _description)
{
	description = _description;
	iter = 0;
}


string GrammarParser::parseWord(bool ignore_whitespace, char end)
{
	string word = "";
	iter++;
	if (ignore_whitespace)
	{
		while (description[iter] != end)
		{
			word += description[iter];
			iter++;
		}
	}
	else
	{
		while (description[iter] == '\n' || description[iter] == '\t' || description[iter] == '\r')
			iter++;
		while (description[iter] != '\n' || description[iter] != '\t' || description[iter] != '\r' ||
			description[iter] != ':' || description[iter] != '|' || description[iter] != '(' ||
			description[iter] != ')' || description[iter] != '[' || description[iter] != ']' ||
			description[iter] != '\'' || description[iter] != '"' || description[iter] != '*')
		{
			word += description[iter];
			iter++;
		}
	}
	if (word != "")
		lastword = word;
	return word;
}

Production * GrammarParser::parseUntil(char end)
{
	string current = "";
	Production* pcurrent = nullptr;
	vector<Production*> alts;
	while (description[iter] != end)
	{
		string word = parseWord();
		if (lastword != "")
		{
			Production *a;
			if (isUpper(lastword))
				a = new Production(lastword, terminal);
			else
				a = new Production(lastword, nonterminal);
			lastword = "";
			if (description[iter] == '*')
				a->setType(cycle);
			if (pcurrent == nullptr)
				pcurrent = a;
			else
				alts.push_back(a);
		}
		else if (description[iter] == ':')
		{
			throw "wrong syntax ':'";
		}
		else if (description[iter] == '"' || description[iter] == '\'')
		{
			parseWord(true, description[iter]);
			Production *a = new Production(lastword, terminal);
			lastword = "";
			if (pcurrent == nullptr)
				pcurrent = a;
			if (description[iter] == '*')
				a->setType(cycle);
			alts.push_back(a);
		}
		else if (description[iter] == '[')
		{
			iter++;
			Production* a = parseUntil(']');
			if (pcurrent == nullptr)
				pcurrent = a;
			a->setType(optional);
			if (description[iter] == '*')
				a->setType(cycle);
		}
		else if (description[iter] == '(')
		{
			iter++;
			Production* a = parseUntil(')');
			if (pcurrent == nullptr)
				pcurrent = a;
			if (description[iter] == '*')
				a->setType(cycle);
		}
		else if (description[iter] == '|')
		{
			pcurrent->addAlt(alts);
			alts = {};
		}
		else if (description[iter] == ']' || description[iter] == ')')
		{
			throw "wrong syntax too many rpars";
		}
		iter++;
	}
	return pcurrent;
}

void GrammarParser::parse()
{
	string current = "";
	Production* pcurrent = nullptr;
	vector<Production*> alts;
	while (iter < description.size())
	{
		string word = parseWord();
		if (lastword != "")
		{
			Production *a;
			if (isUpper(lastword))
				a = new Production(lastword, terminal);
			else
				a = new Production(lastword, nonterminal);
			lastword = "";
			if (description[iter] == '*')
				a->setType(cycle);
			if (pcurrent == nullptr)
				pcurrent = a;
			else
				alts.push_back(a);
		}
		else if (description[iter] == ':')
		{
			if (current != "")
			{
				grammar[current] = pcurrent;
				pcurrent->addAlt(alts);
				alts = {};
			}
			if (lastword != "")
				grammar[lastword];
			else
				throw "No word before ':'";
			current = lastword;
			lastword = "";
			pcurrent = nullptr;
		}
		else if (description[iter] == '"' || description[iter] == '\'')
		{
			parseWord(true, description[iter]);
			Production *a = new Production(lastword, terminal);
			lastword = "";
			if (pcurrent == nullptr)
				pcurrent = a;
			if (description[iter] == '*')
				a->setType(cycle);
			alts.push_back(a);
		}
		else if (description[iter] == '[')
		{
			iter++;
			Production* a = parseUntil(']');
			if (pcurrent == nullptr)
				pcurrent = a;
			a->setType(optional);
			if (description[iter] == '*')
				a->setType(cycle);
		}
		else if (description[iter] == '(')
		{
			iter++;
			Production* a = parseUntil(')');
			if (pcurrent == nullptr)
				pcurrent = a;
			if (description[iter] == '*')
				a->setType(cycle);
		}
		else if (description[iter] == '|')
		{
			pcurrent->addAlt(alts);
			alts = {};
		}
		else if (description[iter] == ']' || description[iter] == ')')
		{
			throw "wrong syntax too many rpars";
		}
		iter++;
	}
}

void GrammarParser::printGrammar()
{
	for (auto it : grammar)
	{
		cout << it.first << " " << it.second;
	}
}

map<string, Production*> GrammarParser::parseGrammar()
{
	iter = 0;
	parse();
	return grammar;
}

GrammarParser::~GrammarParser()
{
}
