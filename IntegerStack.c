//-----------------------------------------------------------------------------
// IntegerStack.c
// Array based implementation of Integer Stack ADT in C
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include"IntegerStack.h"

// Private Types and Functions ------------------------------------------------

// InitialSize
static const int InitialSize = 1;

// IntegerStackObj
typedef struct IntegerStackObj{
   int* item;     	// array of IntegerStack items
   int numItems;  	// number of items in this IntegerStack
   int physicalSize;	// current length of underlying array
} IntegerStackObj;


// doubleItemArray
// Doubles the physical size of the underlying array S->item.
void doubleItemArray(IntegerStack S){
   int i;
   int* newArray;
   int* oldArray = S->item;
   S->physicalSize *= 2;
   newArray = calloc(S->physicalSize, sizeof(int));
   for( i=0; i<(S->numItems); i++){
      newArray[i] = oldArray[i];
   }
   S->item = newArray;
   free(oldArray);
}

// arrayIndex()
// transforms an IntegerStack index to an Array index
int arrayIndex(int listIndex){
   return listIndex-1;
}


// Constructors-Destructors ---------------------------------------------------
// newIntegerStack()
// Constructor for the IntegerStack ADT
IntegerStack newIntegerStack(){
   IntegerStack S = malloc(sizeof(IntegerStackObj));
   S->item = calloc(InitialSize, sizeof(int));
   S->numItems = 0;
   S->physicalSize = InitialSize;
   return S;
}

// freeIntegerStack()
// Destructor for the Stack ADT
void freeIntegerStack(IntegerStack* pS){
   if( pS != NULL && *pS != NULL ){
      free((*pS)->item);
      free(*pS);
      *pS = NULL;
   }
}


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if Stack S is empty, 0 (false) otherwise
int isEmpty(IntegerStack S) {
   if( S==NULL ) {
      fprintf(stderr, "IntegerStack Error: isEmpty() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   return (S->numItems == 0);
}

// peek()
// Returns integer at top of S.
// Pre: !isEmpty(S)
int peek(IntegerStack S) {
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: peek() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   int n = S->numItems;
   return S->item[arrayIndex(n-1)];
}

// push()
// Pushes x on top of S.
void push(IntegerStack S, int x) {
   if( S==NULL ) {
      fprintf(stderr, "IntegerStack Error: push() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }
   //increase physical size of array if necessary
   if((S->numItems) == (S->physicalSize)) {
      doubleItemArray(S);
   }     

   S->item[S->numItems] = x;
   S->numItems++;

}

// pop()
// Deletes and returns integer at top of S
// Pre: !isEmpty(S)
int pop(IntegerStack S) {
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: pop() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   S->item[S->numItems-1] = NULL;
   S->numItems--;
   return S->item[S->numItems-1];
}


// popAll()
// Resets S to the empty state.
void popAll(IntegerStack S) {
   if( S==NULL ) {
      fprintf(stderr, "IntegerStack Error: popAll() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   S->numItems = 0;
}

// --------------------------------------------------------------------------------------------------------------
// Other Operations ---------------------------------------------------------------------------------------------

// printIntegerStack()
// Prints a space separated list of items in L to file stream pointed to by out
void printIntegerStack(FILE* out, IntegerStack S){
   int i;
   if( S==NULL ){
      fprintf(stderr, "IntegerStack Error: printIntegerStack() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   for( i=1; i<=(S->numItems); i++){
      fprintf(out, "%d ", S->item[arrayIndex(i)] );
   }
   fprintf(out, "\n");
}

// equals()
// Returns true (1) if L and R are matching sequences of integers, false (0) 
// otherwise
int equals(IntegerStack L, IntegerStack R){
   int i, eq;
   if( L==NULL || R==NULL ){
      fprintf(stderr, "IntegerStack Error: equals() called on NULL IntegerStack reference");
      exit(EXIT_FAILURE);
   }

   eq = ( (L->numItems)==(R->numItems) );
   for( i=1; eq && i<=(L->numItems); i++){
      eq = ( (L->item[arrayIndex(i)])==(R->item[arrayIndex(i)]) );
   }
   return eq;
}
