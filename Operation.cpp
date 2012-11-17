/*
	Yong Wen Chua
	http://bit.ly/yongwen
	Released under the LGPL license
*/
/*
	This file contains the operation procedures to deal with the command file and date files.
*/
#include "Operation.h"
#include "List.h"
#include "ListNodeData.h"
using namespace std;

//Global Variable
extern LinkedList<ListNodeData>  TheList;
extern ifstream CommandFile, DataFile;
extern ofstream OutputFile;
extern string FileNumber;

istream& GetLine(istream& is, string& str){		//This function removes the \r carriage return if a Unix system is detected.
	//Doing code that needs to work across platforms IS difficult.
	str = "";	
	while (str.empty() && !is.eof()){		//Try to get a "proper" line and ignore empty lines
		getline(is, str);
	}
	
	//Use of EVIL MACROS to detect Windows. If it is Windows, we don't have to do the following.
	#ifndef _WIN32
		if (str.empty()){				//This means that EOF has been reached
			return is;
		}	
		if (str[str.length()-1] == '\r'){
			str = str.substr(0, str.length()-1);
			if (str.empty()){
				return GetLine(is, str);
			}
		}
	#endif

	return is;
}


void OpenOutputFile(){
	static string _FileNumber = "";
	if (!OutputFile.is_open() || _FileNumber != FileNumber){
		_FileNumber = FileNumber;
		if (OutputFile.is_open()){
			OutputFile.close();
		}
		string file = "output_" + FileNumber + ".txt";
		cout << "Opening output file...";
		OutputFile.open(file.c_str(), ios::ate | ios::app | ios::out);
		if (!OutputFile){
			TerminateError("Unable to open output file.");
		}
	}
}

void ReadDataFile(){
	cout << "Opening data file 'data_" << FileNumber << ".txt'..." << endl;
	string file = "data_" + FileNumber + ".txt";
	DataFile.open(file.c_str());
	if (!DataFile){
		TerminateError("Unable to open data file.");
	}
	ListNode<ListNodeData> *node = NULL;
	//Find the last node to append the list, if the list is already with items. 
	TheList.Rewind();
	while (TheList.Current() != NULL){
		node = TheList.Current();
		TheList.Next();
	}
	string text, dummy;
	int number;
	//Read data file into list
	while (!DataFile.eof()){
		GetLine(DataFile, text);		//GetLine gets rid of newline character.
		if (DataFile.eof()){			//EOF was reached before a number is read!? Means file is malformed. Ignoring final node.
			cout << "Unexpected end of file for data file. Finishing read." << endl;
			break;
		}
		DataFile >> number;
		getline(DataFile, dummy);	//Use GetLine to clear the newline character.
		//The default behaviour of inserting new nodes to the list is by inserting it at the first node.
		//So we need a "workaround" to build the list as it was defined in the data file.
		cout << "Appending Node " << text << " " << number << endl;
		if (node == NULL){
			node = TheList.InsertNewNode(ListNodeData(number, text));		//This is the first node.
		}
		else{
			node = TheList.AppendNode(node, ListNodeData(number, text));	//Append additional node behind the first node
		}
		
	}
	DataFile.close();
}

void DumpFile(){
	OpenOutputFile();
	//Estabilish Output File
	TheList.Rewind();
	cout << "Dumping file... ";
	while(TheList.Current() != NULL){
		OutputFile << TheList.Current()->Data().Text() << endl << TheList.Current()->Data().Number() << endl;
		TheList.Next();
	}
	cout << " Dumped." << endl;
	
}

void DumpAverage(){
	cout << "Calculating average... ";
	double sum = 0, count = 0;
	//Traverse the list
	TheList.Rewind();
	while (TheList.Current() != NULL){
		count ++;
		sum += TheList.Current() -> Data().Number();
		TheList.Next();
	}
	double average = sum/count;

	cout << showpoint << average << " Dumping to file...";
	//Estabilish Output File
	OpenOutputFile();
	OutputFile << "Average Value: " << dec << average << endl;
	cout << " Dumped." << endl;
}

void DumpMax(){
	cout << "Determining maximum... ";
	int max = 0;
	//Traverse the list
	TheList.Rewind();
	while (TheList.Current() != NULL){
		max = (TheList.Current() -> Data().Number() > max) ? TheList.Current() -> Data().Number() : max;
		TheList.Next();
	}

	cout << max << " Dumping to file...";
	//Estabilish Output File
	OpenOutputFile();
	OutputFile << "Maximum Value: " << dec << max << endl;
	cout << " Dumped." << endl;
	OutputFile.close();
}