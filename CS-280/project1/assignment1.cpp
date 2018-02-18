/*
Author: Abhishek Naik
Date: 1/28/2014
Purpose: Assignment 1
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void matchPattern(string, vector<string>, int);			//goes thruoogh the lines and checks for a match
void input(vector<string>&);							//get input from user when no file found
void readFile(vector<string>&, string);					//read data from file into content
void output(int, vector<string>, int);					//print context lines before the match
int outputAfter(int,vector<string>, int, string);		//print context lines after and if match found then reset context and print after those
bool checkLine(string, string);							//check to see if the pattern was found in the sentence.



int main(int argc, char *argv[]) 
{
	vector<string> content (0);				//this will hold the content and its initial size is 1.
	int context = 0;
	if (argc == 1)
	{
		cout <<"No commandline argument was given" << endl;
		return 0;
	}
	if(argc == 2 && (argv[1][0] == '+'))
	{
		cout <<"you Entered " << argv[1] << " which is invalid number, and you did not include a pattern" << endl;
		return 0;
	}
	else if(argc == 2)
	{
		input(content); //get the content 
		matchPattern(argv[1], content, context);
	}
	else if(argc == 3 && argv[1][0] == '+')
	{
		input(content);
		string temp = argv[1];
		try{
		context = atoi(temp.substr(1).c_str());
		}catch(int e)
		{
			cout << "invalid number so bye" << endl;
			return 0;
		}
		matchPattern(argv[2], content, context);
	}
	else if(argc == 3)
	{
		readFile(content, argv[2]);
		matchPattern(argv[1],content, context);
	}
	else if(argc == 4)
	{
		string temp = argv[1];
		try{
		context = atoi(temp.substr(1).c_str());
		}catch(int e)
		{
			cout << "invalid number so bye" << endl;
			return 0;
		}
		readFile(content, argv[3]);
		matchPattern(argv[2], content, context);
	}
	else if(argc > 4)
	{
		cout <<"You entered more then 3 commend line arguments" << endl;
		return 0;
	}
	
	system("pause");
	return 0;
}
bool checkLine(string sent, string pat)
	{
		if(pat.length() == 0)
			return true;
		while(sent.length() >= pat.length())
		{
			int x = 0;
			for(int i = 0; i < pat.length(); i++)
			{
				if(i == pat.length()-1 && ((pat[i] == sent[i - x]) || pat[i] == '.'))
				{
					return true;
				}
				if(pat[i] == '.' || pat[i] == sent[i - x]) //check if its a period or the char matches
					continue;				//continue if it is
				else if(pat[i] == '\\' && pat[i + 1] == sent[i - x])
				{
					x++;
					continue;						
				}
				else
					break;
			}
			sent = sent.substr(1, sent.length());
		}
		return false;
	}

void matchPattern(string pattern, vector<string> content, int context)
{
	for(int line = 0; line < content.size(); line++)
	{
		if(checkLine(content[line], pattern)) 
		{
			output(line, content, context);						//print the first couple lines
			line = outputAfter(line, content, context, pattern);
		}
	}
}

void output(int mPoint, vector<string> content, int context)
{
	if(mPoint - context < 0) //if match point - context is less then 0
	{
		for(int aPoint = 0; aPoint < mPoint; aPoint++)		//loop through and print first lines of match
		{
			cout << content[aPoint] << endl;
		}
	}
	else
	{
		for(int aPoint = mPoint - context ; aPoint < mPoint; aPoint++)		//loop through and print first lines of match
		{
			cout << content[aPoint] << endl;
		}
	}
}

int outputAfter(int mPoint, vector<string> content, int context, string pattern)
{
	cout << content[mPoint] << endl;
	int pointer = mPoint + context;
	for (int i = mPoint + 1; i <= pointer; i++)
	{
		if(i == content.size() - 1)		//exit the function and end program if reached end of content
			return content.size();
		if(checkLine(content[i], pattern))	//if we find match while printing
		{
			cout << content[i] << endl;		//print that line and change the end position to +context from there
			pointer = i + context;
		}
		else
			cout << content[i] << endl;
	}
	return pointer;
}

void input(vector<string>& content)
{
	string line;

	while(getline(cin,line))
	{
		content.push_back(line);
	}

}

void readFile(vector<string>& content, string fileName)
{
	string line;
	fstream myFile;
	myFile.open(fileName.c_str());
	if(!myFile.is_open())
	{
		cout << "Error opening the file" << endl;
		exit(EXIT_FAILURE);
	}
	while(getline(myFile,line))
	{
		content.push_back(line);
	}

}
