//-----------------------------------------------------------------------------
// IntegerList.h
// Header file for the Integer List ADT in C
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>

#ifndef _List_H_INCLUDE_
#define _List_H_INCLUDE_


// Exported type --------------------------------------------------------------

// IntegerList
// Exported reference type
typedef struct IntegerListObj* IntegerList;


// Constructors-Destructors ---------------------------------------------------

// newIntegerList()
// Constructor for the IntegerList ADT
IntegerList newIntegerList();

// freeIntegerList()
// Destructor for the List ADT
void freeIntegerList(IntegerList* pL);


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if List L is empty, 0 (false) otherwise
int isEmpty(IntegerList L);

// size()
// Returns the number of elements in L
int size(IntegerList L);

// get()
// pre: 1 <= index <= size(L)
// Returns int at position index in L
int get(IntegerList L, int index);

// add()
// Inserts int x into L at position index
// pre: 1 <= index <= size(L)+1
void add(IntegerList L, int index, int x);

// delete()
// Deletes int from position index
// pre: 1 <= index <= size(L)
void delete(IntegerList L, int index);

// deleteAll()
// Reset L to the empty state
void deleteAll(IntegerList L);


// Other Operations -----------------------------------------------------------

// printIntegerList()
// Prints a space separated list of items in L to file stream pointed to by out
void printIntegerList(FILE* out, IntegerList L);

// equals()
// Returns true (1) if L and R are matching sequences of integers, false (0) 
// otherwise
int equals(IntegerList L, IntegerList R);


#endif
