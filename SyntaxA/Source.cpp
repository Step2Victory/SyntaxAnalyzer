#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Pair
{
public:
	string first;
	int second; // 1 - Òîêåí, 0 - Íåèçâåñòíî
	Pair(string a, int b)
	{
		first = a;
		second = b;
	}
	Pair() {}
};

string resize(string s, int start, int end)
{
	string res;
	for (int i = start; i <= end; i++)
	{
		res += s[i];
	}
	return res;
}

vector<Pair> Lexer(vector<string> Tokens, vector<string> program)
{
	string string_program;
	for (int i = 0; i < program.size(); i++)
	{
		string_program += program[i] + "\n";
	}


	vector<Pair> result;
	string current;

	for (const auto c : string_program)
	{
		current += c;
		string tmp;
		for (int i = 0; i < current.size(); i++)
		{
			tmp = resize(current, i, current.size() - 1);
			for (const string s : Tokens)
			{
				if (tmp == s)
				{
					if (i != 0)
					{
						result.push_back(Pair(resize(current, 0, i - 1), 0));
					}
					result.push_back(Pair(tmp, 1));
					current = "";
					break;
				}
			}
		}
	}



	return result;
}

ostream& operator<<(ostream& out, vector<Pair> a)
{
	for (int i = 0; i < a.size(); i++)
	{
		cout << "{ '" << a[i].first << "', " << a[i].second << " } ";
	}
	return out;
}


int main()
{
	vector<string> prog = { "print(abc)", "fprintg" };
	vector<string> tok = { "print", "(", ")" };

	cout << Lexer(tok, prog);

}