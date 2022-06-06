#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

const string kwrds[] = {"class","if", "else", "while", "do", "break", "continue", "int", "double", "float", "return", "char", "string", "case", "sizeof", "long", "short", "typedef", "switch", "unsigned", "void", "struct", "goto", "static","class", "for", "continue", "private", "include", "iostream", "using", "namespace", "std", "cout", "endl", "public"};
const char ops[] = {'+', '-', '*', '^', '/', '>', '<', '=', '.', '%', '&', '|', '~', ','};
const string binOps[] = {"<<", "++", "--", "+=", "-=", "*=", "/=", ">>", "&&", "||", "!="};
const char seps[] = {' ', ';', '(', ')',']', '[', '{', '}', '"', '#', ';', ',', '\'', ':'};

string sTable[1024];
int sIndx = 0;

bool isseparators(char ch) 
{
	for(char c: seps)
		if(ch == c)
			return true;
			
	return false;
}

bool isOperator(char ch)
{
	for(char c: ops)
		if(ch == c)
			return true;
			
	return false;
}

bool isKeyWord(string str)
{
	for(string key: kwrds)
		if(key == str)
			return true;
			
	return false;
}

bool isNum(char c)
{
	int code = (int)c;
	if(!(48 <= code && code <=57))
		return false;  
	
	return true;
}

bool isInteger(string str)
{
	for(char c: str)
		if(!isNum(c))
			return false;  
	return true;
}


bool isReal(string str)
{
	bool hasDec = false;
	for(char c : str)
	{
		if(c == '.')
		{
			hasDec = true;
			continue;
		}
		
		if(!isNum(c))
			return false;  	
	}

	return hasDec;
}

bool isAlphabet(char c)
{
	if((97 <= c && c <= 122) || (65 <= c && c <= 90))
		return true;
	
	return false;
}

bool isBinaryOperator(char op1, char op2)
{
	for(string s: binOps)
		if(s[0] == op1 && s[1] == op2)
			return true;
			
	return false;
}

void addSymbol(string s)
{
	sTable[sIndx++] = s;
}

bool isIdentifier(string str)
{
	if(!isAlphabet(str[0]) && str[0] != '_')
		return false;

	for(char c: str)
		if(!isAlphabet(c) && !isNum(c) && (c != '_'))
			return false;

	return true;
}

bool checkTable(string str)
{
	for(int i = 0; i < sIndx; i++)
		if(str == sTable[i])
			return true;
	
	return false;
}

void parse(string uri)
{
string buff, str;
ifstream stream(uri);
bool indentifier = false;
bool comments = false, multiLineComment = false;
bool rvalue = false;
unordered_set<string> kwr, idfs, intr, rlnum;
unordered_set<char> oprt; 

cout<<"# is a Special Keyword\n";
cout<<"; is a Special Keyword\n";
if(!stream.is_open())
{
	throw runtime_error("Could not open the file");
	exit(1);
}

while(getline(stream, str, ';'))
{

indentifier = false;

for(int i = 0; i < str.length(); i++)
{

	if(i > 0 && str[i] == '/' && str[i-1] == '*')
	{
		multiLineComment = false;
		continue;
	}

	if(str[i] == ' '|| str[i] == '\n' || str[i] == '\t' || comments == true || multiLineComment == true)
	{
		if(str[i] == '\n')
			comments = false;
		buff = "";
		continue;
	}


	buff = buff + str[i];

	if((i == (str.length() - 1)) || isseparators(str[i+1]) || isOperator(str[i+1]) || isseparators(str[i]) || isOperator(str[i]))
	{

		if(isseparators(buff[0]))
		{
			if(buff[0] == '"')
			{
				i++;
				while(str[i] != '"')
				{
					if(str[i] != '\n')
						cout << str[i];
					i++;
					if(i >= str.length()) 
						throw runtime_error("missing \'\"\'");
				}
				cout << " is a String Constant" << endl;
				continue;

			}

			if(buff[0] == '\'')
			{
				cout << str[i+1] << " is a Character Constant" << endl;
				i += 2;
				cout << (bool)(str[i] != '\'');
				if(i < str.length() && str[i] != '\'') 
					throw runtime_error("invalid character declaration");
				continue;

			}

			
		} 
		else if(isOperator(buff[0]))
		{
			if(indentifier == true && buff[0] == ',') 
			{
				indentifier =  true; 
				rvalue = false;
			}

			else if(buff[0] == '/' && str[i+1] == '/')
			{
				comments = true;
				i++;
				continue;
			} 

			else if(buff[0] == '/' && str[i+1] == '*')
			{
				multiLineComment = true;
				i++;
				continue;
			}

			oprt.insert(buff[0]);

			if(buff[0] == '=')
				rvalue = true;
		}

		else if(isKeyWord(buff))
		{
			kwr.insert(buff);
			indentifier = true;
		}

		else if(isInteger(buff))
			intr.insert(buff);
		
		else if(isReal(buff))
			rlnum.insert(buff);
		
		else if(isIdentifier(buff))
		{
			if(indentifier && !rvalue && !checkTable(buff))
				addSymbol(buff);
			else 
			{
				if(checkTable(buff))
					indentifier = true;
				else
				{
					throw runtime_error(buff + " identifier is not declared");
					buff = "";
					continue;
				}
			}
			if(buff == "name" or buff == "id")
				idfs.insert("s1." + buff);
			else
				idfs.insert(buff);
				

		}

		else
			throw runtime_error(buff + " ---> not valid identifier");

		buff = "";
	}
}
}

cout<<"Keywords : ";
for(auto x : kwr)
	cout<<x<<" ";

cout<<"\nOperators : ";
cout<<"<< ";
for(auto x : oprt)
	cout<<x<<" ";

cout<<"\nIntegers : ";
for(auto x : intr)
	cout<<x<<" ";

cout<<"\nReal Numbers : ";
for(auto x : rlnum)
	cout<<x<<" ";

cout<<"\nIdentifiers : ";
for(auto x : idfs)
	cout<<x<<" ";

}

int main() 
{
	parse("program.txt");
	return 0;
}