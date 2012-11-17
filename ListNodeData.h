/*
	Yong Wen Chua
	http://bit.ly/yongwen
	Released under the LGPL license
*/
/*
	Custom Data Type to meet requirements in the Assignment.
*/
//These Macros ensure that the file is only #included once.
#pragma once
#ifndef ListNodeData_H
#define ListNodeData_H

#include <string>
using namespace std;

class ListNodeData{
	private:				//Private Members
		int _number;			
		string _text;

	public:
		//Constructors
		ListNodeData(){}							//Default Uninitialised Constructor
		ListNodeData(int number, string text){		//Constructor
			SetNumber(number);
			SetText(text);
		}
		ListNodeData(int number, char *text){		//C-string variant
			SetNumber(number);
			SetText(text);
		}
		//Various Methods to set data
		void SetNumber(int number){ _number = number; }		//Set the number
		void SetText(string text){ _text = text; }		//Set the text
		void SetText(char *text) { _text = text; };		//C-String variant
		
		//Methods to retrieve data
		int Number(){ return _number; }			//Retrieve Number
		string Text() { return _text; }			//Retrieve Text
		
		//Overloaded Operators
		operator int(){ return _number; }									//Overloaded int type cast operator
		bool operator<(ListNodeData &op){ return (int(*this) < int(op)); }	//Overloaded < comparison operator with integers
		bool operator>(ListNodeData &op){ return (int(*this) > int(op)); }	//Overloaded > comparison operator with integers
		bool operator<=(ListNodeData &op){ return (int(*this) <= int(op)); }	//Overloaded <= comparison operator with integers
		bool operator>=(ListNodeData &op){ return (int(*this) >= int(op)); }	//Overloaded >= comparison operator with integers
		bool operator==(ListNodeData &op){										//Overloaded == comparison with other data
			return (this->Number() == op.Number() && this->Text() == op.Text());	
		}
		
		//Friend functions are used so that comparison with integers/strings can be done in any order
		friend bool operator==(ListNodeData &op1, string op2);			//Overloaded Operator for comparison with strings
		friend bool operator==(string op1, ListNodeData &op2);			//Overloaded Operator for comparison with strings
		friend bool operator==(ListNodeData &op1, int op2);				//Overloaded Operator for comparison with int
		friend bool operator==(int op1, ListNodeData &op2);				//Overloaded Operator for comparison with int
		
		bool operator!=(ListNodeData &op){								//Overloaded != comparison operator.
			return (this->Number() != op.Number() || this->Text() != op.Text());	
		}
};
#endif /* ListNodeData_H */