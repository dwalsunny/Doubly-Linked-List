/*****************************************
 * Name: Sunny Dhaliwal
 * Student ID: 20478089
 * UW User ID:  s24dhali
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H

#define nullptr 0

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

#define nullptr 0

template <typename Type>
class Double_list {
private:
    Double_node<Type> *list_head;
    Double_node<Type> *list_tail;
    int list_size;
    
public:
    Double_list();
    Double_list( Double_list const & );
    ~Double_list();
    
    // Accessors
    
    int size() const;
    bool empty() const;
    
    Type front() const;
    Type back() const;
    
    Double_node<Type> *head() const;
    Double_node<Type> *tail() const;
    
    int count( Type const & ) const;
    
    // Mutators
    
    void swap( Double_list & );
    Double_list &operator=( Double_list const & );
    
    void push_front( Type const & );
    void push_back( Type const & );
    
    Type pop_front();
    Type pop_back();
    
    int erase( Type const & );
    
	// Friends
    
	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_list<T> const & );
};

template <typename Type>
Double_list<Type>::Double_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
}

template <typename Type>
Double_list<Type>::Double_list( Double_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	
    //Iterate through the list and push back each element in the list to this doubly linked list.
    for(Double_node<Type> *ptr = list.list_head; ptr!=nullptr; ptr = ptr->next())
    {
        push_back(ptr->retrieve());
    }
  }

template <typename Type>
Double_list<Type>::~Double_list<Type>() {
    
    //While the doubly linked list is not empty I keep popping the node at the front of the list.
    //When the loop executes as false the doubly linked list is now empty
    while(!empty())
    {
        pop_front();
    }
}

template <typename Type>
int Double_list<Type>::size() const {
    // Returns a counter variable storing the number of elements in the linked list
    return list_size;
}

template <typename Type>
bool Double_list<Type>::empty() const {
    // Returns a true/false depending on if list_size = 0 (this is because we used the double equal sign)
	return (list_size == 0);
}

template <typename Type>
Type Double_list<Type>::front() const {
    // If the linked list is empty we throw an underflow
	if(empty())
    {
        throw underflow();
    }
    
    // If the linked list has at least 1 element it will return the value at the head.
    return list_head->retrieve();
}

template <typename Type>
Type Double_list<Type>::back() const {
    // If the linked list is empty we throw an underflow
    if(empty())
    {
        throw underflow();
    }
    
    // If the linked list has at least 1 element it will return the value at the tail.
    return list_tail->retrieve();
}

template <typename Type>
Double_node<Type> *Double_list<Type>::head() const {
    // Returns the pointer to the head of the linked list
	return list_head;
}

template <typename Type>
Double_node<Type> *Double_list<Type>::tail() const {
    // Returns the pointer to the tail of the linked list.
	return list_tail;
}

template <typename Type>
int Double_list<Type>::count( Type const &obj ) const {
    int counter = 0;
    
    // If the linked list is empty we return 0 as the element we are looking for is not in the linked list.
    if(empty()){return 0;}
        
    
    // Iterate through the linked list and increment the counter variable by 1 each time the current pointer has the same
    // value as the value being passed in.
	for(Double_node<Type> *ptr = list_head; ptr != nullptr; ptr = ptr->next())
    {
        if(ptr->retrieve() == obj)
        {
            ++counter;
        }
    }
    
    return counter;
}

template <typename Type>
void Double_list<Type>::swap( Double_list<Type> &list ) {
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

template <typename Type>
Double_list<Type> &Double_list<Type>::operator=( Double_list<Type> const &rhs ) {
	Double_list<Type> copy( rhs );
    
	swap( copy );
	
	return *this;
}

template <typename Type>
void Double_list<Type>::push_front( Type const &obj ) {
    // If the linked list is empty, create a new node with null pointers for the next and previous pointer
    // and set the value of the node to the value being passed in and set list_head and list_tail to the new node.
    if(empty())
    {
        Double_node<Type> *node = new Double_node<Type>(obj, nullptr, nullptr);
        list_head = list_tail = node;
        ++list_size;
    }
    
    // If the linked list is not empty, create a new node with a null pointer for the previous pointer and
    // the previous list_head as the next pointer. Set the value of the node to the value being passed in and
    // set previous node of the old list_head to the new node and set the list_head to the new node.
    else
    {
        Double_node<Type> *node = new Double_node<Type>(obj, nullptr, list_head);
        list_head->previous_node = node;
        list_head = node;
        ++list_size;
    }
}

template <typename Type>
void Double_list<Type>::push_back( Type const &obj ) {
    
    // If the linked list is empty, create a new node with null pointers for the next and previous pointer
    // and set the value of the ndoe to the value being passed in and set the list_head and list_tail to the new node.
    if(empty())
    {
        Double_node<Type> *node = new Double_node<Type>(obj, nullptr, nullptr);
        list_tail = list_head = node;
        ++list_size;
    }
    
    //If the linked list is not empty, create a new node with a null pointer for the next pointer and
    // the previous list_tail as the previous pointer. Set the value of the node to the value being passed in and
    // set the next node of the old list_tail to the new node and set the list_tail to the new node.
    else
    {
        Double_node<Type> *node = new Double_node<Type>(obj, list_tail, nullptr);
        list_tail->next_node = node;
        list_tail = node;
        ++list_size;
    }
}

template <typename Type>
Type Double_list<Type>::pop_front() {
    
    // If the linked list is empty throw an underflow.
    if(empty())
    {
        throw underflow();
    }
    
    // If the linked list has a size of 1, save the value of the element being popped, assign the head and tail pointers
    // to null and return the value popped.
    if(list_size == 1)
    {
        Type popped =  front();
        Double_node<Type> *ptr = head();
        list_head = list_tail = nullptr;
        delete ptr;
        --list_size;
        return popped;
    }
    
    // If the linked list has a size of greater than 1, save the value of element being popped, and assign the head
    // pointer to the node next to the old head and set the previous pointer to the new head to null. Then return the value
    // popped.
    else
    {
        Type popped =  front();
        Double_node<Type> *ptr = head();
        list_head = list_head->next();
        list_head->previous_node = nullptr;
        delete ptr;
        --list_size;
        return popped;
    }
}

template <typename Type>
Type Double_list<Type>::pop_back() {
    
    // If the linked list is empty, throw an underflow.
    if(empty())
    {
        throw underflow();
    }
    
    // If the linked list has a size of 1, save the value of the element being popped, assign the head and tail pointers
    // to null and return the value being popped.
    else if(list_size == 1)
    {
        Type popped = back();
        Double_node<Type> *ptr = tail();
        list_tail = list_head = nullptr;
        delete ptr;
        --list_size;
        return popped;
    }
    
    
    // If the linked list has a size greater than 1, save the value of the element being popped, and assign the tail
    // pointer to the node previous to the old tail and set the node after the new tail to null. Then return the value
    // popped.
    else
    {
        Type popped = back();
        Double_node<Type> *ptr = tail();
        list_tail = list_tail->previous();
        list_tail->next_node = nullptr;
        delete ptr;
        --list_size;
        return popped;
    }
}

template <typename Type>
int Double_list<Type>::erase( Type const &obj ) {
    
    // Iterating through the linked list
    for(Double_node<Type> *ptr = list_head; ptr != nullptr; ptr = ptr->next())
    {
        if(ptr->retrieve() == obj)
        {
            // If the value passed in is equal to the value at the head of the link list we pop front and return 1
			if(head() == ptr)
            {
				pop_front();
				return 1;
			}
            
            // If the value passed in is equal to the value at the tail of the link list we pop back and return 1
            else if(tail() == ptr)
            {
				pop_back();
				return 1;
			}
            
            // If the value passed in is between the head and tail it will reassign the next and previous pointers to exclude
            // the pointer we are trying to remove and then it will delete that ptr and return 1.
            else
            {
				ptr->previous_node->next_node = ptr->next_node;
				ptr->next_node->previous_node = ptr->previous_node;
				delete ptr;
				--list_size;
				return 1;
			}
		}
    }
    
    // If the value passed into the method is not found 0 will be returned.
    return 0;
}


// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_list<T> const &list ) {
	out << "head";
    
	for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
		out << "->" << ptr->retrieve();
	}
    
	out << "->0" << std::endl << "tail";
    
	for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
		out << "->" << ptr->retrieve();
	}
    
	out << "->0";
    
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
