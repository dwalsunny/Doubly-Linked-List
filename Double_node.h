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

#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#define nullptr 0

#include "ece250.h"

template <typename Type>
class Double_list;

template <typename Type>
class Cyclic_double_list;

template <typename Type>
class Double_sentinel_list;

template <typename Type>
class Cyclic_double_sentinel_list;

template <typename Type>
class Double_node {
private:
    Type       element;
    Double_node *previous_node;
    Double_node *next_node;
    
public:
    Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );
    
    Type retrieve() const;
    Double_node *previous() const;
    Double_node *next() const;
    
    friend class Double_list<Type>;
    friend class Cyclic_double_list<Type>;
    friend class Double_sentinel_list<Type>;
    friend class Cyclic_double_sentinel_list<Type>;
    
    // if ptr is a pointer to a Double_node<Type> object
    // in one of the friendly classes, you should:
    //    use   ptr->next_node   to modify it
    //    use   ptr->next()      to access it
};

template <typename Type>
Double_node<Type>::Double_node( Type const &e, Double_node<Type> *p, Double_node<Type> *n ):
element( e ),
previous_node( p ),
next_node( n ) {
}

template <typename Type>
Type Double_node<Type>::retrieve() const {
    // returns the value at the specific node
	return element;
}

template <typename Type>
Double_node<Type> *Double_node<Type>::previous() const {
    // returns a pointer pointing to the node previous to the node currently at
    return previous_node;
}

template <typename Type>
Double_node<Type> *Double_node<Type>::next() const {
    // returns a pointer pointing to the node next to the node currently at
	return next_node;
}

#endif
