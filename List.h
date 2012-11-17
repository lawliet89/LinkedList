/*
	Yong Wen Chua
	http://bit.ly/yongwen
	Released under the LGPL license
*/
/*
	LinkedList is a class that implements a linked list. 
	Each node of the list, implemented as ListNode<TData> contains data of the generic type TData.

	In general, any type of data will work with LinkedList. 
	However, to attain maximum compatibility, TData should implement the following:
		- TData should overload the int() operator
			The list is sorted out based on an integer index assigned to each node. This index is retrieved
			by using the int() operator on the data. Thus, in order to utilise ordered methods of the list,
			the int() operator should be overloaded.

		- TData should overload the == operator
			In order to search through the list, the data has to be compared with the parameters.
			As TData is a generic type, the class will not know how to compare the parameters.
			If TData is not a basic type, it should overload the == operator

	LinkedList has some public "iteration" methods to allow the user to traverse the list.
	E.g. Rewind(), Next(), Previous()

	NB: Is there a way to require template type to derive from a base class (in other words, "implement" an interface)?
	Because templates are used, we cannot separate the declaration from the definition into different files.
*/

//These Macros ensure that the file is only #included once.
//See http://en.wikipedia.org/wiki/Include_guard & http://en.wikipedia.org/wiki/Pragma_once
#pragma once
#ifndef List_H
#define List_H

#include <new>
#include "ListNode.h"

//using namespace std;

enum SortOrder { Unordered, Ascending, Descending };		//Sort order enumeration
template <typename TData=int> class LinkedList{
	ListNode<TData> *_firstNode;		//Pointer to the first node of the list
	ListNode<TData> *_current, *_previous;	//Current node, previous node.

	//Sort Helper. Helps to compare and swap value. Used by Sort()
	inline bool _SortHelper(ListNode<TData> *previous, ListNode<TData> *current, ListNode<TData> *next, SortOrder SortBy);

	public:

		//Constructors
		LinkedList();								//Creates an empty list
		LinkedList(ListNode<TData> *FirstNode);		//Create a list with an existing first node
		LinkedList(TData data);						//Create a list with one element containing data

		//Destructor
		~LinkedList();
		
		/*
			Retriving Methods
		*/
		ListNode<TData> *GetFirstNode();	//Get a pointer to the first node.
		int Length();		//Returns the number of elements

		/*
			Iteration Methods
		*/
		void Rewind();		//Rewind internal pointer to first element

		//Returns a pointer to current node pointed to by the internal pointer and advance to the next node
		//If attempting to retrive past the last item, a NULL pointer is returned
		ListNode<TData> *Next();
		
		//Returns a pointer to the previous node pointed to by the internal pointer
		//If attempting to retrieve past the first item, a NULL pointer is returned
		ListNode<TData> *Previous();

		//Returns a pointer to the current node pointed to by the internal pointer.
		//If the list is empty, a NULL pointer is returned
		ListNode<TData> *Current();

		//From the current internal pointer, advances the internal pointer until the first match with the search parameter is found
		//Returns a pointer to the node.
		//If you want to search from the start, use Rewind()
		//If nothing is found by the end of the list, null is returned.
		//Template TSearch is used to allow for flexibility in the list node data type used.
		//List Node data being used needs to overload the appropriate comparison operator for the different types of data it expects
		//the user to use!
		//If the second parameter is provided, a pointer to the previous node is provided
		template <typename TSearch> ListNode<TData> *SearchForNode(TSearch search, ListNode<TData> *&previous);
		template <typename TSearch> ListNode<TData> *SearchForNode(TSearch search);

		bool IsLast();		//Check if the internal pointer is pointing to the last item or past the last item
		bool IsFirst();		//Check if the internal pointer is pointing to the first item

		/*
			Modifying Methods
		*/

		//Set the first node of the list to FirstNode. The node is not modified to point to the previous first node!
		//After calling this method, SortStatus will be set to Unordered
		void SetFirstNode(ListNode<TData> *FirstNode);
		
		//Insertion of a New Node at the head of the list in an unordered manner
		//After calling this method, SortStatus will be changed to unordered.
		void InsertNewNode(ListNode<TData> *Node);		//Insert an already created Node
		ListNode<TData> *InsertNewNode(TData data);		//Create a new node based on data. Returns a pointer to node.
		ListNode<TData> *InsertNewNode();				//Create an empty new node. Returns a pointer to node.
		
		/*
			Insert a new node in an ordered manner. The order is determined by SortStatus.
			It will find the first node that satisfies the SortStatus and insert before it.

			If the list is Unordered, this will simply cause the node to be added at the head of the list
		*/
		void InsertNewNodeOrdered(ListNode<TData> *Node);		//Insert an already created Node
		ListNode<TData> *InsertNewNodeOrdered(TData data);		//Create a new node based on data. Returns a pointer to node.
	
		/*
			Search the list for data corresponding to the data and deletes the first n instances of it. Returns the number of items deleted
			Set n to -1 to delete everything it finds

			Note: TData must be able to handle the appropriate overloaded == operator. This is because this class
			has no means of determining the type or structure of TData.

			Causes Rewind() to be called.
		*/
		template <typename TSearch> int DeleteNode(TSearch data, int n = -1);
		//This method simply deletes the node provided to it and does the relinking if the previous node was provided
		//THIS VERSION OF THE METHOD IS POTENTIALLY UNSAFE (i.e. MEMORY LEAK IS POSSIBLE)
		void DeleteNode(ListNode<TData> *Node, ListNode<TData> *previous = NULL);	
		
		//Append after the node provided in an unordered manner. Beware of memory leak. Sets SortStatus to Unordered
		//THESE METHODS ARE POTENTIALLY UNSAFE (i.e. MEMORY LEAK IS POSSIBLE)
		void AppendNode(ListNode<TData> *Node, ListNode<TData> *NewNode);		//Append an already created Node
		ListNode<TData> *AppendNode(ListNode<TData> *Node, TData data);		//Create a new node based on data. Returns a pointer to node.
		ListNode<TData> *AppendNode(ListNode<TData> *Node);				//Create an empty new node. Returns a pointer to node.

		//Insert a node after an existing node and before the next node. Sets SortStatus to Unordered
		void InsertNodeAfter(ListNode<TData> *RefNode, ListNode<TData> *NewNode);
		ListNode<TData> *InsertNodeAfter(ListNode<TData> *RefNode, TData NewData);
		ListNode<TData> *InsertNodeAfter(ListNode<TData> *RefNode);

		//Delete everything down the chain. Remember to set the pointer of the previous item to NULL or provide the pointer.
		//Calls Rewind()
		//THIS VERSION OF THE METHOD IS POTENTIALLY UNSAFE (i.e. MEMORY LEAK IS POSSIBLE)
		void DeleteNodesChained(ListNode<TData> *Node, ListNode<TData> *previous=NULL);
		//Search for the node matching the parameter and then chain deletes itself down the chain.
		//Returns true if the data was found and deletion took place. False otherwise.
		//Calls Rewind
		//Template TSearch is used to allow for flexibility in the list node data type used.
		//List Node data being used needs to overload the appropriate comparison operator for the different types of data it expects
		//the user to use!
		template <typename TSearch> bool DeleteNodesChained(TSearch data);
				
		/*	
			Sort Related
		*/
		void Reverse();				//Reverse the list. Implicitly calls Rewind() Changes SortStatus
		SortOrder GetSortStatus(){ return _SortStatus; }
		
		//	Apply bubble sort algorithmn. Implicitly calls Rewind(). Changes SortStatus
		void Sort(SortOrder SortBy = Ascending);	

		/*
			Static Methods
		*/

		//Node Factory Methods - returns pointer to new node.
		//Be careful of memory leaks if you use these methods!
		//THIS METHOD IS POTENTIALLY UNSAFE! USUALLY, YOU DO NOT NEED TO CALL THIS AT ALL!
		static ListNode<TData> *CreateNode();
		static ListNode<TData> *CreateNode(TData data);

		//Destroy node
		//THIS METHOD IS POTENTIALLY UNSAFE! USUALLY, YOU DO NOT NEED TO CALL THIS AT ALL!
		static void DestroyNode(ListNode<TData> *Node);

	protected:
		SortOrder _SortStatus;			//Stores the sort status of the list
};


/*
	Constructor
*/
template <typename TData> LinkedList<TData>::LinkedList(){		//Set everything to be empty
	_firstNode = NULL;
	_SortStatus = Unordered;
	Rewind();
}


template <typename TData> LinkedList<TData>::LinkedList(ListNode<TData> *FirstNode){
	InsertNewNode(FirstNode);	//Set first node as the node provided
	_SortStatus = Unordered;
	Rewind();
}

template <typename TData> LinkedList<TData>::LinkedList(TData data){
	InsertNewNode(data);		//Create a new node based on data provided.
	_SortStatus = Unordered;
}


/*
	Destructor
*/
template <typename TData> LinkedList<TData>::~LinkedList(){
	//std::cout << "Destroying List" << std::endl;
	//Traverse the list and delete! This is because new nodes are created with the new keyword and needs to be deleted to prevent leaks!
	ListNode<TData> *current, *next;
	current = _firstNode;
	while (current != NULL){
		next = current -> Next();
		DestroyNode(current);		//Destroy the node
		current = next;
	}
}

/*
	Iteration Methods
*/
//Rewind()
template <typename TData> void LinkedList<TData>::Rewind(){
	_current = _firstNode;
	_previous = NULL;
}
//IsFirst()
template <typename TData> bool LinkedList<TData>::IsFirst(){
	return (_current == _firstNode);
}
//IsLast()
template <typename TData> bool LinkedList<TData>::IsLast(){
	if (_current == NULL){
		return true;
	}
	else{
		return (_current -> Next() == NULL);
	}
}
//Previous()
template <typename TData> ListNode<TData> *LinkedList<TData>::Previous(){
	if (IsFirst()){
		return NULL;
	}
	return _previous;
}
//Next()
template <typename TData> ListNode<TData> *LinkedList<TData>::Next(){
	if (_current == NULL){
		return NULL;
	}
	_previous = _current;
	_current = _previous -> Next();

	return Current();
}
//Current()
template <typename TData> ListNode<TData> *LinkedList<TData>::Current(){
	return _current;
}

//SearchForNode
//Template TSearch is used to allow for flexibility in the list node data type used.
//List Node data being used needs to overload the appropriate comparison operator for the different types of data it expects
//the user to use!
template <typename TData> template <typename TSearch> ListNode<TData> *LinkedList<TData>::SearchForNode(TSearch search, ListNode<TData> *&previous){
	if (Current()->Data() == search){
		previous = Previous();
		return Current();
	}
	while (Current() != NULL){
		if (Current()->Data() == search){
			previous = Previous();
			return Current();
		}
		Next();
		
	}
	return NULL;
}
//Since we cannot set a default value for a reference variable, we have to resort to using a dummy variable
template <typename TData> template <typename TSearch> ListNode<TData> *LinkedList<TData>::SearchForNode(TSearch search){
	ListNode<TData> *dummy;
	return SearchForNode(search, dummy);		//dummy is discarded by the time this method returns.
}
/*
	Retrieving methods
*/
//GetFirstNode()
template <typename TData> ListNode<TData> *LinkedList<TData>::GetFirstNode(){
	return _firstNode;
}

//Length()
template <typename TData> int LinkedList<TData>::Length(){
	if (_firstNode == NULL){
		return 0;
	}
	else if(_firstNode -> Next() == NULL){
		return 1;
	}
	else{
		int count = 0;
		ListNode<TData> *current;
		current = _firstNode;
		while (current != NULL){
			count ++;

			current = current -> Next();
		}
		return count;
	}
}

/*
	Modification Methods
*/
//SetFirstNode()
template <typename TData> void LinkedList<TData>::SetFirstNode(ListNode<TData> *FirstNode){
	_firstNode = FirstNode;
	_SortStatus = Unordered;
}

//InsertNewNode()
template <typename TData> void LinkedList<TData>::InsertNewNode(ListNode<TData> *Node){
	Node -> SetNext(_firstNode);
	SetFirstNode(Node);
}
template <typename TData> ListNode<TData> *LinkedList<TData>::InsertNewNode(TData data){
	ListNode<TData> *Node = CreateNode();			//Create a new node based on data provided
	Node -> SetNext(_firstNode);
	Node -> SetData(data);
	SetFirstNode(Node);

	return Node;
}
template <typename TData> ListNode<TData> *LinkedList<TData>::InsertNewNode(){
	ListNode<TData> *Node = CreateNode();			//Create an empty new node.
	Node -> SetNext(_firstNode);
	SetFirstNode(Node);

	return Node;
}

//InsertNewNodeOrdered()
template <typename TData> void LinkedList<TData>::InsertNewNodeOrdered(ListNode<TData> *Node){
	if (_SortStatus == Unordered){
		return InsertNewNode(Node);			//Unordered? Just add the node to the head of the list!
	}
	ListNode<TData> *current, *previous;

	if (_firstNode == NULL){	//No Nodes
		_firstNode = Node;
	}
	else{
		current = _firstNode;
		previous = NULL;
		while (current != NULL){		//Search for node
			if ( 
				(_SortStatus == Ascending && ((int) current -> Data() >= (int) Node -> Data()))
				||
				(_SortStatus == Descending && ((int) current -> Data() <= (int) Node -> Data()))
				){		//Matched!
				Node -> SetNext(current);
				if (previous == NULL){
					_firstNode = Node;
				}
				else{
					previous -> SetNext(Node);
				}
				return;			//Now that the node has been inserted, we can return the method
			}
			else{
				previous = current;
				current = previous -> Next();
			}
		}
		//If this point is ever reached, the node to insert is either the largest (ASC) or the smallest (DSC)
		//Then let's append it to the back
		previous -> SetNext(Node);
	}
}

template <typename TData> ListNode<TData> *LinkedList<TData>::InsertNewNodeOrdered(TData data){
	ListNode<TData> *Node = CreateNode();			//Create a new node based on data to insert.
	Node -> SetData(data);
	InsertNewNodeOrdered(Node);
	return Node;
}

//Sort()
//The sort method works by this: It runs through the list once first to find the length of the list
//Along the way, swap items as necessary.
//Then do the normal sorting.
template <typename TData> void LinkedList<TData>::Sort(SortOrder SortBy){
	if (SortBy == Unordered){
		return;
	}
	if (_firstNode == NULL){		//Zero Items?
		return;
	}
	if (_firstNode -> Next() == NULL){		//1 Item?
		return;
	}
	int length = 0;
	ListNode<TData> *previous, *current, *next;
	previous = NULL;
	current = _firstNode;
	bool swapped = false;
	next = current -> Next();
	//Traverse the list once first to find the length
	while (current != NULL){
		//cout << "Previous: " << (previous == NULL ? -1 :  (int) previous -> Data() ) << "\t";
		//cout << "Current: " << (current == NULL ? -1 : int(current -> Data())) << "\t";
		//cout << "Next: " << (next == NULL ? -1 : int(next -> Data())) << "\t";
		bool _swapped = _SortHelper(previous, current, next, SortBy);
		if (_swapped){		//Next is not NULL
			swapped = true;
			length++;
			previous = next;
			next = current -> Next();
			//cout << "Swapped\t";
		}
		else{		//No swapping was done. Next could be NULL.
			length++;
			previous = current;
			current = current -> Next();
			if (current == NULL){
				break;
			}
			next = current -> Next();
			//cout << "Not Swapped\t";
		}
		//cout << "Length: " << length << endl;
	}


	//Debugging Purposes
	//current = _firstNode;
	//cout << endl << "0 Pass --> Length: " << length << "\t";
	//for (int j = 0; j < length; j++){
	//	cout << (int) current->Data() << " ";
	//	current = current -> Next();
	//}
	//cout <<endl;
	//End Debugging

	//Now that we have found the length, the usual sorting can take place
	if (swapped){
		for (int i = 1; i < length; i++){
			swapped = false;
			previous = NULL;
			current = _firstNode;
			next = current -> Next();
			//By the ith time the list is traversed, the last i items will already be in place.
			//So we don't have to traverse the whole list again.
			for (int j = 0; j < length-i; j++){			
				//cout << "Previous: " << (previous == NULL ? -1 :  (int) previous -> Data() ) << "\t";
				//cout << "Current: " << (current == NULL ? -1 : int(current -> Data())) << "\t";
				//cout << "Next: " << (next == NULL ? -1 : int(next -> Data())) << "\t";
				bool _swapped = _SortHelper(previous, current, next, SortBy);
				if (_swapped){		//Next is not NULL
					swapped = true;
					previous = next;
					next = current -> Next();
					//cout << "Swapped\t";
				}
				else{		//No swapping was done. Next could be NULL.
					previous = current;
					current = current -> Next();
					if (current == NULL){
						break;
					}
					next = current -> Next();
					//cout << "Not Swapped\t";
				}
				//cout << "Length: " << length << endl;
			}

			//Debugging Purposes
			//current = _firstNode;
			//cout << i << " Pass --> Length: " << length << "\t";
			//for (int j = 0; j < length; j++){
			//	cout << (int) current->Data() << " ";
			//	current = current -> Next();
			//}
			//cout <<endl;
			
			//End Debugging

			if (swapped == false){
				break;
			}
		}
	}
	_SortStatus = SortBy;
	Rewind();
}
//Helper method. To compare and then swap if necessary.
template <typename TData> inline bool LinkedList<TData>::_SortHelper(ListNode<TData> *previous, ListNode<TData> *current, ListNode<TData> *next, SortOrder SortBy){
	if (next == NULL){
		return false;
	}
	if ( 
		(SortBy == Ascending && ((int) current->Data() > (int) next->Data()))
		||
		(SortBy == Descending && ((int) current->Data() < (int) next->Data()))
		){
		
		if (current == _firstNode){
			_firstNode = next;
		}
		else{
			previous -> SetNext(next);
		}
		if (next -> Next() == NULL){
			current -> SetNext(NULL);
		}
		else{
			current -> SetNext(next -> Next());
		}
		next -> SetNext(current);

		return true;
	}
	else{
		return false;
	}
}

//Reverse()
template <typename TData> void LinkedList<TData>::Reverse(){
	ListNode<TData> *previous, *current, *next;
	if (_firstNode == NULL){
		return;
	}
	previous = NULL;
	current = _firstNode;
	next = _firstNode -> Next();
	if (next == NULL){
		return;
	}
	//cout << "Reversing" << endl;
	while (next != NULL){
		current -> SetNext(previous);
		previous = current;
		current = next;
		next = current -> Next();
	}
	current -> SetNext(previous);
	_firstNode = current;

	Rewind();

	switch (_SortStatus){
		case Ascending:
			_SortStatus = Descending;
			break;
		case Descending:
			_SortStatus = Ascending;
			break;
		default:
			_SortStatus = Unordered;
			break;
	}
}

//DeleteNode

template<typename TData> template <typename TSearch> int LinkedList<TData>::DeleteNode(TSearch data, int n){
	int count = 0;
	ListNode<TData> *previous, *current, *next;
	previous = NULL;
	current = _firstNode;
	if (current == NULL){
		return 0;
	}
	//Only one node
	if (current -> Next() == NULL){
		if (current -> Data() == data){			//Data matched, let's delete!
			DestroyNode(current);

			_firstNode = NULL;
			return 1;
		}
	}
	next = current -> Next();

	while ( (n > 0 || n == -1) && current != NULL){			//Need to check if the item delete counter
		if (current -> Data() == data){
			DestroyNode(current);
			if (previous == NULL){
				_firstNode = next;
			}
			else{
				previous -> SetNext(next);
			}
			count++;
			if (n != -1){			//-1 is to delete ALL items that match
				n--;
			}
			if (next == NULL){
				break;
			}
			current = next;
			next = current -> Next();
		}
		else{
			if (next == NULL){
				break;
			}
			previous = current;
			current = next;
			next = current -> Next();
		}
	}
	Rewind();
	return count;
}

template <typename TData> void LinkedList<TData>::DeleteNode(ListNode<TData> *Node, ListNode<TData> *previous){
	if (previous != NULL){
		previous ->SetNext(Node -> Next());
	}
	DestroyNode(Node);
	Rewind();
}


//AppendNode()
template <typename TData> void LinkedList<TData>::AppendNode(ListNode<TData> *Node, ListNode<TData> *NewNode){
	_SortStatus = Unordered;
	Node -> SetNext(NewNode);
}
template <typename TData> ListNode<TData> *LinkedList<TData>::AppendNode(ListNode<TData> *Node, TData data){
	_SortStatus = Unordered;
	ListNode<TData> *NewNode = CreateNode(data);
	Node -> SetNext(NewNode);
	return NewNode;

}
template <typename TData> ListNode<TData> *LinkedList<TData>::AppendNode(ListNode<TData> *Node){
	_SortStatus = Unordered;
	ListNode<TData> *NewNode = CreateNode();
	Node -> SetNext(NewNode);
	return NewNode;

}			

//InsertNodeAfter()
template  <typename TData> void LinkedList<TData>::InsertNodeAfter(ListNode<TData> *RefNode, ListNode<TData> *NewNode){
	_SortStatus = Unordered;
	NewNode -> SetNext(RefNode -> Next());
	RefNode ->SetNext(NewNode);
}
template <typename TData> ListNode<TData> *LinkedList<TData>::InsertNodeAfter(ListNode<TData> *RefNode, TData NewData){
	_SortStatus = Unordered;
	ListNode<TData> *NewNode = CreateNode(NewData);
	NewNode -> SetNext(RefNode -> Next());
	RefNode ->SetNext(NewNode);
	return NewNode;
}
template <typename TData> ListNode<TData> *LinkedList<TData>::InsertNodeAfter(ListNode<TData> *RefNode){
	_SortStatus = Unordered;
	ListNode<TData> *NewNode = CreateNode();
	NewNode -> SetNext(RefNode -> Next());
	RefNode ->SetNext(NewNode);
	return NewNode;
}
/*
	Static Methods
*/
//CreateNode()
template <typename TData> ListNode<TData> *LinkedList<TData>::CreateNode(){
	return new ListNode<TData>;
}
template <typename TData> ListNode<TData> *LinkedList<TData>::CreateNode(TData data){
	ListNode<TData> *node = new ListNode<TData>;
	node -> SetData(data);
	return node;
}

//DestroyNode
template <typename TData> void LinkedList<TData>::DestroyNode(ListNode<TData> *Node){
	delete Node;
}

//DeleteNodesChained
template <typename TData> void LinkedList<TData>::DeleteNodesChained(ListNode<TData> *Node, ListNode<TData> *previous){
	Rewind();
	if (previous != NULL){
		previous -> SetNext(NULL);
	}
	else if (Node == _firstNode){
		_firstNode = NULL;
	}
	if (Node == NULL){
		return;
	}
	else{
		ListNode<TData> *next;
		while (Node != NULL){
			next = Node -> Next();
			DestroyNode(Node);
			Node = next;
		}
	}
}

template <typename TData> template <typename TSearch> bool LinkedList<TData>::DeleteNodesChained(TSearch data){
	ListNode<TData> *current, *previous;
	//Normally, in order not to disturb the internal pointer, I will search for the node manually in the method. But since
	//the internal pointer is going to be rewinded anyway, might as well make use of existing methods.
	Rewind();
	current = SearchForNode(data, previous);
	if (current != NULL){
		DeleteNodesChained(current, previous);
		return true;
	}
	return false;
}

#endif /* List_H */