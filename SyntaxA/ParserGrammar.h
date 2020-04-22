#pragma once
#include <map>
#include <iostream>
#include "Production.h"
using namespace std;


class GrammarParser
{
	string description;
	map<string, Production*> grammar;
	int iter;
	string lastword;
public:
	GrammarParser();
	GrammarParser(string);
	string parseWord(bool ignore_whitespace = false, char end = '"');
	Production* parseUntil(char end);
	void parse();
	void printGrammar();
	map<string, Production*> parseGrammar();
	~GrammarParser();
};

bool isUpper(string s)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if ('a' <= s[i] <= 'z')
		{
			return false;
		}
	}
	return true;
}