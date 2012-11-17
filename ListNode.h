/*
	Yong Wen Chua
	http://bit.ly/yongwen
	Released under the LGPL license
*/
/*
	Each node contains two elements
		-> A pointer to the next node
		-> An object of type TData

	A new node SHOULD not be created manually but via the LinkedList class.
	Because templates are used, we cannot separate the declaration from the definition into different files.
*/
//These Macros ensure that the file is only #included once.
#pragma once
#ifndef ListNode_H
#define ListNode_H

template <typename TData=int> class ListNode{
	TData _data;
	ListNode<TData> *_nextNode;

	public:
		//Constructors
		ListNode(){		//Default uninitialised Constructor
			_nextNode = NULL;
		}

		ListNode(TData data, ListNode<TData> *next = NULL){		//Construct the node with information
			SetData(data);
			SetNext(next);
		}
		~ListNode(){
			//cout << "Destroying Node " << int(_data) << endl;
		}

		//Get a pointer to next mode
		ListNode<TData> *Next(){
			return _nextNode;
		}
		//Gets a pointer to node Data
		TData &Data(){
			return _data;
		}

		//Set Pointer to next node
		void SetNext(ListNode<TData> *next){
			_nextNode = next;
		}

		//Set data to data.	
		//Note: A copy of data will be made! Make sure to overload the copy mechanism in TData if necessary!
		void SetData(TData data){
			_data = data;
		}
};
#endif /* ListNode_H */