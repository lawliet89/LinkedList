/*
	Yong Wen Chua
	http://bit.ly/yongwen
	Released under the LGPL license
*/
/*
	Custom Data Type to meet requirements in the Assignment.
*/
#include <string>
#include "ListNodeData.h"
using namespace std;

//Friend Functions
bool operator==(ListNodeData &op1, string op2){
	return (op1.Text() == op2);
}
bool operator==(string op1, ListNodeData &op2){
	return (op2.Text() == op1);
}
bool operator==(ListNodeData &op1, int op2){
	return ( int(op1) == op2);
}
bool operator==(int op1, ListNodeData &op2){
	return (op1 == int(op2));
}