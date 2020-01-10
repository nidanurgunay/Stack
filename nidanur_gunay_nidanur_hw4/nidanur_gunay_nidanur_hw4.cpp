#include <iostream>
#include <fstream>
#include "DynIntStack.h"
#include <string>
#include <sstream>

using namespace std;

// this function checks if the line has a keyword
bool keywords(string line )
{
	string words;
	istringstream iss(line);
	while(iss>>words)
	{ 
		if(words=="if" || words=="else" || words== "for" || words=="elif" ||words=="while")
		{
			cout<<"Keyword " << words<< " found on this line. \n";
			return true;			
		}
	}
	return false;
}


int main()
{
	ifstream python;
	string input;
	cout<<"Please enter the file name that is going to be analyzed. \n";
	cin>> input;
	python.open(input.c_str());
	if(!python.fail())
		cout<<"Starting file analysis... \n";
	
	while(python.fail())//check the input
	{
		cout<<"Unable to open file please enter a different file name. \n";
		cin>> input;
		python.open(input.c_str());

			if(!python.fail())
		cout<<"Starting file analysis... \n";
	}
	cout<<"Initial indentation level is pushed to the stack as 0. \n\n";
	DynIntStack stack;
	stack.push(0);// i push 0 to stack as intializer
	string line,word;
	char c=' ';
	int l=1, clevel=0;
	bool check=false;
	
	while(getline(python,line))
	{
		cout<<"Line number: "<< l<<endl;
		cout<<"Line: "<< line<<endl;
		int i=0;
		while(line.substr(i,1)==" ")
			i++;//calculate the number of space
		cout<< i<< " number of spaces observed before the start of the line. \n";
		
			if(check)			
			cout<<"This line proceeds a keyword containing line.\n";//if the previous linehas a keyword
		
		cout<<"Current Level = " << clevel<< " This line = "<< i <<endl;

		if(!check && (clevel <i))// if the previous line does not have any keyword and current line is greater than current indentation level
		{
			cout <<"Incorrect file structure. \n"<<"Current line cannot be greater than the Current indentation level. \n";
			cout<< "Stopping file analysis...  \n \n"<< "Stack emptied and program ending. \n";
			return 0;
		}

		if(check && clevel>=i) // if the prev line has keyword and indentation level is not sufficient
		{
			cout <<"Incorrect file structure. \n"<<"Current line must be greater than the Current indentation level.  \n";
			cout<< "Stopping file analysis...  \n \n"<< "Stack emptied and program ending. \n";
			return 0;
		}


		if(!check && !(clevel>i))//	if the line is proper
		cout<<"Line belongs to current block. \n";
	

		if(clevel>i) // if the number of space is less than current level
		{
			int s;
			stack.pop(s);//checking the stack if the line belings to prev indntation level
		
			while(s!=i && !stack.isEmpty())//find the line which belongs to proper indentation level
			{
				stack.pop(s);			
				cout<<"Current line is smaller than Current indentation level; checking if line belongs to outer indentation. \n";
				cout<<"Current Level = " << s<< " This line = "<< i <<endl;
			}
			
			if(s==i)//if you find the proper indentation level
			{
				clevel=s;
				cout<<"Line belongs to outer block. \n";
			}
		
			else  ///if there is no indentation levl that match up with the prev indentation levels
			{
				cout <<"Incorrect file structure. \n"<<"An indentation level same as the Current line is not found in outer blocks. \n";
				cout<< "Stopping file analysis...  \n \n"<< "Stack emptied and program ending. \n";
				return 0;
			}
		
			stack.push(s);

		}
			
		if(check)
		{
			cout<<"Line correct. Depth "<< i <<" added to the stack. \n"; 
			clevel=i;
			stack.push(i);
		}
		
		check=keywords(line);// check if the line has a keyword
		cout<<endl;
		l++;
	}
	while(!stack.isEmpty()) // making the stack empty
	{
		int s;
		stack.pop(s);
	}
	cout<<"\n Finished file analysis. \nFile structure is correct! \n ";

	return 0;
}


