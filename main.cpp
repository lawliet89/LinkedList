/*
	Yong Wen Chua
	http://bit.ly/yongwen
	Released under the LGPL license
*/
/*
	Description of Implementation:

	Each linked list is implemented as an object of type LinkedList<ListNodeData>.
	LinkedList contains the methods to manipulate the linked list and contains a pointer to the first node of the list.

	Each node is implented as an object of type ListNode<ListNodeData>. ListNode contains methods to retrive the data of the node itself and contains a pointer to the next node in the list.

	ListNodeData is an object that contains an integer and the string (as specified in the assignment). It also includes methods to	set and retrieve the data. It overloads the necessary operators to allow for comparison between objects of the same type.

	main.cpp opens a command file specified in its runtime argument and parses it for argument. You can ignore it and skip to the class for the crux.
*/
#include "Operation.h"
#include "List.h"
#include "ListNodeData.h"		//List Node Data is "custom"

using namespace std;

//Global Variables
LinkedList<ListNodeData>  TheList;			//The Linked List
ifstream CommandFile, DataFile;				//Input File Streams
ofstream OutputFile;						//Output file streams
string FileNumber;							//File Number for input and output

int main(int argc, char* argv[]){
	if (argc < 2){			//Missing argument
		TerminateError("You need to specify a command file to load!");
	}
	//Open the command file
	cout << "Open command file " << argv[1] << "..." << endl;
	CommandFile.open(argv[1]);
	if (!CommandFile){
		TerminateError("Unable to open command file.");
	}
	cout << "Parsing and executing command file..." << endl;
	string line, text, search;
	int number;
	while (!CommandFile.eof()){			//Iterate till end of file
		//Using Getline instead of the extraction operator takes care of the newline character
		//cf same problem with sscanf()
		GetLine(CommandFile, line);			
		//Parse for commands
		if (line == "r" || line == "R"){		//Read Command. Next command is file number
			GetLine(CommandFile, FileNumber);		//GetLine gets rid of newline character.
			ReadDataFile();
		}
		else if (line == "s" || line == "S"){	//Sort
			cout << "Sorting List..." << endl;
			TheList.Sort(Ascending);			//The SortOrder enum is defined in List.h
		}
		else if (line == "w" || line == "W"){	//Write file
			DumpFile();
		}
		else if (line == "i" || line == "I"){	//Insert. Next two commands to be text and number
			GetLine(CommandFile, text);		//GetLine gets rid of newline character.
			CommandFile >> number;			//atoi() not used to prevent legacy problems. stringstream not used to prevent overhead
			getline(CommandFile, line);		//Extract and discard the newline character to prevent unknown command errors
			TheList.InsertNewNodeOrdered(ListNodeData(number, text));		//Insert new node based on data
			cout << "Inserting new node... " << text << " " << number << endl;
		}
		else if (line == "d" || line == "D"){	//Delete. Next command to be search parameter
			GetLine(CommandFile, search);		//GetLine gets rid of newline character.
			cout << "Deleting node " << search << "... ";
			
			cout << (TheList.DeleteNode(search,1) == 1 ? "Deleted." : "Not found.") << endl;
		}
		else if (line == "x" || line == "X"){		//Reverse list
			cout << "Reversing list..." << endl;
			TheList.Reverse();
		}
		else if (line == "a" || line == "A"){		//Dump average value
			DumpAverage();
		}
		else if (line == "m" || line == "M"){		//Dump max value
			DumpMax();
		}
		else{										//Unknown command. Possibly non wellformed command file?
			//EOL Format: Windows: \r\n Mac: \r Unix: \n
			cout << "Unknown command '" << line << "'. Ignoring." << endl;	
		}

	}
	OutputFile.close();
	cout << "-----------------" << endl << "Operation Complete. Type anything and enter to exit." << endl;
	string dummy;				
	cin >> dummy;				//A mechanism to allow the user to view the output, especially on Windows.

	//RunDebug();				//The debug function is a set of function to test the linked list.
	return 0;
}

/*
	General Functions
*/
void TerminateError(string message){
	cout << "Error encountered: " << message << endl;
	cout << "-----------------" << endl << "Type anything and enter to exit." << endl;
	string dummy;				
	cin >> dummy;				//A mechanism to allow the user to view the output, especially on Windows.
	exit(1);
}