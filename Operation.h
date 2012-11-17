/*
	Yong Wen Chua
	http://bit.ly/yongwen
	Released under the LGPL license
*/
/*
	This file contains the operation procedures to deal with the command file and data files.
*/
//These Macros ensure that the file is only #included once.
#pragma once
#ifndef Operation_H
#define Operation_H

#include <cstdlib>				//Required for use of exit(). Otherwise G++ will complain
#include <iostream>
#include <fstream>
#include <string>
//#include <cstring>
#include <iomanip>

using namespace std;

//Function Prototypes

//"Overloaded" version of GetLine() to deal with carriage return \r
//Also if an empty line was returned, will attempt to seek to find a line with the proper characters
//If intending to clear the buffer of new lines, call getline() instead.
istream& GetLine(istream& is, string& str);															

void TerminateError(string message);	//Fatal error

void OpenOutputFile();	//Initialise output file stream
void ReadDataFile();	//Read data file
void DumpFile();		//Dump list data to file
void DumpAverage();		//Dump average
void DumpMax();			//Dump max

#endif /* Operation_H */